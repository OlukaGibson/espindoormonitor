#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

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


// Serial Port connections for PM2.5 Sensor
#define RXD2 16 // ==> sensor TXD
#define TXD2 17 // ==> sensor RXD

boolean readPMSdata(Stream *s);

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2);
  tft.init();
  tft.setRotation(1); // rotation of the screen 
  tft.fillScreen(TFT_WHITE); // white color
}

struct pms5003data {
  uint16_t framelen;
  uint16_t pm10_standard, pm25_standard, pm100_standard;
  uint16_t pm10_env, pm25_env, pm100_env;
  uint16_t particles_03um, particles_05um, particles_10um, particles_25um, particles_50um, particles_100um;
  uint16_t unused;
  uint16_t checksum;
};
struct pms5003data pmdata;

void loop() {
  if (readPMSdata(&Serial1)) {
    // Print data to Serial Monitor
    Serial.println("======= PMS5003 DATA =======");
    Serial.print("PM 1.0: "); Serial.print(pmdata.pm10_standard);
    Serial.print(", PM 2.5: "); Serial.print(pmdata.pm25_standard);
    Serial.print(", PM 10: "); Serial.println(pmdata.pm100_standard);
    Serial.println("===========================");

    // Clear screen with white background
    tft.fillScreen(TFT_WHITE); 

    // Set label text color and size
    tft.setTextColor(TFT_BLACK);
    tft.setTextSize(1);

    // Define the middle of the screen and spacing for the circles
    int screenMidY = tft.height() / 2;    // Middle of the screen vertically
    int circleRadius = 40;                // Increase circle size
    int pm1_x = 60;                       // Position for PM 1.0 on the left
    int pm25_x = tft.width() / 2;         // Position for PM 2.5 in the middle
    int pm10_x = tft.width() - 60;        // Position for PM 10 on the right

    // Draw labels above each circle
    tft.setCursor(pm1_x - 15, screenMidY - circleRadius - 20);
    tft.println("PM 1.0");

    tft.setCursor(pm25_x - 15, screenMidY - circleRadius - 20);
    tft.println("PM 2.5");

    tft.setCursor(pm10_x - 15, screenMidY - circleRadius - 20);
    tft.println("PM 10");

    // Draw circles with values
    tft.fillCircle(pm1_x, screenMidY, circleRadius, TFT_GREEN); // PM 1.0 circle
    tft.setCursor(pm1_x - 10, screenMidY - 5);
    tft.setTextColor(TFT_BLACK, TFT_GREEN); // Black text with green background
    tft.setTextSize(3);                     // Larger text size for values
    tft.print(pmdata.pm10_standard);

    tft.fillCircle(pm25_x, screenMidY, circleRadius, TFT_YELLOW); // PM 2.5 circle
    tft.setCursor(pm25_x - 10, screenMidY - 5);
    tft.setTextColor(TFT_BLACK, TFT_YELLOW); // Black text with yellow background
    tft.print(pmdata.pm25_standard);

    tft.fillCircle(pm10_x, screenMidY, circleRadius, TFT_RED); // PM 10 circle
    tft.setCursor(pm10_x - 10, screenMidY - 5);
    tft.setTextColor(TFT_BLACK, TFT_RED);   // Black text with red background
    tft.print(pmdata.pm100_standard);

    // Reset text size and color for future use
    tft.setTextSize(1);
    tft.setTextColor(TFT_BLACK);
  }
  delay(1000);
}


boolean readPMSdata(Stream *s){
  if (! s->available()){
    return false ;
  }
  
  // Read a byte at a time until we get to the special '0x42' start-byte
  if (s->peek() != 0x42) {
    s->read();
    return false;
  }

  // Now read all 32 bytes
  if (s->available() < 32) {
    return false;
  }

  uint8_t buffer[32];
  uint16_t sum = 0;
  s->readBytes(buffer, 32);

  // get checksum ready
  for (uint8_t i = 0; i < 30; i++) {
    sum += buffer[i];
  }

  // The data comes in endian'd, this solves it so it works on all platforms
  uint16_t buffer_u16[15];
  for (uint8_t i = 0; i < 15; i++) {
    buffer_u16[i] = buffer[2 + i * 2 + 1];
    buffer_u16[i] += (buffer[2 + i * 2] << 8);
  }

  // put it into a nice struct :)
  memcpy((void *)&pmdata, (void *)buffer_u16, 30);

  if (sum != pmdata.checksum) {
    Serial.println("Checksum failure");
    return false;
  }

  // success!
  return true;

}