#pragma once
#include <Arduino.h>

String hmacSign(const String& payload);
String getNowTime();
