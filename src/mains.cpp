#include <Arduino.h>
#include <WiFi.h>

#include "LittleFS.h"

#include "GlobalVariables.h"
#include "SensorsReading.h"
#include "LCDDisplay.h"
#include "WifiComms.h"
#include "EspnowComms.h"
#include "Storage.h"

// #include <SPI.h>
#include <TFT_eSPI.h>


//this is for wifif and lcd related tasks
void Task1code( void * pvParameters ){
    Serial.println("Task1 running on core ");
    Serial.println(xPortGetCoreID());
    lcdSetup();
    // if(!checkWifiConnection()){
    //     wifiManagerSetup();
    // }
    // wifiManagerSetup();
    // serverRoutes();
    joystickSetup();
    for(;;){
        displayHomeScreen();
        displayMenu();
        displayIndoorSensorData();
        displayMenu();
    }
}

//this is for storage and sensor and data upload reading related tasks
void Task2code( void * pvParameters ){
    Serial.println("Task2 running on core ");
    Serial.println(xPortGetCoreID());
    setupStorage();
    // if(!checkWifiConnection()){
    //     wifiManagerSetup();
    // }
    // // if (checkWifiConnection()){
    //     getTime();
    // // }
    for(;;){
        // cloudDataUpload();
        writeCSVData();
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

void setup() {
    Serial.begin(115200);
    delay(10);
    Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2);
    delay(10);
    littleFSStorage();
    fontSetup();
    xTaskCreatePinnedToCore(
        Task1code,   /* Task function. */
        "Task1",     /* name of task. */
        10000,       /* Stack size of task */
        NULL,        /* parameter of the task */
        1,           /* priority of the task */
        &Task1,      /* Task handle to keep track of created task */
        0);          /* pin task to core 0 */
    xTaskCreatePinnedToCore(
        Task2code,   /* Task function. */
        "Task2",     /* name of task. */
        10000,       /* Stack size of task */
        NULL,        /* parameter of the task */
        1,           /* priority of the task */
        &Task2,      /* Task handle to keep track of created task */
        1);          /* pin task to core 1 */
}

void loop() {}