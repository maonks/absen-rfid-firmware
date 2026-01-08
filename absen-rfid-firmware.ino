#include "config.h"
#include "secrets.h"

#include "wifi_manager.h"
#include "http_client.h"
#include "rfid_reader.h"
#include "crypto.h"
#include "buzzer.h"




unsigned long lastTap = 0;

void setup() {
  Serial.begin(115200);
  buzzerInit();

  wifiConnect();

  testHttpBasic();
  testPostNoHmac();
  
  initTime();
  rfidInit();

  Serial.println("[RFID] Ready");

  Serial.println("[TEST] IP ESP32 = " + WiFi.localIP().toString());
  Serial.println("[TEST] Gateway = " + WiFi.gatewayIP().toString());
}

void loop() {
  syncOfflineQueue();

  if (!rfidCardPresent()) return;

  unsigned long now = millis();
  if (now - lastTap < TAP_COOLDOWN) return;
  lastTap = now;

  String uid = rfidReadUID();
  String waktu = getNowTime();

  Serial.printf("[TAP] UID=%s | TIME=%s\n", uid.c_str(), waktu.c_str());
  Serial.flush();

  // bunyi saat TAP
  buzzerTap();

  if (sendData(uid, waktu)) {
    Serial.println("[INFO] Sukses kirim");
    buzzerSuccess();        // 🔥 2x beep
  } else {
    queueOffline(uid, waktu);
    Serial.println("[INFO] Gagal kirim → queued");
    buzzerError();          // 🔥 beep panjang
  }

}
