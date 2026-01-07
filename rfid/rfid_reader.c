#include <SPI.h>
#include <MFRC522.h>
#include "rfid_reader.h"
#include "config/config.h"

MFRC522 rfid(SS_PIN, RST_PIN);

bool readRFID(String &uid) {
  if (!rfid.PICC_IsNewCardPresent()) return false;
  if (!rfid.PICC_ReadCardSerial()) return false;

  uid = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    uid += (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
           String(rfid.uid.uidByte[i], HEX);
  }
  uid.toUpperCase();

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  return true;
}
