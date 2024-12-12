// #include <Arduino.h>
// #include <WiFi.h>
// #include <vector> // Include vector library

// // Include the SD library
// #include <SD.h>

// #include "GlobalVariables.h"
// #include "SensorsReading.h"
// #include "LCDDisplay.h"
// #include "wifiComms.h"
// #include "EspnowComms.h"
// #include "Storage.h"

// // #include <SPI.h>
// #include <TFT_eSPI.h>
// #include <TFT_eWidget.h>
// #include "time.h"

// // Wi-Fi credentials
// const char* ssid = "Airqo";
// const char* password = "A1rq0@2022";

// // NTP Server details
// const char* ntpServer = "pool.ntp.org";
// const long gmtOffset_sec = 0;  // Adjust based on your timezone
// const int daylightOffset_sec = 0; // Daylight savings (if applicable)

// File logFile;

// void setup() {
//   Serial.begin(115200);

//   // Initialize Wi-Fi
//   WiFi.begin(ssid, password);
//   Serial.print("Connecting to Wi-Fi");
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println("Connected!");

//   // Initialize NTP
//   configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
//   Serial.println("Time synchronized via NTP.");

//   // Initialize SD card
//   if (!SD.begin(SD_CS)) {
//     Serial.println("Failed to initialize SD card.");
//     return;
//   }
//   Serial.println("SD card initialized.");

//   // Open or create a CSV file
//   logFile = SD.open("/data.csv", FILE_WRITE);
//   if (logFile) {
//     logFile.println("Timestamp,Data1,Data2"); // Add header row
//     logFile.close();
//   } else {
//     Serial.println("Failed to create file.");
//   }
// }

// void loop() {
//   logFile = SD.open("/data.csv", FILE_APPEND);
//   if (logFile) {
//     // Get current time
//     struct tm timeinfo;
//     if (!getLocalTime(&timeinfo)) {
//       Serial.println("Failed to obtain time");
//       return;
//     }
//     char timestamp[30];
//     strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &timeinfo);

//     // Log data
//     int data1 = random(0, 100);
//     int data2 = random(100, 200);
//     logFile.printf("%s,%d,%d\n", timestamp, data1, data2);
//     logFile.close();

//     Serial.printf("Logged: %s,%d,%d\n", timestamp, data1, data2);
//   } else {
//     Serial.println("Failed to open file for appending.");
//   }

//   delay(5000); // Log every 5 seconds
// }
