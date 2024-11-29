#include "GlobalVariables.h"
#include<TFT_eSPI.h>
#include <TFT_eWidget.h>
#include <ESPAsyncWebServer.h>
#include <SD.h>
#include <SPI.h>

#include <PNGdec.h>
#include <LittleFS.h>

String commandID;
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