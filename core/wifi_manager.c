#include <WiFi.h>
#include "wifi_manager.h"
#include "config/secrets.h"

void wifiConnect() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}
