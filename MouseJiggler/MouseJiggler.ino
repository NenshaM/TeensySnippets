/*
  ============================================================
   Human-Like Mouse Jiggler for Teensy 3.1 (USB HID)
  ============================================================

  Board Setting:
    Tools > USB Type > Keyboard + Mouse + Joystick

  Description:
    This sketch simulates subtle, human-like mouse movement
    at random intervals to prevent a computer from going idle.

    Features:
      - Random 1–4 minute delays between movements
      - 20% chance to skip a cycle (more human behavior)
      - Small ±1 pixel movements
      - Optional debug output
      - Fully configurable timing and behavior

  Note:
    - Press the reset button before flashing
    - Arduino IDE 2.3.7

  Author: NenshaM
  License: GPL v3
  Version: 1.0.0
  ============================================================
*/

#include <Mouse.h>

// ================= USER CONFIGURATION =================

// Enable serial debug output
const bool DEBUG_MODE = false;

// Delay range between movements (milliseconds)
const unsigned long MIN_DELAY = 60000UL;        // 1 minute
const unsigned long MAX_DELAY = 4 * 60000UL;    // 4 minutes

// Chance (percentage) to skip a movement cycle
const int SKIP_PROBABILITY = 20;  // 20%

// Maximum pixel movement per axis (-STEP to +STEP)
const int STEP = 1;

// ======================================================

void setup() {

  if (DEBUG_MODE) {
    Serial.begin(115200);
    delay(1000);
    Serial.println("Mouse Jiggler Started");
  }

  // Seed random generator using floating analog pin
  randomSeed(analogRead(0));

  Mouse.begin();
}

void loop() {

  // Random delay before action
  unsigned long waitTime = random(MIN_DELAY, MAX_DELAY);
  
  if (DEBUG_MODE) {
    Serial.print("Waiting ");
    Serial.print(waitTime / 1000);
    Serial.println(" seconds...");
  }

  delay(waitTime);

  // Random chance to skip movement (human-like behavior)
  if (random(0, 100) < SKIP_PROBABILITY) {
    if (DEBUG_MODE) {
      Serial.println("Cycle skipped.");
    }
    return;
  }

  // Generate small random movement
  int dx = random(-STEP, STEP + 1);
  int dy = random(-STEP, STEP + 1);

  // Avoid 0,0 (no movement)
  if (dx == 0 && dy == 0) {
    dx = 1;
  }

  if (DEBUG_MODE) {
    Serial.print("Moving: dx=");
    Serial.print(dx);
    Serial.print(" dy=");
    Serial.println(dy);
  }

  // Perform movement
  Mouse.move(dx, dy);
}
