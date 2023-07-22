#if defined(ARDUINO)

#include <Arduino.h>
#include <SD.h>
#include <SPIFFS.h>

#endif

#include <Adafruit_NeoPixel.h>
#include <GlobalDefines.h>
#include <M5UnitOLED.h>

// NOTE: include this last
#include <M5Unified.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(
    NUMPIXELS, PIN,
    NEO_GRB + NEO_KHZ800);  // set number of LEDs, pin number, LED type.

void setup(void) {
  auto cfg = M5.config();
  cfg.external_display.unit_oled = true;

  // begin M5Unified.
  M5.begin(cfg);

  pixels.begin();  // Init the NeoPixel library
  pixels.setBrightness(10);
  pixels.setPixelColor(0, 0, 255, 0);
  pixels.show();

  M5.Display.setTextSize(1);

  // MUST SET ROTATION TO 3, other options overlap
  M5.Display.setRotation(3);
  M5.Display.print("New line\n");

  vTaskDelay(5000);
}

void draw_function(LovyanGFX* const gfx) {
  int x = rand() % gfx->width();
  int y = rand() % gfx->height();
  int r = (gfx->width() >> 4) + 2;
  uint32_t c = rand();
  gfx->fillRect(x - r, y - r, r * 2, r * 2, c);
}

void loop(void) {
  vTaskDelay(100);

  M5.Display.fillCircle(0, 0, 10, 255);
  M5.Display.drawCircle(10, 10, 10, 255);
}
