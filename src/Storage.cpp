#include <SD.h>
#include <SPI.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "GlobalVariables.h"
#include "WifiComms.h"
#include "SensorsReading.h"

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
      Serial.print("Read PM2.5 value: ");
      Serial.println(pm25_data[data_count]);
      data_count++;
    }
  }
  dataFile.close();
}


void writeCSVData(){
  if (readPMSdata(&Serial1)) {
    currentMillis = millis();
    runtime = currentMillis - startTime;
    
    // Open the file on SD card
    File dataFile = SD.open("/data.csv", FILE_APPEND);

    if (!dataFile) {
      Serial.println("Error opening data.csv for writing!");
      return;
    }

    // Write the data to the file

    dataFile.print(created_at);
    dataFile.print(",");
    dataFile.print(runtime);
    dataFile.print(",");
    dataFile.print(pmdata.pm10_standard);
    dataFile.print(",");
    dataFile.print(pmdata.pm25_standard);
    dataFile.print(",");
    dataFile.println(pmdata.pm100_standard);

    dataFile.close();
    Serial.println("Data written to data.csv");
  } 
}

  
  // if(checkWifiConnection){}

// void writeCSVData() {

//   // Open the file on SD card
//   File dataFile = SD.open("/data.csv", FILE_APPEND);

//   if (!dataFile) {
//     Serial.println("Error opening data.csv for writing!");
//     return;
//   }

//   // Write the data to the file
//   dataFile.print(created_at);
//   dataFile.print(",");
//   dataFile.print(pmdata.pm10_standard);
//   dataFile.print(",");
//   dataFile.print(pmdata.pm25_standard);
//   dataFile.print(",");
//   dataFile.println(pmdata.pm100_standard);

//   dataFile.close();
//   Serial.println("Data written to data.csv");
// }