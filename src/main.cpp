#include <Arduino.h>
#include <WiFi.h>
#include <vector> // Include vector library

// Include the SD library
#include <SD.h>

#include "GlobalVariables.h"
#include "SensorsReading.h"
#include "LCDDisplay.h"
#include "wifiComms.h"
#include "EspnowComms.h"
#include "Storage.h"

// #include <SPI.h>
#include <TFT_eSPI.h>
#include <TFT_eWidget.h>

std::vector<TFT_eSPI_Button> mainButtons; // Vector for main menu buttons
std::vector<std::vector<TFT_eSPI_Button>> subButtons;  // Vector of vectors for submenu buttons

// Define main menu button labels
const std::vector<const char*> mainButtonLabels = {"Wifi", "Devices", "Files", "Settings"};

// Define submenu button labels
const std::vector<std::vector<const char*>> subButtonLabels = {
  {"room1"},
  {"device1", "device2"},
  {"file1", "file2", "file3"},
  {"setting1", "setting2", "setting3"}
};

// Joystick pin definitions
#define VRx_PIN 34
#define VRy_PIN 35
#define SW_PIN 0 

// Global state variables
int currentSelection = 0; // Current selected button index
bool selectPressed = false;
bool isMainMenu = true;   // Tracks if the user is in the main menu
int activeMainMenu = -1;  // Tracks which main menu button was selected

// Button properties
#define BUTTON_WIDTH  120
#define BUTTON_HEIGHT 50
#define BUTTON_GAP    20
#define BUTTON_COLOR  TFT_BLUE
#define SELECT_COLOR  TFT_WHITE

// Center positions
#define CENTER_X 1947
#define CENTER_Y 1891
#define TOLERANCE 1000

// Function declarations
void handleJoystick(int xValue, int yValue, int buttonState);
void moveSelection(int direction);
void highlightButton(std::vector<TFT_eSPI_Button>& buttons, int index);
void resetSelection();
void drawMainMenu();
void drawSubMenu(int menuIndex);
void clearHighlight(std::vector<TFT_eSPI_Button>& buttons, int index);

void setup() {
  // Initialize serial and joystick
  Serial.begin(115200);
  pinMode(SW_PIN, INPUT_PULLUP);

  // Initialize TFT display
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  // Initialize main menu
  drawMainMenu();
}

void loop() {
  // Read joystick values
  int xValue = analogRead(VRx_PIN);
  int yValue = analogRead(VRy_PIN);
  int buttonState = digitalRead(SW_PIN);

  // Handle joystick input
  handleJoystick(xValue, yValue, buttonState);

  // Delay for smoother input handling
  delay(150);
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
      currentSelection = 0; // Reset selection for submenu

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

// Function to move the selection in the menu
void moveSelection(int direction) {
  // Clear current highlight
  if (isMainMenu) {
    clearHighlight(mainButtons, currentSelection);
  } else {
    clearHighlight(subButtons[activeMainMenu], currentSelection);
  }

  // Update selection index
  currentSelection += direction;

  // Wrap around menu options
  if (isMainMenu) {
    if (currentSelection < 0) currentSelection = mainButtons.size() - 1;
    if (currentSelection >= mainButtons.size()) currentSelection = 0;
  } else {
    if (currentSelection < 0) currentSelection = subButtons[activeMainMenu].size() - 1;
    if (currentSelection >= subButtons[activeMainMenu].size()) currentSelection = 0;
  }

  // Highlight new selection
  if (isMainMenu) {
    highlightButton(mainButtons, currentSelection);
  } else {
    highlightButton(subButtons[activeMainMenu], currentSelection);
  }
}

// Function to highlight a button
void highlightButton(std::vector<TFT_eSPI_Button>& buttons, int index) {
  buttons[index].drawButton(true);
}

// Function to clear button highlight
void clearHighlight(std::vector<TFT_eSPI_Button>& buttons, int index) {
  buttons[index].drawButton(false);
}

// Function to reset selection and return to the main menu
void resetSelection() {
  Serial.println("Returning to main menu...");
  isMainMenu = true;
  activeMainMenu = -1;
  currentSelection = 0;
  drawMainMenu();
}

// Function to draw the main menu
void drawMainMenu() {
  tft.fillScreen(TFT_BLACK);

  mainButtons.clear(); // Clear existing buttons
  for (int i = 0; i < mainButtonLabels.size(); i++) {
    TFT_eSPI_Button button;
    button.initButton(
      &tft,
      80, // Shifted left to make space for submenu
      40 + i * (BUTTON_HEIGHT + BUTTON_GAP),
      BUTTON_WIDTH,
      BUTTON_HEIGHT,
      TFT_WHITE,
      BUTTON_COLOR,
      TFT_BLACK,
      (char*)mainButtonLabels[i], // Cast to char*
      2
    );
    mainButtons.push_back(button);
    mainButtons[i].drawButton(false);
  }

  // Highlight the first button
  highlightButton(mainButtons, currentSelection);
}

// Function to draw a submenu
void drawSubMenu(int menuIndex) {
  tft.fillRect(160, 0, tft.width() - 160, tft.height(), TFT_BLACK);

  if (subButtons.size() <= menuIndex) {
    subButtons.resize(menuIndex + 1);
  }

  subButtons[menuIndex].clear(); // Clear existing submenu buttons
  for (int i = 0; i < subButtonLabels[menuIndex].size(); i++) {
    TFT_eSPI_Button button;
    button.initButton(
      &tft,
      240, // Submenu positioned on the right
      40 + i * (BUTTON_HEIGHT + BUTTON_GAP),
      BUTTON_WIDTH,
      BUTTON_HEIGHT,
      TFT_WHITE,
      BUTTON_COLOR,
      TFT_BLACK,
      (char*)subButtonLabels[menuIndex][i], // Cast to char*
      2
    );
    subButtons[menuIndex].push_back(button);
    subButtons[menuIndex][i].drawButton(false);
  }

  // Highlight the first button in the submenu
  highlightButton(subButtons[menuIndex], currentSelection);
}