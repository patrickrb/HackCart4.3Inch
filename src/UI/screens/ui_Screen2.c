// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.2
// LVGL version: 8.3.6
// Project name: hackcart43

#include "../ui.h"

void ui_Screen2_screen_init(void)
{
ui_Screen2 = lv_obj_create(NULL);
lv_obj_clear_flag( ui_Screen2, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_WifiFormPanel = lv_obj_create(ui_Screen2);
lv_obj_set_width( ui_WifiFormPanel, 371);
lv_obj_set_height( ui_WifiFormPanel, 252);
lv_obj_set_x( ui_WifiFormPanel, -12 );
lv_obj_set_y( ui_WifiFormPanel, -2 );
lv_obj_set_align( ui_WifiFormPanel, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_WifiFormPanel,LV_FLEX_FLOW_COLUMN);
lv_obj_set_flex_align(ui_WifiFormPanel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
lv_obj_clear_flag( ui_WifiFormPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_LabelWifiSettings = lv_label_create(ui_WifiFormPanel);
lv_obj_set_width( ui_LabelWifiSettings, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_LabelWifiSettings, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_LabelWifiSettings, LV_ALIGN_CENTER );
lv_label_set_text(ui_LabelWifiSettings,"Wifi Settings");

ui_PanelWIfiSettings = lv_obj_create(ui_WifiFormPanel);
lv_obj_set_width( ui_PanelWIfiSettings, 280);
lv_obj_set_height( ui_PanelWIfiSettings, 146);
lv_obj_set_x( ui_PanelWIfiSettings, -149 );
lv_obj_set_y( ui_PanelWIfiSettings, 72 );
lv_obj_set_align( ui_PanelWIfiSettings, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_PanelWIfiSettings,LV_FLEX_FLOW_COLUMN);
lv_obj_set_flex_align(ui_PanelWIfiSettings, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
lv_obj_clear_flag( ui_PanelWIfiSettings, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_border_color(ui_PanelWIfiSettings, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_PanelWIfiSettings, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_DropdownSSID = lv_dropdown_create(ui_PanelWIfiSettings);
lv_dropdown_set_options( ui_DropdownSSID, "" );
lv_obj_set_width( ui_DropdownSSID, 280);
lv_obj_set_height( ui_DropdownSSID, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_DropdownSSID, -14 );
lv_obj_set_y( ui_DropdownSSID, 51 );
lv_obj_set_align( ui_DropdownSSID, LV_ALIGN_TOP_MID );
lv_obj_add_flag( ui_DropdownSSID, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags



ui_TextAreaWifiPassword = lv_textarea_create(ui_PanelWIfiSettings);
lv_obj_set_width( ui_TextAreaWifiPassword, 280);
lv_obj_set_height( ui_TextAreaWifiPassword, LV_SIZE_CONTENT);   /// 42
lv_obj_set_x( ui_TextAreaWifiPassword, -14 );
lv_obj_set_y( ui_TextAreaWifiPassword, 18 );
lv_obj_set_align( ui_TextAreaWifiPassword, LV_ALIGN_CENTER );
lv_textarea_set_placeholder_text(ui_TextAreaWifiPassword,"wifi password");
lv_textarea_set_one_line(ui_TextAreaWifiPassword,true);



ui_PanelWIfiSettingsButtons = lv_obj_create(ui_WifiFormPanel);
lv_obj_set_width( ui_PanelWIfiSettingsButtons, 280);
lv_obj_set_height( ui_PanelWIfiSettingsButtons, 47);
lv_obj_set_x( ui_PanelWIfiSettingsButtons, 0 );
lv_obj_set_y( ui_PanelWIfiSettingsButtons, 19 );
lv_obj_set_align( ui_PanelWIfiSettingsButtons, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_PanelWIfiSettingsButtons,LV_FLEX_FLOW_ROW);
lv_obj_set_flex_align(ui_PanelWIfiSettingsButtons, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
lv_obj_clear_flag( ui_PanelWIfiSettingsButtons, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_border_color(ui_PanelWIfiSettingsButtons, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_PanelWIfiSettingsButtons, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ButtonCancelWifi = lv_btn_create(ui_PanelWIfiSettingsButtons);
lv_obj_set_width( ui_ButtonCancelWifi, 110);
lv_obj_set_height( ui_ButtonCancelWifi, 32);
lv_obj_set_x( ui_ButtonCancelWifi, -68 );
lv_obj_set_y( ui_ButtonCancelWifi, 17 );
lv_obj_set_align( ui_ButtonCancelWifi, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_ButtonCancelWifi,LV_FLEX_FLOW_ROW);
lv_obj_set_flex_align(ui_ButtonCancelWifi, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
lv_obj_add_flag( ui_ButtonCancelWifi, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_ButtonCancelWifi, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_text_color(ui_ButtonCancelWifi, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_ButtonCancelWifi, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_LabelCancelWifi = lv_label_create(ui_ButtonCancelWifi);
lv_obj_set_width( ui_LabelCancelWifi, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_LabelCancelWifi, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_LabelCancelWifi, -8 );
lv_obj_set_y( ui_LabelCancelWifi, 3 );
lv_obj_set_align( ui_LabelCancelWifi, LV_ALIGN_CENTER );
lv_label_set_text(ui_LabelCancelWifi,"Cancel");

ui_ButtonSaveWifi = lv_btn_create(ui_PanelWIfiSettingsButtons);
lv_obj_set_width( ui_ButtonSaveWifi, 110);
lv_obj_set_height( ui_ButtonSaveWifi, 32);
lv_obj_set_x( ui_ButtonSaveWifi, 65 );
lv_obj_set_y( ui_ButtonSaveWifi, 16 );
lv_obj_set_align( ui_ButtonSaveWifi, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_ButtonSaveWifi,LV_FLEX_FLOW_ROW);
lv_obj_set_flex_align(ui_ButtonSaveWifi, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
lv_obj_add_flag( ui_ButtonSaveWifi, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_ButtonSaveWifi, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_text_color(ui_ButtonSaveWifi, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_ButtonSaveWifi, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_ButtonSaveWifi, &lv_font_montserrat_14, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_LabelSaveWifi = lv_label_create(ui_ButtonSaveWifi);
lv_obj_set_width( ui_LabelSaveWifi, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_LabelSaveWifi, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_LabelSaveWifi, 1 );
lv_obj_set_y( ui_LabelSaveWifi, 11 );
lv_obj_set_align( ui_LabelSaveWifi, LV_ALIGN_CENTER );
lv_label_set_text(ui_LabelSaveWifi,"Save Wifi");

ui_Keyboard1 = lv_keyboard_create(ui_Screen2);
lv_keyboard_set_mode(ui_Keyboard1,LV_KEYBOARD_MODE_USER_4);
lv_obj_set_width( ui_Keyboard1, 476);
lv_obj_set_height( ui_Keyboard1, 93);
lv_obj_set_x( ui_Keyboard1, 1 );
lv_obj_set_y( ui_Keyboard1, 184 );
lv_obj_set_align( ui_Keyboard1, LV_ALIGN_CENTER );

lv_obj_add_event_cb(ui_TextAreaWifiPassword, ui_event_TextAreaWifiPassword, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_ButtonCancelWifi, ui_event_ButtonCancelWifi, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_ButtonSaveWifi, ui_event_ButtonSaveWifi, LV_EVENT_ALL, NULL);
lv_keyboard_set_textarea(ui_Keyboard1,ui_TextAreaWifiPassword);
lv_obj_add_event_cb(ui_Keyboard1, ui_event_Keyboard1, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_Screen2, ui_event_Screen2, LV_EVENT_ALL, NULL);

}
