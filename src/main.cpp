// #include <Arduino.h>
// #include <WiFi.h>

// #include "LittleFS.h"

// #include "GlobalVariables.h"
// #include "SensorsReading.h"
// #include "LCDDisplay.h"
// #include "wifiComms.h"
// #include "EspnowComms.h"
// #include "Storage.h"

// // #include <SPI.h>
// #include <TFT_eSPI.h>


// void setup() {
//     Serial.begin(115200);
//     delay(10);
//     Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2);
//     delay(10);
//     lcdSetup();
//     wifiManagerSetup();
//     setupStorage();
//     if (!LittleFS.begin()){
//         Serial.println("An Error has occurred while mounting LittleFS");
//         return;
//     }
//     // MDNS.begin("esp32");
//     // Serial.print("mDNS responder started at esp32.local:8080");
//     serverRoutes();
//     // fileSytem();
// }

// void loop() {
//     // // MDNS.update();
//     displayData();
//     cloudDataUpload();
//     delay(100);
// }