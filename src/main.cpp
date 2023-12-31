// Libraries
#include <lvgl.h>
#include <ui.h>
#include <TinyGPSPlus.h>
#include "compass/compass.hpp"
#include "time/time.hpp"
#include "WifiManager/WifiManager.hpp"
#include "UI/ui_helpers.h"
#include <Arduino_GFX_Library.h>
#include <Wire.h>

#define SDA_PIN 37
#define SCL_PIN 38

// Constants
#define TFT_BL 2
#define GFX_BL DF_GFX_BL

// Variables
Compass compass;
WifiManager wifiManager;
HardwareSerial gpsSerial(1);
TinyGPSPlus gps;
TimeModule timeHandler(gps);

static uint32_t screenWidth;
static uint32_t screenHeight;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t disp_draw_buf[480 * 272 / 8];
static lv_disp_drv_t disp_drv;
static lv_indev_drv_t indev_drv;

// Functions declaration
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);
void updateRealSpeed(float speed);
void lvgl_loop(void *parameter);
void guiHandler();

// Touch calibration data
uint16_t touchCalibration_x0 = 300, touchCalibration_x1 = 3600, touchCalibration_y0 = 300, touchCalibration_y1 = 3600;
uint8_t touchCalibration_rotate = 1, touchCalibration_invert_x = 2, touchCalibration_invert_y = 0;

Arduino_ESP32RGBPanel *bus = new Arduino_ESP32RGBPanel(
    GFX_NOT_DEFINED, GFX_NOT_DEFINED, GFX_NOT_DEFINED,
    40, 41, 39, 42,
    45, 48, 47, 21, 14,
    5, 6, 7, 15, 16, 4,
    8, 3, 46, 9, 1);
Arduino_RPi_DPI_RGBPanel *lcd = new Arduino_RPi_DPI_RGBPanel(
    bus,
    480, 0, 8, 2, 43,
    272, 0, 8, 2, 12,
    1, 7000000, true);

#include "touch.h"

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  lcd->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);

  lv_disp_flush_ready(disp);
}

void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
  if (touch_has_signal())
  {
    if (touch_touched())
    {
      data->state = LV_INDEV_STATE_PR;
      data->point.x = touch_last_x;
      data->point.y = touch_last_y;
    }
    else if (touch_released())
    {
      data->state = LV_INDEV_STATE_REL;
    }
  }
  else
  {
    data->state = LV_INDEV_STATE_REL;
  }
}

void updateRealSpeed(float speed)
{
  lv_arc_set_value(ui_ArcSpeed, speed);
  lv_label_set_text_fmt(ui_LabelSpeed, "%d", (int)speed);
}

void lvgl_loop(void *parameter)
{
  while (true)
  {
    lv_timer_handler();
  }
  vTaskDelete(NULL);
}

void guiHandler()
{
  xTaskCreatePinnedToCore(
      lvgl_loop,
      "LVGL Loop",
      20480,
      NULL,
      1,
      NULL,
      1);
}

void keyboard_event_cb(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *kb = lv_event_get_target(e);

  if (code == LV_EVENT_VALUE_CHANGED)
  {
    uint16_t btn_idx = lv_keyboard_get_selected_btn(kb);

    // Display button index on the label for testing purposes
    // lv_label_set_text_fmt(ui_LabelTime, "Key index: %d", btn_idx);
    // Serial.print("Button pressed with index: ");
    // Serial.println(btn_idx);
    if (btn_idx == 39)
    {
      Serial.println('Enter pressed!');
      HideKeyboard_Animation(ui_Keyboard1, 0);
    }
  }
}

void connect_button_event_cb(lv_event_t *e)
{
  char SSIDBuffer[128];
  lv_dropdown_get_selected_str(ui_DropdownSSID, SSIDBuffer, sizeof(SSIDBuffer));

  // Retrieve password from text area
  const char *password = lv_textarea_get_text(ui_TextAreaWifiPassword);

  Serial.print("Selected SSID: ");
  Serial.print(SSIDBuffer);
  Serial.print("          Password: ");
  Serial.println(password);

  // Now initiate a WiFi connection
  wifiManager.connectToSSID(SSIDBuffer, password);

  // Optional: Provide feedback to the user, for instance:
  // lv_label_set_text(ui_LabelConnectionStatus, "Connecting...");
}

void setup()
{
  Serial.begin(115200);
  gpsSerial.begin(9600, SERIAL_8N1, 18, 17);

  Wire.begin(SDA_PIN, SCL_PIN);
  compass.init();
  timeHandler.setTimeZoneOffset(-5);

  lcd->begin();
  lcd->fillScreen(BLACK);
  lcd->setTextSize(2);
  delay(200);

  lv_init();
  touch_init();

  screenWidth = lcd->width();
  screenHeight = lcd->height();

  lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, screenWidth * screenHeight / 10);

  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  lcd->fillScreen(BLACK);

  ui_init();
  guiHandler();
  lv_obj_add_event_cb(ui_Keyboard1, keyboard_event_cb, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui_ButtonSaveWifi, connect_button_event_cb, LV_EVENT_CLICKED, NULL);

  wifiManager.scanAndPopulateDropdown(ui_DropdownSSID);
}

void loop()
{
  while (gpsSerial.available())
  {
    char c = gpsSerial.read();
    if (gps.encode(c))
    {
      updateRealSpeed(gps.speed.mph());
      lv_label_set_text_fmt(ui_LabelSatCount, "%d", gps.satellites.value());
      lv_label_set_text(ui_LabelTime, timeHandler.getTimeString());
      compass.update();
    }
  }

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println("No GPS data received: check wiring");
    while (true)
      ;
  }
}
