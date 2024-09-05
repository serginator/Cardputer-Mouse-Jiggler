/*
*******************************************************************************
* Copyright (c) 2024 by serginator
*
* Cardputer Mouse Jiggler
*
* Describe: M5Stack Cardputer Mouse Jiggler
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

unsigned long jiggleCount = 0;

void updateDisplay() {
  M5Cardputer.Display.fillScreen(BLACK);
  M5Cardputer.Display.setCursor(0, 0);
  M5Cardputer.Display.setTextSize(1.3);
  M5Cardputer.Display.println("Mouse Jiggler 1.0");
  M5Cardputer.Display.println("");
  M5Cardputer.Display.println("Min: " + String(MIN_DELAY_MS / 60000) + " min");
  M5Cardputer.Display.println("Max: " + String(MAX_DELAY_MS / 60000) + " min");
  M5Cardputer.Display.println("");
  M5Cardputer.Display.println("Up/Down: +- Min");
  M5Cardputer.Display.println("Left/Right: +- Max");
  M5Cardputer.Display.println("Press OK to Jiggle");
  M5Cardputer.Display.setCursor(M5Cardputer.Display.width() - 95, M5Cardputer.Display.height() - 135);
  M5Cardputer.Display.printf("Battery: %d%%", M5Cardputer.Power.getBatteryLevel());
  M5Cardputer.Display.println("");
  M5Cardputer.Display.setCursor(M5Cardputer.Display.width() - 95, M5Cardputer.Display.height() - 120);
  M5Cardputer.Display.printf("Jiggles: %lu", jiggleCount);
}

void setup() {
  M5Cardputer.begin();
  USB.begin();
  Mouse.begin();

  Serial.begin(115200);
  Serial.println("Mouse Jiggler initialized");

  M5Cardputer.Display.setTextSize(1.3);
  M5Cardputer.Display.setCursor(0, 0);
  M5Cardputer.Display.println("    sjw       ..----.._    _");
  M5Cardputer.Display.println("            .' .--.    \"-.(O)_");
  M5Cardputer.Display.println("-.__.-'\"=:|  ,  _)_ \\__ . c\'-..");
  M5Cardputer.Display.println("             ''------'---''---'-");
  M5Cardputer.Display.println("");
  M5Cardputer.Display.println("");
  M5Cardputer.Display.println("Cardputer Mouse Jiggler 1.0");
  M5Cardputer.Display.println("");
  M5Cardputer.Display.println("by serginator");

  delay(3000);  // Show splash for 3 seconds
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
      currentDelay = random(MIN_DELAY_MS, MAX_DELAY_MS + 1);
      M5Cardputer.Display.fillScreen(BLACK);
      M5Cardputer.Display.setCursor(0, 0);
      M5Cardputer.Display.setTextSize(1.3);
      M5Cardputer.Display.println("Mouse Jiggler 1.0");
      M5Cardputer.Display.println("");
      M5Cardputer.Display.println("Jiggling...");
      M5Cardputer.Display.println("");
      M5Cardputer.Display.println("Min: " + String(MIN_DELAY_MS / 60000) + " min");
      M5Cardputer.Display.println("Max: " + String(MAX_DELAY_MS / 60000) + " min");
      M5Cardputer.Display.println("");
      M5Cardputer.Display.print("Next move in: ");
      M5Cardputer.Display.print(currentDelay / 1000);
      M5Cardputer.Display.println(" seconds");
      M5Cardputer.Display.println("");
      M5Cardputer.Display.println("Press OK to Stop");
      M5Cardputer.Display.setCursor(M5Cardputer.Display.width() - 95, M5Cardputer.Display.height() - 135);
      M5Cardputer.Display.printf("Battery: %d%%", M5Cardputer.Power.getBatteryLevel());
      M5Cardputer.Display.println("");
      M5Cardputer.Display.setCursor(M5Cardputer.Display.width() - 95, M5Cardputer.Display.height() - 120);
      M5Cardputer.Display.printf("Jiggles: %lu", jiggleCount);
      enterPressed = true;
    } else if (!M5Cardputer.Keyboard.isKeyPressed(0x28)) {
      enterPressed = false;
    }
  } else {
    unsigned long currentTime = millis();

    if (currentTime - lastMoveTime >= currentDelay) {
      Mouse.move(40, 0);
      delay(200);
      Mouse.move(-40, 0);
      lastMoveTime = currentTime;

      currentDelay = random(MIN_DELAY_MS, MAX_DELAY_MS + 1);

      M5Cardputer.Display.fillScreen(BLACK);
      M5Cardputer.Display.setCursor(0, 0);
      M5Cardputer.Display.setTextSize(1.3);
      M5Cardputer.Display.println("Mouse Jiggler 1.0");
      M5Cardputer.Display.println("");
      M5Cardputer.Display.println("Jiggling...");
      M5Cardputer.Display.println("");
      M5Cardputer.Display.println("Min: " + String(MIN_DELAY_MS / 60000) + " min");
      M5Cardputer.Display.println("Max: " + String(MAX_DELAY_MS / 60000) + " min");
      M5Cardputer.Display.println("");
      M5Cardputer.Display.println("Next move in: ");
      M5Cardputer.Display.print(currentDelay / 1000);
      M5Cardputer.Display.println(" seconds");
      M5Cardputer.Display.println("");
      M5Cardputer.Display.println("Press OK to Stop");
      jiggleCount++;

      M5Cardputer.Display.setCursor(M5Cardputer.Display.width() - 95, M5Cardputer.Display.height() - 135);
      M5Cardputer.Display.printf("Battery: %d%%", M5Cardputer.Power.getBatteryLevel());
      M5Cardputer.Display.println("");
      M5Cardputer.Display.setCursor(M5Cardputer.Display.width() - 95, M5Cardputer.Display.height() - 120);
      M5Cardputer.Display.printf("Jiggles: %lu", jiggleCount);
    }
    if (M5Cardputer.Keyboard.isKeyPressed(0x28) && !enterPressed) {  // ENTER button to stop
      jiggling = false;
      jiggleCount = 0;
      updateDisplay();
      enterPressed = true;
    } else if (!M5Cardputer.Keyboard.isKeyPressed(0x28)) {
      enterPressed = false;
    }
  }
}
