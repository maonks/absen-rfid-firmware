#include "rfid_reader.h"
#include <SPI.h>
#include <MFRC522.h>
#include "config.h"

static MFRC522 rfid(SS_PIN, RST_PIN);

void rfidInit() {
  SPI.begin();
  rfid.PCD_Init();
}

bool rfidCardPresent() {
  return rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial();
}

String rfidReadUID() {
  String uid = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10) uid += "0";
    uid += String(rfid.uid.uidByte[i], HEX);
  }
  uid.toUpperCase();

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  return uid;
}
