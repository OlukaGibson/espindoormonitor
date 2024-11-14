#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#include <Arduino.h>
#include<TFT_eSPI.h>
#include <ESPAsyncWebServer.h>

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

#endif
