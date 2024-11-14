#include <Arduino.h>
#include <Stream.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <AsyncTCP.h>
#include <HTTPClient.h>
#include <FS.h>
#include <ESPmDNS.h>

#include "WiFiManager.h" 
WiFiManager wm;
#define WEBSERVER_H
#include "ESPAsyncWebServer.h"
#include <Wire.h> 

#include "LittleFS.h"

#include "GlobalVariables.h"
#include "SensorsReading.h"

const char* ssid = "AirQo Device";
const char* password = "password";


void wifiManagerSetup() {
    // wm.resetSettings();
    if( !wm.autoConnect(ssid, password) ) {
        Serial.println("Failed to connect");
        delay(60000);
        // ESP.restart();
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(deviceName);
    Serial.print("IP address: ");
    Serial.print(WiFi.localIP());
    Serial.println(":8080");
}

void serverRoutes(){
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/index.html", "text/html");
    });
    server.on("/pm1", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", String(pmdata.pm10_standard).c_str());
    });
    server.on("/pm25", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", String(pmdata.pm25_standard).c_str());
    });
    server.on("/pm10", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", String(pmdata.pm100_standard).c_str());
    });
    server.on("/dataState", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", String(dataState).c_str());
    });
    server.begin();
}

void cloudDataUpload() {
    String url = String(serverName) + "?api_key=" + String(apiKey) + "&field1=" + String(sensor1_2) +
                 "&field2=" + String(sensor1_10) + "&field3=" + String(sensor2_2) +
                 "&field4=" + String(sensor2_10) + "&field5=" + String(latitude) +
                 "&field6=" + String(longitude) + "&field7=" + String(battery_voltage) +
                 "&field8=" + String(extra_data);
    WiFiClient client;
    HTTPClient http;
    Serial.println("Sending data to ThingSpeak...");
    Serial.println(url);
    http.begin(client, url);
    int httpResponseCode = http.GET();
    
    if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println("HTTP Response code: " + String(httpResponseCode));
        Serial.println(response);
    } else {
        Serial.print("Error sending data to ThingSpeak. HTTP Response code: ");
        Serial.println(httpResponseCode);
    }

    http.end();
}

void cloudFileUpload(){}



// int8_t pm1 = random(0, 10);
// int8_t pm25 = random(0, 10);
// int8_t pm10 = random(0, 10);