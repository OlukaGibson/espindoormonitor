void wegitCode(){
    // #include <Arduino.h>
// #include <WiFi.h>

// #include "LittleFS.h"

// #include "GlobalVariables.h"
// #include "SensorsReading.h"
// #include "LCDDisplay.h"
// #include "wifiComms.h"
// #include "EspnowComms.h"
// #include "Storage.h"

// // #include <SPI.h>
// #include <TFT_eSPI.h>
// #include <TFT_eWidget.h>

// MeterWidget   amps  = MeterWidget(&tft);
// MeterWidget   volts = MeterWidget(&tft);
// MeterWidget   ohms  = MeterWidget(&tft);

// #define LOOP_PERIOD 1000

// void setup(){
//     tft.init();
//     tft.setRotation(1);
//     tft.fillScreen(TFT_WHITE);
//     Serial.begin(115200);

//     amps.setZones(75, 100, 50, 75, 25, 50, 0, 25);
//     amps.analogMeter(0, 0, 2.0, "mA", "0", "0.5", "1.0", "1.5", "2.0");

//     volts.setZones(0, 100, 25, 75, 0, 0, 40, 60);
//     volts.analogMeter(0, 128, 10.0, "V", "0", "2.5", "5", "7.5", "10"); 

//     ohms.analogMeter(0, 256, 100, "R", "0", "", "50", "", "100");
// }

// float mapValue(float ip, float ipmin, float ipmax, float tomin, float tomax){
//   return tomin + (((tomax - tomin) * (ip - ipmin))/ (ipmax - ipmin));
// }

// void loop(){
//   static int d = 0;
//   static uint32_t updateTime = 0;  

//   if (millis() - updateTime >= LOOP_PERIOD) {
//     updateTime = millis();

//     d += 4; if (d > 360) d = 0;

//     // Create a Sine wave for testing, value is in range 0 - 100
//     float value = 50.0 + 50.0 * sin((d + 0) * 0.0174532925);

//     float current;
//     current = mapValue(value, (float)0.0, (float)100.0, (float)0.0, (float)2.0);
//     //Serial.print("I = "); Serial.print(current);
//     amps.updateNeedle(current, 0);

//     float voltage;
//     voltage = mapValue(value, (float)0.0, (float)100.0, (float)0.0, (float)10.0);
//     //Serial.print(", V = "); Serial.println(voltage);
//     volts.updateNeedle(voltage, 0);
    
//     float resistance;
//     resistance = mapValue(value, (float)0.0, (float)100.0, (float)0.0, (float)100.0);
//     //Serial.print(", R = "); Serial.println(resistance);
//     ohms.updateNeedle(resistance, 0);
//   }
// }

}

void setupcode(){
//     #include <Arduino.h>
// #include <WiFi.h>

// #include "LittleFS.h"

// #include "GlobalVariables.h"
// #include "SensorsReading.h"
// #include "LCDDisplay.h"
// #include "wifiComms.h"
// #include "EspnowComms.h"
// #include "Storage.h"

// // #include <SPI.h>
// #include <TFT_eSPI.h>
// #include <TFT_eWidget.h>
// #define FileSys LittleFS

// // Include the PNG decoder library
// #include <PNGdec.h>

// PNG png;
// File pngfile;
// #define MAX_IMAGE_WIDTH 480 // Increase the width to accommodate your image

// int16_t xpos = 0;
// int16_t ypos = 0;

// void setup(){
//   Serial.begin(115200);
//   Serial.println("\n\n Using the PNGdec library");

//   // Initialise FS
//   if (!FileSys.begin()) {
//     Serial.println("LittleFS initialisation failed!");
//     while (1) yield(); // Stay here twiddling thumbs waiting
//   }

//   // Initialise the TFT
//   tft.begin();
//   tft.setRotation(1); // Set rotation to 1
//   tft.fillScreen(TFT_WHITE);
//   Serial.println("\r\nInitialisation done.");
// }

// void pngDraw(PNGDRAW *pDraw) {
//   uint16_t lineBuffer[MAX_IMAGE_WIDTH];
//   png.getLineAsRGB565(pDraw, lineBuffer, PNG_RGB565_BIG_ENDIAN, 0xffffffff);
//   tft.pushImage(xpos, ypos + pDraw->y, pDraw->iWidth, 1, lineBuffer);
// }

// void * pngOpen(const char *filename, int32_t *size) {
//   Serial.printf("Attempting to open %s\n", filename);
//   pngfile = FileSys.open(filename, "r");
//   *size = pngfile.size();
//   return &pngfile;
// }

// void pngClose(void *handle) {
//   File pngfile = *((File*)handle);
//   if (pngfile) pngfile.close();
// }

// int32_t pngRead(PNGFILE *page, uint8_t *buffer, int32_t length) {
//   if (!pngfile) return 0;
//   page = page; // Avoid warning
//   return pngfile.read(buffer, length);
// }

// int32_t pngSeek(PNGFILE *page, int32_t position) {
//   if (!pngfile) return 0;
//   page = page; // Avoid warning
//   return pngfile.seek(position);
// }

// void loop()
// {
//   // Open the specific image file
//   String strname = "/gibson.png";
//   Serial.println(strname);
//   // Pass support callback function names to library
//   int16_t rc = png.open(strname.c_str(), pngOpen, pngClose, pngRead, pngSeek, pngDraw);
//   if (rc == PNG_SUCCESS) {
//     tft.startWrite();
//     Serial.printf("image specs: (%d x %d), %d bpp, pixel type: %d\n", png.getWidth(), png.getHeight(), png.getBpp(), png.getPixelType());
//     uint32_t dt = millis();
//     if (png.getWidth() > MAX_IMAGE_WIDTH) {
//       Serial.println("Image too wide for allocated line buffer size!");
//     }
//     else {
//       rc = png.decode(NULL, 0);
//       png.close();
//     }
//     tft.endWrite();
//     // How long did rendering take...
//     Serial.print(millis()-dt); Serial.println("ms");
//   }
//   delay(3000);
//   tft.fillScreen(random(0x10000));
// }


}

void interruptCode(){
    // #include <Arduino.h>

// #define BUTTON_PIN 0 // GPIO0 as the interrupt pin

// volatile bool buttonPressed = false; // Flag to track button press

// void IRAM_ATTR handleButtonPress() {
//   buttonPressed = true; // Set the flag when the interrupt triggers
// }

// void setup() {
//   Serial.begin(115200);

//   // Configure GPIO0 as an input with pull-up
//   pinMode(BUTTON_PIN, INPUT_PULLUP);

//   // Attach an interrupt to GPIO0
//   attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleButtonPress, FALLING);

//   Serial.println("Interrupt attached to GPIO0");
// }

// void loop() {
//   // Check if the button was pressed
//   if (buttonPressed) {
//     buttonPressed = false; // Reset the flag
//     Serial.println("Button was pressed!");
//   }

//   delay(100); // Small delay for stability
// }

}

void littlefsCode(){
// void listFilesInLittleFS();

// void listFilesInLittleFS() {
//     Serial.println("Listing files in LittleFS:");
//     File root = LittleFS.open("/");
//     File file = root.openNextFile();
//     while (file) {
//         Serial.print("FILE: ");
//         Serial.println(file.name());
//         file = root.openNextFile();
//     }
// }

// void displayData(){
//     if (readPMSdata(&Serial1)) {
//     // Print data to Serial Monitor
//     Serial.println("======= PMS5003 DATA =======");
//     Serial.print("PM 1.0: "); Serial.print(pmdata.pm10_standard);
//     Serial.print(", PM 2.5: "); Serial.print(pmdata.pm25_standard);
//     Serial.print(", PM 10: "); Serial.println(pmdata.pm100_standard);
//     Serial.println("===========================");

//     // Clear screen with white background
//     tft.fillScreen(TFT_WHITE); 

//     // Set label text color and size
//     tft.setTextColor(TFT_BLACK);
//     tft.setTextSize(1);

//     // Define the middle of the screen and spacing for the circles
//     int screenMidY = tft.height() / 2;    // Middle of the screen vertically
//     int circleRadius = 40;                // Increase circle size
//     int pm1_x = 60;                       // Position for PM 1.0 on the left
//     int pm25_x = tft.width() / 2;         // Position for PM 2.5 in the middle
//     int pm10_x = tft.width() - 60;        // Position for PM 10 on the right

//     // Draw labels above each circle
//     tft.setCursor(pm1_x - 15, screenMidY - circleRadius - 20);
//     tft.println("PM 1.0");

//     tft.setCursor(pm25_x - 15, screenMidY - circleRadius - 20);
//     tft.println("PM 2.5");

//     tft.setCursor(pm10_x - 15, screenMidY - circleRadius - 20);
//     tft.println("PM 10");

//     // Draw circles with values
//     tft.fillCircle(pm1_x, screenMidY, circleRadius, TFT_GREEN); // PM 1.0 circle
//     tft.setCursor(pm1_x - 10, screenMidY - 5);
//     tft.setTextColor(TFT_BLACK, TFT_GREEN); // Black text with green background
//     tft.setTextSize(3);                     // Larger text size for values
//     tft.print(pmdata.pm10_standard);

//     tft.fillCircle(pm25_x, screenMidY, circleRadius, TFT_YELLOW); // PM 2.5 circle
//     tft.setCursor(pm25_x - 10, screenMidY - 5);
//     tft.setTextColor(TFT_BLACK, TFT_YELLOW); // Black text with yellow background
//     tft.print(pmdata.pm25_standard);

//     tft.fillCircle(pm10_x, screenMidY, circleRadius, TFT_RED); // PM 10 circle
//     tft.setCursor(pm10_x - 10, screenMidY - 5);
//     tft.setTextColor(TFT_BLACK, TFT_RED);   // Black text with red background
//     tft.print(pmdata.pm100_standard);

//     // Reset text size and color for future use
//     tft.setTextSize(1);
//     tft.setTextColor(TFT_BLACK);
//   }
//   delay(1000);
// }
}

void fontselectionCode(){
//     #include <Arduino.h>
// #include <WiFi.h>

// // Include the SD library
// #include <SD.h>

// #include "GlobalVariables.h"
// #include "SensorsReading.h"
// #include "LCDDisplay.h"
// #include "wifiComms.h"
// #include "EspnowComms.h"
// #include "Storage.h"

// // #include <SPI.h>
// #include <TFT_eSPI.h>
// #include <TFT_eWidget.h>

// #define AA_FONT_SMALL "NotoSansBold15"
// #define AA_FONT_LARGE "NotoSansBold36"

// #define FlashFS LittleFS

// void setup(void) {

//   Serial.begin(250000);

//   tft.begin();

//   tft.setRotation(1);

//   if (!LittleFS.begin()) {
//     Serial.println("Flash FS initialisation failed!");
//     while (1) yield(); // Stay here twiddling thumbs waiting
//   }
// //   Serial.println("\n\Flash FS available!");
  
//   bool font_missing = false;
//   if (LittleFS.exists("/NotoSansBold15.vlw")    == false) font_missing = true;
//   if (LittleFS.exists("/NotoSansBold36.vlw")    == false) font_missing = true;

//   if (font_missing)
//   {
//     Serial.println("\nFont missing in Flash FS, did you upload it?");
//     while(1) yield();
//   }
//   else Serial.println("\nFonts found OK.");
// }


// void loop() {

//   tft.fillScreen(TFT_BLACK);

//   tft.setTextColor(TFT_WHITE, TFT_BLACK); // Set the font colour AND the background colour
//                                           // so the anti-aliasing works

//   tft.setCursor(0, 0); // Set cursor at top left of screen


//   // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//   // Small font
//   // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//   tft.loadFont(AA_FONT_SMALL, LittleFS); // Must load the font first

//   tft.println("Small 15pt font"); // println moves cursor down for a new line

//   tft.println(); // New line

//   tft.print("ABC"); // print leaves cursor at end of line

//   tft.setTextColor(TFT_CYAN, TFT_BLACK);
//   tft.println("1234"); // Added to line after ABC

//   tft.setTextColor(TFT_YELLOW, TFT_BLACK);
//   // print stream formatting can be used,see:
//   // https://www.arduino.cc/en/Serial/Print
//   int ivalue = 1234;
//   tft.println(ivalue);       // print as an ASCII-encoded decimal
//   tft.println(ivalue, DEC);  // print as an ASCII-encoded decimal
//   tft.println(ivalue, HEX);  // print as an ASCII-encoded hexadecimal
//   tft.println(ivalue, OCT);  // print as an ASCII-encoded octal
//   tft.println(ivalue, BIN);  // print as an ASCII-encoded binary

//   tft.println(); // New line
//   tft.setTextColor(TFT_MAGENTA, TFT_BLACK);
//   float fvalue = 1.23456;
//   tft.println(fvalue, 0);  // no decimal places
//   tft.println(fvalue, 1);  // 1 decimal place
//   tft.println(fvalue, 2);  // 2 decimal places
//   tft.println(fvalue, 5);  // 5 decimal places

//   delay(5000);

//   // Get ready for the next demo while we have this font loaded
//   tft.fillScreen(TFT_BLACK);
//   tft.setCursor(0, 0); // Set cursor at top left of screen
//   tft.setTextColor(TFT_WHITE, TFT_BLACK);
//   tft.println("Wrong and right ways to");
//   tft.println("print changing values...");

//   tft.unloadFont(); // Remove the font to recover memory used


//   // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//   // Large font
//   // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//   tft.loadFont(AA_FONT_LARGE, LittleFS); // Load another different font

//   //tft.fillScreen(TFT_BLACK);
  
//   // Draw changing numbers - does not work unless a filled rectangle is drawn over the old text
//   for (int i = 0; i <= 20; i++)
//   {
//     tft.setCursor(50, 50);
//     tft.setTextColor(TFT_GREEN, TFT_BLACK); // TFT_BLACK is used for anti-aliasing only
//                                             // By default background fill is off
//     tft.print("      "); // Overprinting old number with spaces DOES NOT WORK!
//     tft.setCursor(50, 50);
//     tft.print(i / 10.0, 1);

//     // Adding a parameter "true" to the setTextColor() function fills character background
//     // This extra parameter is only for smooth fonts!
//     tft.setTextColor(TFT_GREEN, TFT_BLACK, true);
//     tft.setCursor(50, 90);
//     tft.print(i / 10.0, 1);
    
//     delay (200);
//   }

//   delay(5000);

//   // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//   // Large font text wrapping
//   // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//   tft.fillScreen(TFT_BLACK);
  
//   tft.setTextColor(TFT_YELLOW, TFT_BLACK); // Change the font colour and the background colour

//   tft.setCursor(0, 0); // Set cursor at top left of screen

//   tft.println("Large font!");

//   tft.setTextWrap(true); // Wrap on width
//   tft.setTextColor(TFT_CYAN, TFT_BLACK);
//   tft.println("Long lines wrap to the next line");

//   tft.setTextWrap(false, false); // Wrap on width and height switched off
//   tft.setTextColor(TFT_MAGENTA, TFT_BLACK);
//   tft.println("Unless text wrap is switched off");

//   tft.unloadFont(); // Remove the font to recover memory used

//   delay(8000);
// }

}

void menuCodeandButtonCode(){
    // #include <Arduino.h>
// #include <WiFi.h>
// #include <vector> // Include vector library

// // Include the SD library
// #include <SD.h>

// #include "GlobalVariables.h"
// #include "SensorsReading.h"
// #include "LCDDisplay.h"
// #include "wifiComms.h"
// #include "EspnowComms.h"
// #include "Storage.h"

// // #include <SPI.h>
// #include <TFT_eSPI.h>
// #include <TFT_eWidget.h>

// std::vector<TFT_eSPI_Button> mainButtons; // Vector for main menu buttons
// std::vector<std::vector<TFT_eSPI_Button>> subButtons;  // Vector of vectors for submenu buttons

// // Define main menu button labels
// const std::vector<const char*> mainButtonLabels = {"Wifi", "Devices", "Files", "Settings"};

// // Define submenu button labels
// const std::vector<std::vector<const char*>> subButtonLabels = {
//   {"room1"},
//   {"device1", "device2"},
//   {"file1", "file2", "file3"},
//   {"setting1", "setting2", "setting3"}
// };

// // Joystick pin definitions
// #define VRx_PIN 34
// #define VRy_PIN 35
// #define SW_PIN 0 

// // Global state variables
// int currentSelection = 0; // Current selected button index
// int subMenuSelection = 0; // Current selected submenu button index
// bool selectPressed = false;
// bool isMainMenu = true;   // Tracks if the user is in the main menu
// int activeMainMenu = -1;  // Tracks which main menu button was selected

// // Button properties
// #define BUTTON_WIDTH  120
// #define BUTTON_HEIGHT 50
// #define BUTTON_GAP    20
// #define BUTTON_COLOR  TFT_BLUE
// #define SELECT_COLOR  TFT_WHITE

// // Center positions
// #define CENTER_X 1947
// #define CENTER_Y 1891
// #define TOLERANCE 1000

// // Function declarations
// void handleJoystick(int xValue, int yValue, int buttonState);
// void moveSelection(int direction);
// void highlightButton(std::vector<TFT_eSPI_Button>& buttons, int index);
// void resetSelection();
// void drawMainMenu();
// void drawSubMenu(int menuIndex);
// void clearHighlight(std::vector<TFT_eSPI_Button>& buttons, int index);

// void setup() {
//   // Initialize serial and joystick
//   Serial.begin(115200);
//   pinMode(SW_PIN, INPUT_PULLUP);

//   // Initialize TFT display
//   tft.init();
//   tft.setRotation(1);
//   tft.fillScreen(TFT_WHITE);

//   // Initialize main menu
//   drawMainMenu();
// }

// void loop() {
//   // Read joystick values
//   int xValue = analogRead(VRx_PIN);
//   int yValue = analogRead(VRy_PIN);
//   int buttonState = digitalRead(SW_PIN);

//   // Handle joystick input
//   handleJoystick(xValue, yValue, buttonState);

//   delay(150);
// }

// // Function to handle joystick input
// void handleJoystick(int xValue, int yValue, int buttonState) {
//   static bool prevButtonState = HIGH;

//   if (isMainMenu) {
//     // Up/Down to toggle selection
//     if (yValue < CENTER_Y - TOLERANCE) {
//       moveSelection(-1); // Up
//     } else if (yValue > CENTER_Y + TOLERANCE) {
//       moveSelection(1); // Down
//     }

//     // Right or button press to select
//     if ((xValue > CENTER_X + TOLERANCE || buttonState == LOW) && !selectPressed) {
//       selectPressed = true;
//       activeMainMenu = currentSelection; // Track selected main menu button
//       isMainMenu = false;
//       subMenuSelection = 0; // Reset selection for submenu

//       // Show the corresponding submenu
//       drawSubMenu(activeMainMenu);
//     } else if (buttonState == HIGH && xValue < CENTER_X + TOLERANCE) {
//       selectPressed = false;
//     }
//   } else {
//     // Submenu navigation
//     if (yValue < CENTER_Y - TOLERANCE) {
//       moveSelection(-1); // Up
//     } else if (yValue > CENTER_Y + TOLERANCE) {
//       moveSelection(1); // Down
//     }

//     // Left to return to the main menu
//     if (xValue < CENTER_X - TOLERANCE) {
//       resetSelection();
//     }
//   }

//   prevButtonState = buttonState;
// }

// // Function to move the selection in the menu
// void moveSelection(int direction) {
//   // Clear current highlight
//   if (isMainMenu) {
//     clearHighlight(mainButtons, currentSelection);
//   } else {
//     clearHighlight(subButtons[activeMainMenu], subMenuSelection);
//   }

//   // Update selection index
//   if (isMainMenu) {
//     currentSelection += direction;
//   } else {
//     subMenuSelection += direction;
//   }

//   // Wrap around menu options
//   if (isMainMenu) {
//     if (currentSelection < 0) currentSelection = mainButtons.size() - 1;
//     if (currentSelection >= mainButtons.size()) currentSelection = 0;
//   } else {
//     if (subMenuSelection < 0) subMenuSelection = subButtons[activeMainMenu].size() - 1;
//     if (subMenuSelection >= subButtons[activeMainMenu].size()) subMenuSelection = 0;
//   }

//   // Highlight new selection
//   if (isMainMenu) {
//     highlightButton(mainButtons, currentSelection);
//   } else {
//     highlightButton(subButtons[activeMainMenu], subMenuSelection);
//   }
// }

// // Function to highlight a button
// void highlightButton(std::vector<TFT_eSPI_Button>& buttons, int index) {
//   buttons[index].drawButton(false);
// }

// // Function to clear button highlight
// void clearHighlight(std::vector<TFT_eSPI_Button>& buttons, int index) {
//   buttons[index].drawButton(true);
// }

// // Function to reset selection and return to the main menu
// void resetSelection() {
//   Serial.println("Returning to main menu...");
//   isMainMenu = true;
//   activeMainMenu = -1;
//   subMenuSelection = 0;
//   drawMainMenu();
// }

// // Function to draw the main menu
// void drawMainMenu() {
//   tft.fillScreen(TFT_WHITE);

//   mainButtons.clear(); // Clear existing buttons
//   for (int i = 0; i < mainButtonLabels.size(); i++) {
//     TFT_eSPI_Button button;
//     button.initButton(
//       &tft,
//       80, // Shifted left to make space for submenu
//       40 + i * (BUTTON_HEIGHT + BUTTON_GAP),
//       BUTTON_WIDTH,
//       BUTTON_HEIGHT,
//       TFT_BLUE,
//       BUTTON_COLOR,
//       TFT_WHITE,
//       (char*)mainButtonLabels[i], // Cast to char*
//       2
//     );
//     mainButtons.push_back(button);
//     mainButtons[i].drawButton(true);
//   }

//   // Highlight the current button
//   highlightButton(mainButtons, currentSelection);
// }

// // Function to draw a submenu
// void drawSubMenu(int menuIndex) {
//   tft.fillRect(160, 0, tft.width() - 160, tft.height(), TFT_WHITE);

//   if (subButtons.size() <= menuIndex) {
//     subButtons.resize(menuIndex + 1);
//   }

//   subButtons[menuIndex].clear(); // Clear existing submenu buttons
//   for (int i = 0; i < subButtonLabels[menuIndex].size(); i++) {
//     TFT_eSPI_Button button;
//     button.initButton(
//       &tft,
//       240, // Submenu positioned on the right
//       40 + i * (BUTTON_HEIGHT + BUTTON_GAP),
//       BUTTON_WIDTH,
//       BUTTON_HEIGHT,
//       TFT_BLUE,
//       BUTTON_COLOR,
//       TFT_WHITE,
//       (char*)subButtonLabels[menuIndex][i], // Cast to char*
//       2
//     );
//     subButtons[menuIndex].push_back(button);
//     subButtons[menuIndex][i].drawButton(true);
//   }

//   // Highlight the first button in the submenu
//   highlightButton(subButtons[menuIndex], subMenuSelection);
// }

}

