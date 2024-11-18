// #include <Arduino.h>
// #include <WiFi.h>

// #include "LittleFS.h"

// #include "GlobalVariables.h"
// #include "SensorsReading.h"
// #include "LCDDisplay.h"
// #include "wifiComms.h"
// #include "EspnowComms.h"
// // testing the sd card functionality
// #include <SD.h>
// #include <SPI.h>
// // testing the sd card functionality


// // testing the sd card functionality
// const int SD_MISO = 19;
// const int SD_MOSI = 23;
// const int SD_SCK = 22;
// const int SD_CS = 15;
// // testing the sd card functionality

// // testing the sd card functionality
// SPIClass spiSD(HSPI);
// // testing the sd card functionality


// void setup() {
//     // testing the sd card functionality
//     Serial.begin(115200);
//     delay(10);

//     Serial.println("Connecting to WiFi");
//     WiFi.begin("Airqo", "A1rq0@2022");

//     while (WiFi.status() != WL_CONNECTED) {
//         delay(500);
//         Serial.print(".");
//     }
//     Serial.println("Connected to WiFi");
//     Serial.print("IP Address: ");
//     Serial.println(WiFi.localIP());

//     spiSD.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
//     if (!SD.begin(SD_CS, spiSD)) {
//         Serial.println("Card Mount Failed");
//         return;
//     }
//     Serial.println("Card Mount Success");

//     server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
//         String html = "<html><body><h1>SD Card File List</h1><ul>";
//         File root = SD.open("/");
//         File file = root.openNextFile();
//         while (file) {
//             String fileName = String(file.name());
//             html += "<li><a href=\"/download?file=" + fileName + "\">" + fileName + "</a></li>";
//             file = root.openNextFile();
//     }
//     html += "</ul></body></html>";
//     request->send(200, "text/html", html);
//   });

//     // Handle file download
//     server.on("/download", HTTP_GET, [](AsyncWebServerRequest *request) {
//         if (request->hasParam("file")) {
//               String fileName = request->getParam("file")->value();
//             File downloadFile = SD.open("/" + fileName);
//             if (downloadFile) {
//                 request->send(SD, "/" + fileName, "application/octet-stream");
//                 downloadFile.close();
//             } else {
//                 request->send(404, "text/plain", "File not found");
//             }
//         } else {
//             request->send(400, "text/plain", "File parameter missing");
//         }
//     });

//     // Start the server
//     server.begin();
//     // testing the sd card functionality
// }

// void loop() {
// }