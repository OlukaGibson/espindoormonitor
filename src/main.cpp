#include <Arduino.h>
#include <WiFi.h>

#include "LittleFS.h"

#include "GlobalVariables.h"
#include "SensorsReading.h"
#include "LCDDisplay.h"
#include "wifiComms.h"
#include "EspnowComms.h"
#include "Storage.h"

// #include <SPI.h>
#include <TFT_eSPI.h>


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
    setupStorage();
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
    // serverRoutes();
    fileSytem();
}

void loop() {
    // // MDNS.update();
    // displayData();
    // cloudDataUpload();
    // delay(1000);
}