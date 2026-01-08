#pragma once
#include <Arduino.h>

bool sendData(const String& uid, const String& waktu);
void queueOffline(const String& uid, const String& waktu);
void syncOfflineQueue();

void testHttpBasic();
void testPostNoHmac();
