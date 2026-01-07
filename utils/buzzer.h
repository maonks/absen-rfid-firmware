#pragma once
#include <Arduino.h>

static inline void buzz() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(120);
  digitalWrite(BUZZER_PIN, LOW);
}
