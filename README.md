# ESP32-S3-N16R8

Community PlatformIO support for the ESP32-S3-WROOM-1U N16R8, providing a custom board definition for a configuration with 16 MB Flash and 8 MB Octal PSRAM.

## Why This Repository?

The ESP32-S3-WROOM-1U N16R8 is an ESP32-S3 module configuration with 16 MB Flash and 8 MB Octal PSRAM. However, there is no dedicated `esp32-s3-wroom-1u-n16r8` 
board option in the standard PlatformIO Espressif32 board list.

This repository provides a custom PlatformIO board definition and a documented ESP-IDF configuration procedure for developers using this module.

The configuration has been tested on physical ESP32-S3-WROOM-1U N16R8 hardware.

---

## Hardware

### ESP32-S3-WROOM-1U N16R8

 Specification  
 MCU:  ESP32-S3 
 CPU Frequency:  240 MHz 
 Flash:  16 MB 
 PSRAM: 8 MB 
 PSRAM Type:  Octal SPI (OPI) 
 Connectivity:  Wi-Fi / Bluetooth LE 
 Framework:  ESP-IDF 
 Development Platform:  PlatformIO 

The `N16R8` designation refers to:

N16 = 16 MB Flash
R8 = 8 MB Octal PSRAM

---

