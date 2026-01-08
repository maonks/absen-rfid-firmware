#include "http_client.h"
#include "config.h"
#include "crypto.h"

#include <WiFi.h>
#include <HTTPClient.h>
#include <vector>

struct OfflineData {
  String uid;
  String waktu;
};

static std::vector<OfflineData> offlineQueue;

bool sendData(const String& uid, const String& waktu) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("[HTTP] FAIL: WiFi disconnected");
    return false;
  }

  HTTPClient http;
  String payload =
    "{\"uid\":\"" + uid +
    "\",\"device_id\":\"" + DEVICE_ID +
    "\",\"waktu\":\"" + waktu + "\"}";

  String sig = hmacSign(payload);

  // 🔍 DEBUG HMAC
  Serial.println("[HMAC] Payload:");
  Serial.println(payload);
  Serial.println("[HMAC] Signature:");
  Serial.println(sig);

  http.begin(API_URL);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("X-Signature", sig);

  int code = http.POST(payload);
  http.end();

  Serial.printf("[HTTP] Response Code = %d\n", code);

  return code == 200;
}


void queueOffline(const String& uid, const String& waktu) {
  offlineQueue.push_back({uid, waktu});
}

void syncOfflineQueue() {
  if (WiFi.status() != WL_CONNECTED || offlineQueue.empty()) return;

  for (auto &d : offlineQueue) {
    sendData(d.uid, d.waktu);
  }
  offlineQueue.clear();
}

void testHttpBasic() {
  HTTPClient http;
  http.begin("http://192.168.1.100:8000/health");
  int code = http.GET();
  http.end();

  Serial.printf("[TEST] HTTP GET /health => %d\n", code);
}

void testPostNoHmac() {
  HTTPClient http;
  http.begin("http://192.168.1.100:8000/test");
  http.addHeader("Content-Type", "application/json");

  int code = http.POST("{\"ping\":\"ok\"}");
  http.end();

  Serial.printf("[TEST] POST no HMAC => %d\n", code);
}
