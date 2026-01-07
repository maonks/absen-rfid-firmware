#pragma once
#include <Arduino.h>
#include "config.h"

inline void buzzerInit() {
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
}

// 1x beep pendek (scan kartu)
inline void buzzerTap() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(80);
  digitalWrite(BUZZER_PIN, LOW);
}

// 2x beep pendek (send data sukses)
inline void buzzerSuccess() {
  for (int i = 0; i < 2; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(80);
    digitalWrite(BUZZER_PIN, LOW);
    delay(80);
  }
}

// 1x beep panjang (gagal send data)
inline void buzzerError() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(300);
  digitalWrite(BUZZER_PIN, LOW);
}