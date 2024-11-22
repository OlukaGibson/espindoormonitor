void wegitCode(){
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
// #include <TFT_eWidget.h>

// MeterWidget   amps  = MeterWidget(&tft);
// MeterWidget   volts = MeterWidget(&tft);
// MeterWidget   ohms  = MeterWidget(&tft);

// #define LOOP_PERIOD 1000

// void setup(){
//     tft.init();
//     tft.setRotation(1);
//     tft.fillScreen(TFT_WHITE);
//     Serial.begin(115200);

//     amps.setZones(75, 100, 50, 75, 25, 50, 0, 25);
//     amps.analogMeter(0, 0, 2.0, "mA", "0", "0.5", "1.0", "1.5", "2.0");

//     volts.setZones(0, 100, 25, 75, 0, 0, 40, 60);
//     volts.analogMeter(0, 128, 10.0, "V", "0", "2.5", "5", "7.5", "10"); 

//     ohms.analogMeter(0, 256, 100, "R", "0", "", "50", "", "100");
// }

// float mapValue(float ip, float ipmin, float ipmax, float tomin, float tomax){
//   return tomin + (((tomax - tomin) * (ip - ipmin))/ (ipmax - ipmin));
// }

// void loop(){
//   static int d = 0;
//   static uint32_t updateTime = 0;  

//   if (millis() - updateTime >= LOOP_PERIOD) {
//     updateTime = millis();

//     d += 4; if (d > 360) d = 0;

//     // Create a Sine wave for testing, value is in range 0 - 100
//     float value = 50.0 + 50.0 * sin((d + 0) * 0.0174532925);

//     float current;
//     current = mapValue(value, (float)0.0, (float)100.0, (float)0.0, (float)2.0);
//     //Serial.print("I = "); Serial.print(current);
//     amps.updateNeedle(current, 0);

//     float voltage;
//     voltage = mapValue(value, (float)0.0, (float)100.0, (float)0.0, (float)10.0);
//     //Serial.print(", V = "); Serial.println(voltage);
//     volts.updateNeedle(voltage, 0);
    
//     float resistance;
//     resistance = mapValue(value, (float)0.0, (float)100.0, (float)0.0, (float)100.0);
//     //Serial.print(", R = "); Serial.println(resistance);
//     ohms.updateNeedle(resistance, 0);
//   }
// }

}

void setupcode(){
//     #include <Arduino.h>
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
// #include <TFT_eWidget.h>
// #define FileSys LittleFS

// // Include the PNG decoder library
// #include <PNGdec.h>

// PNG png;
// File pngfile;
// #define MAX_IMAGE_WIDTH 480 // Increase the width to accommodate your image

// int16_t xpos = 0;
// int16_t ypos = 0;

// void setup(){
//   Serial.begin(115200);
//   Serial.println("\n\n Using the PNGdec library");

//   // Initialise FS
//   if (!FileSys.begin()) {
//     Serial.println("LittleFS initialisation failed!");
//     while (1) yield(); // Stay here twiddling thumbs waiting
//   }

//   // Initialise the TFT
//   tft.begin();
//   tft.setRotation(1); // Set rotation to 1
//   tft.fillScreen(TFT_WHITE);
//   Serial.println("\r\nInitialisation done.");
// }

// void pngDraw(PNGDRAW *pDraw) {
//   uint16_t lineBuffer[MAX_IMAGE_WIDTH];
//   png.getLineAsRGB565(pDraw, lineBuffer, PNG_RGB565_BIG_ENDIAN, 0xffffffff);
//   tft.pushImage(xpos, ypos + pDraw->y, pDraw->iWidth, 1, lineBuffer);
// }

// void * pngOpen(const char *filename, int32_t *size) {
//   Serial.printf("Attempting to open %s\n", filename);
//   pngfile = FileSys.open(filename, "r");
//   *size = pngfile.size();
//   return &pngfile;
// }

// void pngClose(void *handle) {
//   File pngfile = *((File*)handle);
//   if (pngfile) pngfile.close();
// }

// int32_t pngRead(PNGFILE *page, uint8_t *buffer, int32_t length) {
//   if (!pngfile) return 0;
//   page = page; // Avoid warning
//   return pngfile.read(buffer, length);
// }

// int32_t pngSeek(PNGFILE *page, int32_t position) {
//   if (!pngfile) return 0;
//   page = page; // Avoid warning
//   return pngfile.seek(position);
// }

// void loop()
// {
//   // Open the specific image file
//   String strname = "/gibson.png";
//   Serial.println(strname);
//   // Pass support callback function names to library
//   int16_t rc = png.open(strname.c_str(), pngOpen, pngClose, pngRead, pngSeek, pngDraw);
//   if (rc == PNG_SUCCESS) {
//     tft.startWrite();
//     Serial.printf("image specs: (%d x %d), %d bpp, pixel type: %d\n", png.getWidth(), png.getHeight(), png.getBpp(), png.getPixelType());
//     uint32_t dt = millis();
//     if (png.getWidth() > MAX_IMAGE_WIDTH) {
//       Serial.println("Image too wide for allocated line buffer size!");
//     }
//     else {
//       rc = png.decode(NULL, 0);
//       png.close();
//     }
//     tft.endWrite();
//     // How long did rendering take...
//     Serial.print(millis()-dt); Serial.println("ms");
//   }
//   delay(3000);
//   tft.fillScreen(random(0x10000));
// }


}