#ifndef STORAGE_H
#define STORAGE_H

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

void setupStorage();
void readCSVData();
void littleFSStorage();

#endif