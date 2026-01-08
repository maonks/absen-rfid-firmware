#include "wifi_manager.h"
#include "secrets.h"

#include <WiFi.h>
#include <time.h>


void wifiConnect() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);    
  }
  Serial.println("[WIFI] Connected");
}

void initTime() {
  configTime(28800, 0, "pool.ntp.org");
}




