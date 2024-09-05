/*
*******************************************************************************
* Copyright (c) 2024 by serginator
*
* Mouse Jiggler
*
* Describe: M5Stack.
* Date: 2024/09/04
*******************************************************************************
*/

#include <M5Cardputer.h>
#include <USB.h>
#include <USBHIDMouse.h>

USBHIDMouse Mouse;

unsigned long lastMoveTime = 0;
unsigned long MIN_DELAY_MS = 60000;  // 1 minute
unsigned long MAX_DELAY_MS = 300000; // 5 minutes
unsigned long currentDelay = MIN_DELAY_MS;
bool jiggling = false;

bool upPressed = false, downPressed = false, leftPressed = false, rightPressed = false, enterPressed = false;

void updateDisplay() {
  M5Cardputer.Display.fillScreen(BLACK);
  M5Cardputer.Display.setCursor(0, 0);
  M5Cardputer.Display.setTextSize(2);
  M5Cardputer.Display.println("Mouse Jiggler");
  M5Cardputer.Display.println("Min: " + String(MIN_DELAY_MS / 60000) + " min");
  M5Cardputer.Display.println("Max: " + String(MAX_DELAY_MS / 60000) + " min");
  M5Cardputer.Display.println("Up/Down: +- Min");
  M5Cardputer.Display.println("Left/Right: +-Max");
  M5Cardputer.Display.println("Press OK to Jiggle");
}

void setup() {
  M5Cardputer.begin();
  USB.begin();
  Mouse.begin();

  Serial.begin(115200);
  Serial.println("Mouse Jiggler initialized");

  updateDisplay();
}

void loop() {
  M5Cardputer.update();

  if (!jiggling) {
    if (M5Cardputer.Keyboard.isKeyPressed(';') && !upPressed) {  // Up button
      MIN_DELAY_MS = min(MAX_DELAY_MS - 60000, MIN_DELAY_MS + 60000);
      updateDisplay();
      upPressed = true;
    } else if (!M5Cardputer.Keyboard.isKeyPressed(';')) {
      upPressed = false;
    }

    if (M5Cardputer.Keyboard.isKeyPressed('.') && !downPressed) {  // Down button
      MIN_DELAY_MS = max(60000UL, MIN_DELAY_MS - 60000);
      updateDisplay();
      downPressed = true;
    } else if (!M5Cardputer.Keyboard.isKeyPressed('.')) {
      downPressed = false;
    }

    if (M5Cardputer.Keyboard.isKeyPressed(',') && !leftPressed) {  // Left button
      MAX_DELAY_MS = max(MIN_DELAY_MS + 60000, MAX_DELAY_MS - 60000);
      updateDisplay();
      leftPressed = true;
    } else if (!M5Cardputer.Keyboard.isKeyPressed(',')) {
      leftPressed = false;
    }

    if (M5Cardputer.Keyboard.isKeyPressed('/') && !rightPressed) {  // Right button
      MAX_DELAY_MS = min(3600000UL, MAX_DELAY_MS + 60000);
      updateDisplay();
      rightPressed = true;
    } else if (!M5Cardputer.Keyboard.isKeyPressed('/')) {
      rightPressed = false;
    }

    if (M5Cardputer.Keyboard.isKeyPressed(0x28) && !enterPressed) {  // ENTER button
      jiggling = true;
      M5Cardputer.Display.fillScreen(BLACK);
      M5Cardputer.Display.setCursor(0, 0);
      M5Cardputer.Display.println("Jiggling...");
      M5Cardputer.Display.println("Min: " + String(MIN_DELAY_MS / 60000) + " min");
      M5Cardputer.Display.println("Max: " + String(MAX_DELAY_MS / 60000) + " min");
      M5Cardputer.Display.println("Press OK to Stop");
      enterPressed = true;
    } else if (!M5Cardputer.Keyboard.isKeyPressed(0x28)) {
      enterPressed = false;
    }
  } else {
    unsigned long currentTime = millis();

    if (currentTime - lastMoveTime >= currentDelay) {
      Mouse.move(2, 0);
      delay(500);
      Mouse.move(-2, 0);
      lastMoveTime = currentTime;

      currentDelay = random(MIN_DELAY_MS, MAX_DELAY_MS + 1);

      M5Cardputer.Display.fillScreen(BLACK);
      M5Cardputer.Display.setCursor(0, 0);
      M5Cardputer.Display.println("Mouse moved!");
      M5Cardputer.Display.print("Next move in: ");
      M5Cardputer.Display.print(currentDelay / 1000);
      M5Cardputer.Display.println(" seconds");
      Serial.println("Mouse moved");
      Serial.print("Next move in: ");
      Serial.print(currentDelay / 1000);
      Serial.println(" seconds");
    }
    if (M5Cardputer.Keyboard.isKeyPressed(0x28) && !enterPressed) {  // ENTER button to stop
      jiggling = false;
      updateDisplay();
      enterPressed = true;
    } else if (!M5Cardputer.Keyboard.isKeyPressed(0x28)) {
      enterPressed = false;
    }
  }
}
