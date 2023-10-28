// lvgl
#include <lvgl.h>
// UI
#include <ui.h>
#include "UI/ui_helpers.h"

uint16_t touchCalibration_x0 = 300, touchCalibration_x1 = 3600, touchCalibration_y0 = 300, touchCalibration_y1 = 3600;
uint8_t touchCalibration_rotate = 1, touchCalibration_invert_x = 2, touchCalibration_invert_y = 0;
static int val = 100;

static uint32_t screenWidth;
static uint32_t screenHeight;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t disp_draw_buf[480 * 272 / 8];
static lv_disp_drv_t disp_drv;
#include <Arduino_GFX_Library.h>
#define TFT_BL 2
#define GFX_BL DF_GFX_BL // default backlight pin, you may replace DF_GFX_BL to actual backlight pin

#if defined(DISPLAY_DEV_KIT)
Arduino_GFX *lcd = create_default_Arduino_GFX();
#else  /* !defined(DISPLAY_DEV_KIT) */

Arduino_ESP32RGBPanel *bus = new Arduino_ESP32RGBPanel(
    GFX_NOT_DEFINED /* CS */, GFX_NOT_DEFINED /* SCK */, GFX_NOT_DEFINED /* SDA */,
    40 /* DE */, 41 /* VSYNC */, 39 /* HSYNC */, 42 /* PCLK */,
    45 /* R0 */, 48 /* R1 */, 47 /* R2 */, 21 /* R3 */, 14 /* R4 */,
    5 /* G0 */, 6 /* G1 */, 7 /* G2 */, 15 /* G3 */, 16 /* G4 */, 4 /* G5 */,
    8 /* B0 */, 3 /* B1 */, 46 /* B2 */, 9 /* B3 */, 1 /* B4 */
);
// option 1:
// ILI6485 LCD 480x272
Arduino_RPi_DPI_RGBPanel *lcd = new Arduino_RPi_DPI_RGBPanel(
    bus,
    480 /* width */, 0 /* hsync_polarity */, 8 /* hsync_front_porch */, 2 /* hsync_pulse_width */, 43 /* hsync_back_porch */,
    272 /* height */, 0 /* vsync_polarity */, 8 /* vsync_front_porch */, 2 /* vsync_pulse_width */, 12 /* vsync_back_porch */,
    1 /* pclk_active_neg */, 7000000 /* prefer_speed */, true /* auto_flush */);
#endif /* !defined(DISPLAY_DEV_KIT) */
#include "touch.h"
/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

#if (LV_COLOR_16_SWAP != 0)
  lcd->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#else
  lcd->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#endif

  lv_disp_flush_ready(disp);
}

void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
  if (touch_has_signal())
  {
    if (touch_touched())
    {
      data->state = LV_INDEV_STATE_PR;

      /*Set the coordinates*/
      data->point.x = touch_last_x;
      data->point.y = touch_last_y;
      Serial.print("Data x :");
      Serial.println(touch_last_x);

      Serial.print("Data y :");
      Serial.println(touch_last_y);
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

int speedValue = 0;
bool incrementingSpeed = true;
const int speedInterval = 30;
const int SPEED_INCREMENT = 1;
const int MAX_SPEED = 45;
const int MIN_SPEED = 0;

float fraction = 0.0f; // Fraction of the animation cycle, varies from 0 to 1 and back to 0

void updateSpeed()
{
  const float FRACTION_INCREMENT = 0.005f;

  if (incrementingSpeed)
  {
    fraction += FRACTION_INCREMENT;
    if (fraction >= 1.0f)
    {
      fraction = 1.0f;
      incrementingSpeed = false;
    }
  }
  else
  {
    fraction -= FRACTION_INCREMENT;
    if (fraction <= 0.0f)
    {
      fraction = 0.0f;
      incrementingSpeed = true;
    }
  }

  // Applying the sine function for ease-in-out effect over the complete cycle
  speedValue = (int)(MAX_SPEED * (sin((fraction - 0.5f) * M_PI) + 1) / 2);

  lv_arc_set_value(ui_ArcSpeed, speedValue);
  lv_label_set_text_fmt(ui_LabelSpeed, "%d", speedValue);
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
      lvgl_loop,   // Function that should be called
      "LVGL Loop", // Name of the task (for debugging)
      20480,       // Stack size (bytes)
      NULL,        // Parameter to pass
      1,           // Task priority
      NULL,        // Task handle
      1);
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200); // Init Display

  lcd->begin();
  lcd->fillScreen(BLACK);
  lcd->setTextSize(2);
  delay(200);

  lv_init();
  touch_init();
  screenWidth = lcd->width();
  screenHeight = lcd->height();

  lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, screenWidth * screenHeight / 10);

  /* Initialize the display */
  lv_disp_drv_init(&disp_drv);
  /* Change the following line to your display resolution */
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  /* Initialize the (dummy) input device driver */
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  // Back light
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  lcd->fillScreen(BLACK);

  ui_init();
  guiHandler();
}

unsigned long previousMillis = 0;

void loop()
{
  unsigned long currentMillis = millis();

  // Calculate the time elapsed since the last update
  unsigned long timeElapsed = currentMillis - previousMillis;

  // Update speed based on elapsed time
  while (timeElapsed >= speedInterval)
  {
    updateSpeed();
    timeElapsed -= speedInterval;
    previousMillis += speedInterval;
  }
}