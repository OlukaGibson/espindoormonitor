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
