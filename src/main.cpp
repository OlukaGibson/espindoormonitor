#include <Arduino.h>
#include <WiFi.h>

#include "LittleFS.h"

#include "GlobalVariables.h"
#include "SensorsReading.h"
#include "LCDDisplay.h"
#include "wifiComms.h"
#include "EspnowComms.h"

// #include <SPI.h>
#include <TFT_eSPI.h>

// Serial Port connections for PM2.5 Sensor
#define RXD2 16 // ==> sensor TXD
#define TXD2 17 // ==> sensor RXD

// Screen data imposed
#define TFT_GREY 0x5AEB // New colour

#define TFT_DC   18
#define TFT_CS   33
#define TFT_RST  32
#define TFT_RD    2
#define TFT_WR    4

#define TFT_D0   12
#define TFT_D1   13
#define TFT_D2   26
#define TFT_D3   25
#define TFT_D4   21
#define TFT_D5    5
#define TFT_D6   27
#define TFT_D7   14

#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF

#define SMOOTH_FONT



void setup() {
    Serial.begin(115200);
    delay(10);
    Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2);
    delay(10);
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_WHITE);
    delay(10);
    wifiManagerSetup();
    if (!LittleFS.begin()){
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }
    // MDNS.begin("esp32");
    // Serial.print("mDNS responder started at esp32.local:8080");
    Serial.println("IP address: ");
    Serial.print(WiFi.localIP());
    Serial.print(":8080");
    Serial.println("");
    serverRoutes();
}

void loop() {
    // MDNS.update();
    displayData();
    // cloudDataUpload();
    delay(1000);
}