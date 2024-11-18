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

