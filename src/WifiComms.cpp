#include <Arduino.h>
#include <Stream.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <AsyncTCP.h>
#include <HTTPClient.h>
#include <FS.h>
#include <ESPmDNS.h>

#include <SD.h>
#include <SPI.h>

#include "WiFiManager.h" 
WiFiManager wm;
#define WEBSERVER_H
#include "ESPAsyncWebServer.h"
#include <Wire.h> 

#include "LittleFS.h"

#include "GlobalVariables.h"
#include "SensorsReading.h"
#include "Storage.h"

char* ssid = "AirQo Device";
char* password = "password";

void getTime() {
    HTTPClient http;
    int httpCode = -1;
    String created_at;

    while (httpCode <= 0) {
        http.begin("http://worldtimeapi.org/api/timezone/Etc/UTC");
        httpCode = http.GET();

        if (httpCode > 0) {
            String payload = http.getString();
            int datetimeIndex = payload.indexOf("\"datetime\":\"") + 12;
            created_at = payload.substring(datetimeIndex, datetimeIndex + 19);
            Serial.println(created_at);
        } else {
            Serial.println("Error getting time from API, retrying...");
            delay(1000); // Wait for 1 second before retrying
        }

        http.end();
    }
}

bool checkWifiConnection(){
    if(WiFi.status() != WL_CONNECTED){
        Serial.println("Wifi Disconnected");
        return false;
    }
    return true;
}

void wifiManagerSetup() {
    // wm.resetSettings();
    if( !wm.autoConnect(ssid, password) ) {
        Serial.println("Failed to connect");
        // delay(60000);
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

void fileSytem(){
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(LittleFS, "/index.html", "text/html");
    });

    // Serve file tree as JSON
    server.on("/filetree", HTTP_GET, [](AsyncWebServerRequest *request) {
    String path = "/";
    if (request->hasParam("path")) {
        path = request->getParam("path")->value();
    }

    // Open the requested directory
    File root = SD.open(path);
    if (!root || !root.isDirectory()) {
        request->send(404, "application/json", "{\"error\": \"Path not found or is not a directory\"}");
        return;
    }

    // Determine parent directory
    String parent = "/";
    if (path != "/") {
        int lastSlash = path.lastIndexOf('/');
        parent = path.substring(0, lastSlash);
        if (parent == "") parent = "/";
    }

    // Create JSON structure
    String json = "{ \"parent\": \"" + parent + "\", \"folders\": [";
    String files = "], \"files\": [";

    File file = root.openNextFile();
    while (file) {
        String fileName = String(file.name());
        
        // Ensure filenames are properly stripped of the current directory
        if (fileName.startsWith(path) && path != "/") {
            fileName = fileName.substring(path.length());
        }
        if (fileName.startsWith("/")) {
            fileName = fileName.substring(1);
        }

        // Skip hidden/system files
        if (fileName.startsWith(".")) {
            file = root.openNextFile();
            continue;
        }

        // Add to folders or files
        if (file.isDirectory()) {
            if (json != "{ \"parent\": \"" + parent + "\", \"folders\": [") json += ",";
            json += "\"" + fileName + "/\"";
        } else {
            if (files != "], \"files\": [") files += ",";
            files += "\"" + fileName + "\"";
        }
        file = root.openNextFile();
    }

    json += files + "] }";
    request->send(200, "application/json", json);
});

    // Handle file download
    server.on("/download", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (request->hasParam("path")) {
        String filePath = request->getParam("path")->value();

        // Ensure the path starts with a "/"
        if (!filePath.startsWith("/")) {
            filePath = "/" + filePath;
        }

        File downloadFile = SD.open(filePath);
        if (downloadFile && !downloadFile.isDirectory()) {
            request->send(SD, filePath, "application/octet-stream");
            downloadFile.close();
        } else {
            request->send(404, "text/plain", "File not found or is a directory");
        }
    } else {
        request->send(400, "text/plain", "File parameter missing");
    }
});


    server.begin();
}

//server based data upload
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