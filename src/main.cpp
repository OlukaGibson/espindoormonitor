// #include <Arduino.h>
// #include <WiFi.h>

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

// // GraphWidget gr = GraphWidget(&tft);  // Graph widget
// // // SPIClass spiSD(VSPI);                // SPI for SD card

// // #define MAX_DATA_POINTS 50
// // float pm25_data[MAX_DATA_POINTS];
// // int data_count = 0;

// void setupSDCard() {
//   // Initialize SPI for SD card
//   spiSD.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
  
//   // Mount SD card
//   if (!SD.begin(SD_CS, spiSD)) {
//     Serial.println("Card Mount Failed");
//     while (1); // Stop execution if SD card fails
//   }
//   Serial.println("Card Mount Success");

//   // List files in the root directory
//   File root = SD.open("/");
//   while (root) {
//     Serial.println(root.name());
//     root = root.openNextFile();
//   }
// }



// void plotBarGraphs() {
//   tft.fillScreen(TFT_WHITE);
  
//   // Define graph area
//   gr.createGraph(200, 150, tft.color565(220, 220, 220)); // Light grey background
//   gr.setGraphScale(0.0, data_count, 0.0, 100.0); // X: 0 to data_count, Y: 0 to 100
//   gr.setGraphGrid(0.0, 5.0, 0.0, 10.0, TFT_LIGHTGREY); // Grid every 5 points and 10 units
//   gr.drawGraph(40, 10); // Draw graph at (40, 10)

//   // Draw bars
//   for (int i = 0; i < data_count; i++) {
//     float barHeight = pm25_data[i];
//     int x = gr.getPointX(i);          // Map x to graph pixel
//     int y = gr.getPointY(0.0);        // Bottom of the graph
//     int barY = gr.getPointY(barHeight); // Top of the bar
//     tft.fillRect(x - 2, barY, 4, y - barY, TFT_BLUE); // Draw bar
//   }

//   // Draw x-axis labels
//   for (int i = 0; i < data_count; i++) {
//     tft.setTextDatum(TC_DATUM);
//     tft.setTextColor(TFT_BLACK, TFT_WHITE);
//     tft.drawNumber(i, gr.getPointX(i), gr.getPointY(0.0) + 5);
//   }

//   // Draw y-axis labels
//   for (int i = 0; i <= 100; i += 10) {
//     tft.setTextDatum(MR_DATUM);
//     tft.setTextColor(TFT_BLACK, TFT_WHITE);
//     tft.drawNumber(i, gr.getPointX(0.0) - 5, gr.getPointY(i));
//   }
// }

// void setup() {
//   Serial.begin(115200);
//   delay(2000);

//   // Initialize TFT
//   tft.begin();
//   tft.setRotation(1);

//   // Setup SD card
//   setupSDCard();

//   // Read data and plot graph
//   readCSVDatas();
//   plotBarGraphs();
// }

// void loop() {
//   // No continuous updates for now
// }