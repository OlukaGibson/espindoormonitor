#include <Arduino.h>
#include <Stream.h>
#include "GlobalVariables.h"
#include "SensorsReading.h"


#include<SPI.h>
#include<TFT_eSPI.h>

void lcdSetup(){
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_WHITE);
    delay(10);
}

void displayData(){
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

void displayHomeScreen(){}

void displayIndoorSensorData(){}

void displayOutdoorSensorData(){}

void displayIndoorVsOutdoorSensorData(){}