#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#include <Arduino.h>
#include<TFT_eSPI.h>
#include <TFT_eWidget.h>
#include <ESPAsyncWebServer.h>

#include <PNGdec.h>
#include <LittleFS.h>
#include <SD.h>

extern String commandID;
extern String deviceName;
extern String channelID;
extern String apiKey;
extern String sensor1_2;
extern String sensor1_10;
extern String sensor2_2;
extern String sensor2_10;
extern String latitude;
extern String longitude;
extern String battery_voltage;
extern String extra_data;
extern String discharge_rate;
extern String soc;
extern String battery_voltage1;
extern String external_pressure;
extern String altitude;
extern String external_temperature;
extern String external_humidity;
extern String internal_temperature;
extern String internal_humidity;
extern float dataState;
extern String serverName;
extern int8_t setComms;
extern int8_t setData;
struct pms5003data {
  uint16_t framelen;
  uint16_t pm10_standard, pm25_standard, pm100_standard;
  uint16_t pm10_env, pm25_env, pm100_env;
  uint16_t particles_03um, particles_05um, particles_10um, particles_25um, particles_50um, particles_100um;
  uint16_t unused;
  uint16_t checksum;
};
extern struct pms5003data pmdata;
extern TFT_eSPI tft;
extern AsyncWebServer server;
extern SPIClass spiSD;

// Serial Port connections for PM2.5 Sensor
#define RXD2 16 // ==> sensor TXD
#define TXD2 17 // ==> sensor RXD

//sd card functionality
const int SD_MISO = 19;
const int SD_MOSI = 23;
const int SD_SCK = 22;
const int SD_CS = 15;

#define MAX_DATA_POINTS 15
extern float pm25_data[MAX_DATA_POINTS];
extern int data_count;

extern GraphWidget gr;

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

#define FlashFS LittleFS

extern PNG png;
extern File pngfile;
#define MAX_IMAGE_WIDTH 480 

#define TFT_BG_COLOR 0xF7BE // Hex color 0xFAFCFF in RGB565 format

extern int16_t xpos;
extern int16_t ypos;

// TEXT ALIGNMENT
#define AA_FONT_SMALL "NotoSans20"
#define AA_FONT_LARGE "NotoSans36"
#define AA_FONT_TINNY "NotoSans15"
#define AA_FONT_MEDIUM "NotoSans30"
extern bool font_missing;

// Joystick pin definitions
#define VRx_PIN 34
#define VRy_PIN 35
#define SW_PIN 0 

//menu button
extern TFT_eSPI_Button button;
extern std::vector<TFT_eSPI_Button> mainButtons;
extern std::vector<std::vector<TFT_eSPI_Button>> subButtons;
extern const std::vector<const char*> mainButtonLabels;
extern const std::vector<std::vector<const char*>> subButtonLabels;

// Global state variables
extern int currentSelection ;
extern int subMenuSelection ;
extern bool selectPressed ;
extern bool isMainMenu ;
extern int activeMainMenu ;

// Button properties
#define BUTTON_WIDTH  120
#define BUTTON_HEIGHT 50
#define BUTTON_GAP    20
#define BUTTON_COLOR  TFT_BLUE
#define SELECT_COLOR  TFT_WHITE

// Center positions
#define CENTER_X 1947
#define CENTER_Y 1891
#define TOLERANCE 1200

#endif
