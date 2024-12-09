#ifndef LCDDISPLAY_H
#define LCDDISPLAY_H

void lcdSetup();
void displayData();
void displayHomeScreen();
void displayIndoorSensorData();
void sensorCharts(unsigned int x, unsigned int y, unsigned short bgColor);
void fontSetup();
void menuDisplay();

#endif