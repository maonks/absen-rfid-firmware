#include <HTTPClient.h>
#include "http_client.h"
#include "utils/crypto.h"
#include "config/config.h"

bool sendAbsen(String uid, String waktu) {
  if (WiFi.status() != WL_CONNECTED) return false;

  HTTPClient http;
  String payload =
    "{\"uid\":\"" + uid +
    "\",\"device_id\":\"" DEVICE_ID +
    "\",\"waktu\":\"" + waktu + "\"}";

  http.begin(API_URL);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("X-Signature", hmacSign(payload));

  int code = http.POST(payload);
  http.end();

  return code == 200;
}
