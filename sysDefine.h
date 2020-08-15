#ifndef SYSDEFINE
#define SYSDEFINE
#ifndef NAME_DEVICE
#define NAME_DEVICE "TESTUI" // đặt tên cho dự án
#endif
#define LED_PIN -1
#define CONFIG_FILE F("/config.json")
#define SIZE_CONFIG_FILE 8192
#define LOG(l) Serial.println(l)
 // #define LOG(l)
#endif
