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

    return false;
  }

  HTTPClient http;
  String payload =
    "{\"uid\":\"" + uid +
    "\",\"device_id\":\"" + DEVICE_ID +
    "\",\"waktu\":\"" + waktu + "\"}";

  http.begin(API_URL);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("X-Signature", hmacSign(payload));

  int code = http.POST(payload);
  http.end();

  if (code != 200) {

    return false;
  }
  return true;
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
