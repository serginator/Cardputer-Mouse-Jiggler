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

#include <M5Unified.h>
#include <USB.h>
#include <USBHIDMouse.h>

USBHIDMouse Mouse;

unsigned long lastMoveTime = 0;
const unsigned long MIN_DELAY_MS = 240000; // 4 minutes
const unsigned long MAX_DELAY_MS = 300000; // 5 minutes
unsigned long currentDelay = MIN_DELAY_MS;

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);

  M5.Display.setTextSize(2);
  M5.Display.println("M5Cardputer Mouse Jiggler");
  M5.Display.println("starting...");

  USB.begin();
  Mouse.begin();

  Serial.begin(115200);
  Serial.println("Mouse Jiggler initialized");

  randomSeed(analogRead(0));
}

void loop() {
  M5.update();

  unsigned long currentTime = millis();

  if (currentTime - lastMoveTime >= currentDelay) {
    Mouse.move(2, 0);
    delay(500);
    Mouse.move(-2, 0);
    lastMoveTime = currentTime;

    currentDelay = random(MIN_DELAY_MS, MAX_DELAY_MS + 1);

    M5.Display.fillScreen(BLACK);
    M5.Display.setCursor(0, 0);
    M5.Display.println("Mouse moved!");
    M5.Display.print("Next move in: ");
    M5.Display.print(currentDelay / 1000);
    M5.Display.println(" seconds");
    Serial.println("Mouse moved");
    Serial.print("Next move in: ");
    Serial.print(currentDelay / 1000);
    Serial.println(" seconds");
  }
}
