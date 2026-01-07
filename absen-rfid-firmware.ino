#include <Arduino.h>
#include <time.h>

#include "config/config.h"
#include "core/wifi_manager.h"
#include "core/http_client.h"
#include "rfid/rfid_reader.h"
#include "utils/buzzer.h"

void setup() {
  Serial.begin(115200);
  pinMode(BUZZER_PIN, OUTPUT);

  wifiConnect();
  configTime(28800, 0, "pool.ntp.org");

  SPI.begin();
  Serial.println("READY - TAP CARD");
}

void loop() {
  String uid;
  if (!readRFID(uid)) return;

  buzz();
  String waktu = "AUTO_TIME"; // bisa pakai fungsi time util
  sendAbsen(uid, waktu);

  delay(1500);
}
