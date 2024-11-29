#include <SD.h>
#include <SPI.h>
#include "GlobalVariables.h"

void setupStorage() {
    spiSD.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
    if (!SD.begin(SD_CS, spiSD)) {
        Serial.println("Card Mount Failed");
        return;
    }
    Serial.println("Card Mount Success");
    File root = SD.open("/");
    while (root) {
        Serial.println(root.name());
        root = root.openNextFile();
    }
}

void littleFSStorage() {
    if (!LittleFS.begin()) {
        Serial.println("LittleFS mount failed");
        return;
    }
    Serial.println("LittleFS mount success");
}

void readCSVData() {
  // Open the file on SD card
  File dataFile = SD.open("/data.csv", FILE_READ);

  if (!dataFile) {
    Serial.println("Error opening data.csv!");
    return;
  }

  data_count = 0;

  // Skip the header line
  String line = dataFile.readStringUntil('\n');

  while (dataFile.available() && data_count < MAX_DATA_POINTS) {
    line = dataFile.readStringUntil('\n');
    int commaIndex = line.indexOf(',');
    if (commaIndex > 0) {
      String pm25_str = line.substring(commaIndex + 1);
      pm25_data[data_count] = pm25_str.toFloat();
      Serial.print("Read PM2.5 value: "); // Debug print
      Serial.println(pm25_data[data_count]); // Debug print
      data_count++;
    }
  }
  dataFile.close();
}
