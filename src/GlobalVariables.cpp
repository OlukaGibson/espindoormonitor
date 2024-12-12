#include "GlobalVariables.h"
#include<TFT_eSPI.h>
#include <TFT_eWidget.h>
#include <ESPAsyncWebServer.h>
#include <SD.h>
#include <SPI.h>

#include <PNGdec.h>
#include <LittleFS.h>

//Task management functions
TaskHandle_t Task1;
TaskHandle_t Task2;

// variables for control
String commandID;
String created_at;
String deviceName;
String channelID;
String apiKey;
String sensor1_2;
String sensor1_10;
String sensor2_2;
String sensor2_10;
String latitude;
String longitude;
String battery_voltage;
String extra_data;
String discharge_rate;
String soc;
String battery_voltage1;
String external_pressure;
String altitude;
String external_temperature;
String external_humidity;
String internal_temperature;
String internal_humidity;
float dataState = 0;
String serverName = "http://api.thingspeak.com/update";
int8_t setComms;
int8_t setData = 0;
struct pms5003data pmdata;
TFT_eSPI tft = TFT_eSPI();
AsyncWebServer server(8080);
SPIClass spiSD(HSPI);

GraphWidget gr = GraphWidget(&tft);

float pm25_data[MAX_DATA_POINTS];
int data_count = 0;
PNG png;
File pngfile;
int16_t xpos = 0;
int16_t ypos = 0;

bool font_missing = false;

// menu button
TFT_eSPI_Button button;
std::vector<TFT_eSPI_Button> mainButtons;
std::vector<std::vector<TFT_eSPI_Button>> subButtons;
const std::vector<const char*> mainButtonLabels = {"Wifi", "Devices", "Files", "Settings"};
const std::vector<std::vector<const char*>> subButtonLabels = {
  {"room1"},
  {"device1", "device2"},
  {"file1", "file2", "file3"},
  {"setting1", "setting2", "setting3"}
};

// Global state variables
int currentSelection = 0; // Current selected button index
int subMenuSelection = 0; // Current selected submenu button index
bool selectPressed = false;
bool isMainMenu = true;   // Tracks if the user is in the main menu
int activeMainMenu = -1;  // Tracks which main menu button was selected
volatile bool buttonPressed = false; // Flag to track button press

unsigned long startTime;
unsigned long currentMillis;
unsigned long runtime;