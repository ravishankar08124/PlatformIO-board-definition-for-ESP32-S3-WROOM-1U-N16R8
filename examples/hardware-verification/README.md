ESP32-S3-WROOM-1U N16R8
PlatformIO + ESP-IDF Configuration and Hardware Verification
================================================================

This guide explains how to configure and verify the custom
ESP32-S3-WROOM-1U N16R8 board definition.

Hardware configuration:

    MCU       : ESP32-S3
    Flash     : 16 MB
    PSRAM     : 8 MB Octal PSRAM (OPI)

The configuration must be performed using ESP-IDF menuconfig before
building the verification program.


1. COPY THE BOARD DEFINITION
============================

Before creating/building the project, copy the custom board definition:

    esp32-s3-wroom-1u-n16r8.json

into the PlatformIO project's local boards directory:

    <project>/
    ├── boards/
    │   └── esp32-s3-wroom-1u-n16r8.json
    ├── src/
    │   └── main.c
    └── platformio.ini

The board filename must be:

    esp32-s3-wroom-1u-n16r8.json

The board ID used in platformio.ini must match:

    board = esp32-s3-wroom-1u-n16r8


2. CONFIGURE THE PLATFORMIO PROJECT
===================================

Use the following PlatformIO configuration:

    [env:esp32-s3-wroom-1u-n16r8]
    platform = espressif32
    board = esp32-s3-wroom-1u-n16r8
    framework = espidf
    monitor_speed = 115200

Open a PlatformIO terminal in the project directory.


3. OPEN ESP-IDF MENUCONFIG
==========================

Run:

    pio run -t menuconfig

This opens the ESP-IDF configuration interface.


4. ENABLE OCTAL PSRAM
=====================

Inside menuconfig, navigate to:

    Component config
        |
        └── ESP PSRAM

Configure the following options:

    Initialize the PSRAM related hardware
        Enabled

    Initialize PSRAM during startup
        Enabled

    Mode (QUAD/OCT) of SPI RAM chip in use
        Octal Mode PSRAM

    Type of SPIRAM chip in use
        Auto-detect

    Run memory test on SPI RAM initialization
        Enabled


The important PSRAM settings are:

    CONFIG_SPIRAM=y
    CONFIG_SPIRAM_MODE_OCT=y
    CONFIG_SPIRAM_TYPE_AUTO=y

Do not select Quad Mode.

The N16R8 configuration requires Octal PSRAM.


5. CONFIGURE FLASH SIZE
=======================

Inside menuconfig, search for the Flash size configuration.

Use the menuconfig search function by pressing:

    /

Then search for:

    FLASHSIZE

Locate the ESP-IDF Flash size configuration and select:

    16 MB

The configuration should correspond to:

    CONFIG_ESPTOOLPY_FLASHSIZE_16MB=y

The physical module contains 16 MB Flash, so the ESP-IDF project
configuration should reflect the actual Flash capacity.


6. SAVE THE CONFIGURATION
=========================

After configuring PSRAM and Flash:

    Press S

to save the configuration.

Then exit menuconfig:

    Press Q

If ESP-IDF asks whether to save the configuration, select:

    Yes


7. BUILD THE PROJECT
====================

Run:

    pio run

The project should build successfully.

The board should be recognized as:

    esp32-s3-wroom-1u-n16r8

If PlatformIO reports:

    UnknownBoard: Unknown board ID

verify that the custom JSON file exists in:

    boards/
        esp32-s3-wroom-1u-n16r8.json

and that the board name in platformio.ini exactly matches the board ID
inside the JSON definition.


8. UPLOAD THE VERIFICATION PROGRAM
==================================

Connect the ESP32-S3-WROOM-1U N16R8 board to the computer.

Run:

    pio run -t upload

Select the correct COM port if PlatformIO asks for one.

The USB interface used for upload should be the interface recognized
by PlatformIO as the ESP32-S3 serial/upload port.


9. OPEN THE SERIAL MONITOR
==========================

Open the monitor at 115200 baud:

    pio device monitor

Alternatively, use PlatformIO's Serial Monitor in VS Code.

If the monitor is blank, press the ESP32-S3 EN/RESET button after
opening the monitor.


10. HARDWARE VERIFICATION
=========================

The verification program checks:

    1. Flash chip size
    2. PSRAM initialization
    3. Total PSRAM capacity
    4. Free PSRAM

A correctly configured N16R8 board should report:

    ============================
    ESP32-S3-N16R8 HARDWARE TEST
    ============================
    Flash size     : 16 MB
    PSRAM detected : YES
    Total PSRAM    : 8 MB
    Free PSRAM     : ...
    ============================


11. VERIFIED RESULT
===================

The configuration was tested on physical ESP32-S3-WROOM-1U N16R8
hardware.

The tested board produced:

    ============================
    ESP32-S3-N16R8 HARDWARE TEST
    ============================
    Flash size     : 16 MB
    PSRAM detected : YES
    Total PSRAM    : 8 MB
    Free PSRAM     : 8386156 bytes
    ============================

This confirms:

    ESP32-S3 MCU              : PASS
    16 MB Flash               : PASS
    8 MB PSRAM                : PASS
    Octal PSRAM initialization: PASS
    PlatformIO build          : PASS
    Firmware upload           : PASS
    Serial output             : PASS


12. IMPORTANT NOTE ABOUT FLASH SIZE
===================================

The physical Flash capacity and the application partition size are
different concepts.

The ESP32-S3-WROOM-1U N16R8 physically contains:

    16 MB Flash

However, the amount of Flash shown as available for the application
during a PlatformIO build depends on the selected partition table.

Therefore, a build output such as:

    Flash: [==        ] ...
    used ... bytes from 1048576 bytes

does NOT by itself prove that the physical Flash is only 1 MB.

The verification program directly queries the Flash chip and should
report:

    Flash size : 16 MB

This runtime result is used to verify the physical Flash capacity.


13. IMPORTANT NOTE ABOUT PSRAM
==============================

The N16R8 configuration uses:

    8 MB Octal PSRAM

Selecting Octal Mode in ESP-IDF menuconfig is therefore essential.

If the verification program reports:

    PSRAM detected : NO

check:

    Component config
        -> ESP PSRAM
            -> Initialize PSRAM related hardware
            -> Initialize PSRAM during startup
            -> Octal Mode PSRAM
            -> Auto-detect PSRAM type

Then save the configuration, rebuild, upload, and test again.


14. VERIFICATION PURPOSE
========================

This example is intended to provide a simple hardware-level
verification of the custom PlatformIO board definition.

A successful verification demonstrates that the configuration can:

    - Build using PlatformIO and ESP-IDF
    - Upload firmware to the ESP32-S3
    - Detect the physical 16 MB Flash
    - Initialize and detect the physical 8 MB Octal PSRAM

The verification does not test external peripherals, sensors,
GPIO functionality, UART, I2C, SPI, Wi-Fi, Bluetooth, or display
interfaces.
