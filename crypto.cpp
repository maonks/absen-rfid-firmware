#include "crypto.h"
#include "secrets.h"
#include <time.h>
#include "mbedtls/md.h"


String getNowTime() {
  struct tm t;
  if (!getLocalTime(&t)) return "0000-00-00 00:00:00";
  char buf[20];
  strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &t);
  return String(buf);
}

String hmacSign(const String& payload) {
  byte hmac[32];
  mbedtls_md_context_t ctx;
  mbedtls_md_init(&ctx);
  mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(MBEDTLS_MD_SHA256), 1);
  mbedtls_md_hmac_starts(&ctx,
    (const unsigned char*)SECRET_KEY, strlen(SECRET_KEY));
  mbedtls_md_hmac_update(&ctx,
    (const unsigned char*)payload.c_str(), payload.length());
  mbedtls_md_hmac_finish(&ctx, hmac);
  mbedtls_md_free(&ctx);

  String out;
  for (int i = 0; i < 32; i++) {
    if (hmac[i] < 16) out += "0";
    out += String(hmac[i], HEX);
  }
  return out;
}
