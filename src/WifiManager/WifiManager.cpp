#include "WifiManager.hpp"

WifiManager::WifiManager() : networkCount(0) {}

void WifiManager::scanNetworks()
{
    networkCount = WiFi.scanNetworks();
}

void WifiManager::populateDropdown(lv_obj_t *dropdown)
{
    for (int i = 0; i < networkCount; i++)
    {
        lv_dropdown_add_option(dropdown, WiFi.SSID(i).c_str(), LV_DROPDOWN_POS_LAST);
    }
}

int WifiManager::getNetworkCount() const
{
    return networkCount;
}

String WifiManager::getSSID(int index) const
{
    if (index < networkCount && index >= 0)
    {
        return WiFi.SSID(index);
    }
    return "";
}

void WifiManager::scanAndPopulateDropdown(lv_obj_t *dropdown)
{
    scanNetworks();
    populateDropdown(dropdown);
}

void WifiManager::connectToSSID(const char *ssid, const char *password)
{
    // Ensure WiFi is in station mode
    WiFi.mode(WIFI_STA);

    // Connect to the provided SSID with password
    WiFi.begin(ssid, password);

    // You can expand on this with a more elaborate connection handling,
    // including waiting for connection, handling failures, etc.
}