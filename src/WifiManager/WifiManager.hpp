#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>
#include <lvgl.h>

class WifiManager
{
public:
    WifiManager();
    void scanNetworks();
    void populateDropdown(lv_obj_t *dropdown);
    void scanAndPopulateDropdown(lv_obj_t *dropdown);
    void connectToSSID(const char *ssid, const char *password);
    int getNetworkCount() const;
    String getSSID(int index) const;

private:
    int networkCount;
    WiFiScanClass scannedNetworks;
};

#endif
