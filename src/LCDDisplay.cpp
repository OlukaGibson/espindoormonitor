#include <Arduino.h>
#include <Stream.h>
#include "GlobalVariables.h"
#include "SensorsReading.h"
#include "LCDDisplay.h"
#include "Storage.h"

#include<SPI.h>
#include<TFT_eSPI.h>
#include <TFT_eWidget.h>
#include <PNGdec.h>
#include <LittleFS.h>
#include <SD.h>

uint16_t radius = 5;

void pngDraw(PNGDRAW *pDraw);
void * pngOpen(const char *filename, int32_t *size);
void pngClose(void *handle);
int32_t pngRead(PNGFILE *page, uint8_t *buffer, int32_t length);
int32_t pngSeek(PNGFILE *page, int32_t position);
void sensorReadings (String location, String country, String pollutant, float value, uint32_t x, uint32_t y, uint16_t bgColor);
void sensorCharts(uint32_t x, uint32_t y, uint16_t bgColor);
void chartData(String location, String country, String pollutant, float value, uint32_t x, uint32_t y, uint16_t bgColor);
void roomName(String location, uint32_t x, uint32_t y, uint16_t bgColor);
void topBar(uint32_t x, uint32_t y, uint16_t bgColor);
void fontSetup();

//Menu related functions
void menuDisplay();
void highlightButton(std::vector<TFT_eSPI_Button>& buttons, int index);
void clearHighlight(std::vector<TFT_eSPI_Button>& buttons, int index);
void drawMainMenu();
void resetSelection();
void moveSelection(int direction);
void handleJoystick(int xValue, int yValue, int buttonState);
void displayMenu();

void lcdSetup(){
    // listFilesInLittleFS(); // List files in LittleFS
    tft.begin();
    tft.setRotation(1);
    // tft.fillScreen(TFT_WHITE);
    // delay(10);
    String strname = "/logo.png";
    int16_t rc = png.open(strname.c_str(), pngOpen, pngClose, pngRead, pngSeek, pngDraw);
    if (rc == PNG_SUCCESS) {
      tft.startWrite();
      Serial.printf("image specs: (%d x %d), %d bpp, pixel type: %d\n", png.getWidth(), png.getHeight(), png.getBpp(), png.getPixelType());
      uint32_t dt = millis();
      if (png.getWidth() > MAX_IMAGE_WIDTH) {
        Serial.println("Image too wide for allocated line buffer size!");
      }
      else{
        rc = png.decode(NULL, 0);
        png.close();
      }
      tft.endWrite();
      Serial.print(millis()-dt); Serial.println("ms");
    }
    delay(2000);
}

void displayHomeScreen() {
    // Clear screen with white background
    tft.fillScreen(TFT_BG_COLOR);

    // Set text color and size
    tft.setTextColor(TFT_BLACK);

    // Get current time, day, and date
    String currentTime = "12:34"; // Replace with actual time fetching logic
    String currentDay = "Monday"; // Replace with actual day fetching logic
    String currentDate = "2023-10-10"; // Replace with actual date fetching logic

    // Create widgets for time, day, and date
    tft.setTextColor(TFT_BLACK);
    tft.setTextDatum(MC_DATUM);
    tft.loadFont(AA_FONT_SMALL, LittleFS);
    tft.drawString(currentDay, tft.width() / 2, tft.height() / 4);
    tft.unloadFont();

    tft.setTextColor(TFT_DARKGREY);
    tft.setTextDatum(MC_DATUM);
    tft.loadFont(AA_FONT_LARGE, LittleFS);
    tft.drawString(currentTime, tft.width() / 2, tft.height() / 2);
    tft.unloadFont();

    tft.setTextColor(TFT_BLUE);
    tft.setTextDatum(MC_DATUM);
    tft.loadFont(AA_FONT_SMALL, LittleFS);
    tft.drawString(currentDate, tft.width() / 2, 3 * tft.height() / 4);
    tft.unloadFont();

}

void displayIndoorSensorData(){
  tft.fillScreen(TFT_BG_COLOR);
  topBar(0, 0, TFT_LIGHTGREY);
  roomName("Living Room", 179, 55, TFT_LIGHTGREY);
  readCSVData();
  sensorCharts(240, 106, TFT_LIGHTGREY);
  sensorReadings("Indoor", "Nairobi", "PM2.5", pmdata.pm25_standard, 39, 96, TFT_LIGHTGREY);
  // sensorReadings("Indoor", "Nairobi", "PM10", pmdata.pm100_standard, 266, 86, TFT_WHITE);
  delay(3000);
}

void displayOutdoorSensorData(){}

void displayMenu(){
  for (int i = 0; i < 5000; i++){
    delay(1);
    if (buttonPressed) {
      break;
    }
  }
  if (buttonPressed) {
    buttonPressed = false;
    menuDisplay();
    Serial.println("Button was pressed!");
  }
  delay(1);
}

void menuDisplay() {
  tft.loadFont(AA_FONT_SMALL, LittleFS);
  drawMainMenu();
  for (;;) {
    // Read joystick values
    int xValue = analogRead(VRx_PIN);
    int yValue = analogRead(VRy_PIN);
    int buttonState = digitalRead(SW_PIN);

    // Handle joystick input
    handleJoystick(xValue, yValue, buttonState);

    // Break the loop if left arrow is used on the main menu and not returning from submenu
    if (isMainMenu && xValue < CENTER_X - TOLERANCE && !selectPressed) {
      break;
    }

    delay(150);
  }
  tft.unloadFont();
}

void clearHighlight(std::vector<TFT_eSPI_Button>& buttons, int index) {
  buttons[index].drawButton(true);
}

// Function to highlight a button
void highlightButton(std::vector<TFT_eSPI_Button>& buttons, int index) {
  buttons[index].drawButton(false);
}

// Function to draw the main menu
void drawMainMenu() {
  tft.fillScreen(TFT_BG_COLOR);
  topBar(0, 0, TFT_LIGHTGREY);
  roomName("Living Room", 179, 55, TFT_LIGHTGREY);
  mainButtons.clear(); // Clear existing buttons
  for (int i = 0; i < mainButtonLabels.size(); i++) {
    // TFT_eSPI_Button button;
    button.initButton(
      &tft,
      106, // Shifted left to make space for submenu
      106 + i * (BUTTON_HEIGHT + BUTTON_GAP),
      BUTTON_WIDTH,
      BUTTON_HEIGHT,
      TFT_BLUE,
      BUTTON_COLOR,
      TFT_BG_COLOR,
      (char*)mainButtonLabels[i], // Cast to char*
      2
    );
    mainButtons.push_back(button);
    mainButtons[i].drawButton(true);
  }

  // Highlight the current button
  highlightButton(mainButtons, currentSelection);
}

// Function to draw a submenu
void drawSubMenu(int menuIndex) {
  tft.fillRect(160, 0, tft.width() - 160, tft.height(), TFT_BG_COLOR);
  topBar(0, 0, TFT_LIGHTGREY);
  roomName("Living Room", 179, 55, TFT_LIGHTGREY);
  if (subButtons.size() <= menuIndex) {
    subButtons.resize(menuIndex + 1);
  }

  subButtons[menuIndex].clear(); // Clear existing submenu buttons
  for (int i = 0; i < subButtonLabels[menuIndex].size(); i++) {
    // TFT_eSPI_Button button;
    button.initButton(
      &tft,
      220, // Submenu positioned on the right
      126 + i * (BUTTON_HEIGHT + BUTTON_GAP),
      BUTTON_WIDTH,
      BUTTON_HEIGHT,
      TFT_BLUE,
      BUTTON_COLOR,
      TFT_BG_COLOR,
      (char*)subButtonLabels[menuIndex][i], // Cast to char*
      2
    );
    subButtons[menuIndex].push_back(button);
    subButtons[menuIndex][i].drawButton(true);
  }

  // Highlight the first button in the submenu
  highlightButton(subButtons[menuIndex], subMenuSelection);
}

// Function to reset selection and return to the main menu
void resetSelection() {
  Serial.println("Returning to main menu...");
  isMainMenu = true;
  activeMainMenu = -1;
  subMenuSelection = 0;
  drawMainMenu();
}

// Function to move the selection in the menu
void moveSelection(int direction) {
  // Clear current highlight
  if (isMainMenu) {
    clearHighlight(mainButtons, currentSelection);
  } else {
    clearHighlight(subButtons[activeMainMenu], subMenuSelection);
  }

  // Update selection index
  if (isMainMenu) {
    currentSelection += direction;
  } else {
    subMenuSelection += direction;
  }

  // Wrap around menu options
  if (isMainMenu) {
    if (currentSelection < 0) currentSelection = mainButtons.size() - 1;
    if (currentSelection >= mainButtons.size()) currentSelection = 0;
  } else {
    if (subMenuSelection < 0) subMenuSelection = subButtons[activeMainMenu].size() - 1;
    if (subMenuSelection >= subButtons[activeMainMenu].size()) subMenuSelection = 0;
  }

  // Highlight new selection
  if (isMainMenu) {
    highlightButton(mainButtons, currentSelection);
  } else {
    highlightButton(subButtons[activeMainMenu], subMenuSelection);
  }
}

// Function to handle joystick input
void handleJoystick(int xValue, int yValue, int buttonState) {
  static bool prevButtonState = HIGH;

  if (isMainMenu) {
    // Up/Down to toggle selection
    if (yValue < CENTER_Y - TOLERANCE) {
      moveSelection(-1); // Up
    } else if (yValue > CENTER_Y + TOLERANCE) {
      moveSelection(1); // Down
    }

    // Right or button press to select
    if ((xValue > CENTER_X + TOLERANCE || buttonState == LOW) && !selectPressed) {
      selectPressed = true;
      activeMainMenu = currentSelection; // Track selected main menu button
      isMainMenu = false;
      subMenuSelection = 0; // Reset selection for submenu

      // Show the corresponding submenu
      drawSubMenu(activeMainMenu);
    } else if (buttonState == HIGH && xValue < CENTER_X + TOLERANCE) {
      selectPressed = false;
    }
  } else {
    // Submenu navigation
    if (yValue < CENTER_Y - TOLERANCE) {
      moveSelection(-1); // Up
    } else if (yValue > CENTER_Y + TOLERANCE) {
      moveSelection(1); // Down
    }

    // Left to return to the main menu
    if (xValue < CENTER_X - TOLERANCE) {
      resetSelection();
    }
  }

  prevButtonState = buttonState;
}

void topBar(uint32_t x, uint32_t y, uint16_t bgColor){
  tft.fillRect(x, y, 480, 36, bgColor); // Fill a rectangle at (x, y) with width 160 and height 87 with bgColor
  tft.drawRect(x, y, 480, 36, TFT_BG_COLOR); // Draw a border for the rectangle

  // Draw GoodAir.png image
  String imageName = "/slogo.png";
  int16_t rc = png.open(imageName.c_str(), pngOpen, pngClose, pngRead, pngSeek, pngDraw);
  if (rc == PNG_SUCCESS) {
    xpos = 28 + x; // X position for the image
    ypos = 5 + y; // Y position for the image
    rc = png.decode(NULL, 0);
    png.close();
  } else {
    Serial.printf("Failed to open %s, error code: %d\n", imageName.c_str(), rc);
  }
}

void roomName(String location, uint32_t x, uint32_t y, uint16_t bgColor){
  tft.fillRoundRect(x, y, 137, 30, radius, bgColor); // Fill a rounded rectangle
  tft.drawRoundRect(x, y, 137, 30, radius, TFT_BG_COLOR); // Draw a border for the rounded rectangle

  // Location and country
  tft.setTextColor(TFT_BLACK);
  tft.loadFont(AA_FONT_SMALL, LittleFS);
  tft.setCursor(x + 5, y + 5); // Position for location
  tft.print(location);
  // tft.unloadFont();
}

void sensorReadings (String location, String country, String pollutant, float value, uint32_t x, uint32_t y, uint16_t bgColor){
  tft.fillRoundRect(x, y, 160, 87, radius, bgColor); // Fill a rounded rectangle
  tft.drawRoundRect(x, y, 160, 87, radius, TFT_BG_COLOR); // Draw a border for the rounded rectangle

  // Location and country
  tft.setTextColor(TFT_BLACK);
  tft.loadFont(AA_FONT_SMALL, LittleFS);
  tft.setCursor(x + 10, y + 10); // Position for location
  tft.print(location);
  // tft.unloadFont();
  
  // Pollutant type (e.g., PM2.5)
  tft.loadFont(AA_FONT_TINNY, LittleFS);
  tft.setCursor(x + 10, y + 35); // Adjusted position for pollutant
  tft.print(pollutant);
  // tft.unloadFont();

  // Pollutant value
  tft.loadFont(AA_FONT_MEDIUM, LittleFS);
  tft.setCursor(x + 10, y + 55); // Adjusted position for value
  tft.print(value, 2); // Display with 2 decimal places
  // tft.unloadFont();

  // Temp humidity value
  tft.loadFont(AA_FONT_SMALL, LittleFS);
  tft.setCursor(x + 10, y + 110); // Adjusted position for label
  tft.print("rh  :"); // Display label
  // tft.unloadFont();
  tft.loadFont(AA_FONT_MEDIUM, LittleFS);
  tft.setCursor(x + 70, y + 105); // Adjusted position for value
  tft.print("45.0"); // Display value with size 3
  // tft.unloadFont();

  tft.loadFont(AA_FONT_SMALL, LittleFS);
  tft.setCursor(x + 10, y + 150); // Adjusted position for label
  tft.print("temp:"); // Display label
  // tft.unloadFont();
  tft.loadFont(AA_FONT_MEDIUM, LittleFS);
  tft.setCursor(x + 70, y + 145); // Adjusted position for value
  tft.print("25.0"); // Display value with size 3
  tft.unloadFont();

  // Draw GoodAir.png image
  String imageName = "/Moderate.png";
  int16_t rc = png.open(imageName.c_str(), pngOpen, pngClose, pngRead, pngSeek, pngDraw);
  if (rc == PNG_SUCCESS) {
    xpos = 105 + x; // X position for the image
    ypos = 39 + y; // Y position for the image
    rc = png.decode(NULL, 0);
    png.close();
  } else {
    Serial.printf("Failed to open %s, error code: %d\n", imageName.c_str(), rc);
  }
}

void sensorCharts(unsigned int x, unsigned int y, unsigned short bgColor) {
  tft.loadFont(AA_FONT_TINNY, LittleFS);
    // Define graph area
    gr.createGraph(220, 150, tft.color565(220, 220, 220)); // Light grey background
    gr.setGraphScale(0.0, data_count, 0.0, 100.0); // X: 0 to data_count, Y: 0 to 100
    gr.setGraphGrid(0.0, 5.0, 0.0, 10.0, bgColor); // Grid every 5 points and 10 units
    gr.drawGraph(x, y); // Draw graph at (40, 10)

    // Draw bars
    int barWidth = 10;
    for (int i = 0; i < data_count; i++) {
        float barHeight = pm25_data[i];
        int barX = gr.getPointX(i);          // Map x to graph pixel
        int barY = gr.getPointY(barHeight); // Top of the bar
        int bottomY = gr.getPointY(0.0);    // Bottom of the graph
        if (barX >= 0 && barX < tft.width() && barY >= 0 && barY < tft.height()) {
            tft.fillRect(barX - barWidth / 2, barY, barWidth, bottomY - barY, TFT_BLUE); // Draw bar
        } else {
            Serial.print("Bar out of bounds at X: "); // Debug print
            Serial.print(barX); // Debug print
            Serial.print(", Y: "); // Debug print
            Serial.println(barY); // Debug print
        }
    }

    // Draw x-axis labels
    for (int i = 0; i < data_count; i++) {
        tft.setTextDatum(TC_DATUM);
        // tft.loadFont(AA_FONT_TINNY, LittleFS);
        tft.setTextColor(TFT_BLACK, TFT_BG_COLOR);
        tft.drawNumber(i, gr.getPointX(i), gr.getPointY(0.0) + 5);
        // tft.unloadFont();
    }

    // Draw y-axis labels
    for (int i = 0; i <= 100; i += 10) {
        tft.setTextDatum(MR_DATUM);
        // tft.loadFont(AA_FONT_TINNY, LittleFS);
        tft.setTextColor(TFT_BLACK, TFT_BG_COLOR);
        tft.drawNumber(i, gr.getPointX(0.0) - 5, gr.getPointY(i));
        // tft.unloadFont();
    }
    tft.unloadFont();
}

void fontSetup(){
  if (LittleFS.exists("/NotoSans15.vlw")    == false) font_missing = true;
  if (LittleFS.exists("/NotoSans20.vlw")    == false) font_missing = true;
  if (LittleFS.exists("/NotoSans30.vlw")    == false) font_missing = true;
  if (LittleFS.exists("/NotoSans36.vlw")    == false) font_missing = true;

  if (font_missing)
  {
    Serial.println("\nFont missing in Flash FS, did you upload it?");
    while(1) yield();
  }
  else Serial.println("\nFonts found OK.");
}

//ASSIT FUNCTIONS
void pngDraw(PNGDRAW *pDraw) {
  uint16_t lineBuffer[MAX_IMAGE_WIDTH];
  png.getLineAsRGB565(pDraw, lineBuffer, PNG_RGB565_BIG_ENDIAN, 0xffffffff);
  tft.pushImage(xpos, ypos + pDraw->y, pDraw->iWidth, 1, lineBuffer);
}

void * pngOpen(const char *filename, int32_t *size) {
  Serial.printf("Attempting to open %s\n", filename);
  pngfile = FlashFS.open(filename, "r");
  *size = pngfile.size();
  return &pngfile;
}

void pngClose(void *handle) {
  File pngfile = *((File*)handle);
  if (pngfile) pngfile.close();
}

int32_t pngRead(PNGFILE *page, uint8_t *buffer, int32_t length) {
  if (!pngfile) return 0;
  page = page; // Avoid warning
  return pngfile.read(buffer, length);
}

int32_t pngSeek(PNGFILE *page, int32_t position) {
  if (!pngfile) return 0;
  page = page; // Avoid warning
  return pngfile.seek(position);
}

//color hex codes
// #f5c93b - moderate
// #2aeb81 - good
// #f5c93b - moderate
// #f05666 - unhealthy
// #c76df7 - veryunhealth
// #f173ff - harzadous
// #ebebeb - in bg color
// #f05666 - unhealthy
// #c76df7 - veryunhealth
// #f173ff - harzadous
// #ebebeb - in bg color