#include "crypto.h"
#include "mbedtls/md.h"
#include "config/secrets.h"

String hmacSign(String payload) {
  byte hmac[32];
  mbedtls_md_context_t ctx;
  mbedtls_md_init(&ctx);
  mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(MBEDTLS_MD_SHA256), 1);

  mbedtls_md_hmac_starts(&ctx,
    (const unsigned char*)SECRET,
    strlen(SECRET)
  );
  mbedtls_md_hmac_update(&ctx,
    (const unsigned char*)payload.c_str(),
    payload.length()
  );
  mbedtls_md_hmac_finish(&ctx, hmac);
  mbedtls_md_free(&ctx);

  String sig;
  for (int i = 0; i < 32; i++) sig += String(hmac[i], HEX);
  return sig;
}
