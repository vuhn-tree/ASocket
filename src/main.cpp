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

  // Get the number of available displays
  int display_count = M5.getDisplayCount();

  M5.Displays(0).setTextSize(1);

  // The primary display can be used with M5.Display.
  M5.Display.print("primary display\n");

  const int index_unit_oled = M5.getDisplayIndex(m5::board_t::board_M5UnitOLED);
  if (index_unit_oled >= 0) {
    M5.Displays(index_unit_oled).printf("This is Unit OLED num: %d\n", index_unit_oled);
  }

  vTaskDelay(5000);
}

// When creating a function for drawing, it can be used universally by accepting
// a LovyanGFX type as an argument.
void draw_function(LovyanGFX* gfx) {
  int x = rand() % gfx->width();
  int y = rand() % gfx->height();
  int r = (gfx->width() >> 4) + 2;
  uint32_t c = rand();
  gfx->fillRect(x - r, y - r, r * 2, r * 2, c);
}

void loop(void) {
  vTaskDelay(100);

  for (int i = 0; i < M5.getDisplayCount(); ++i) {
    int x = rand() % M5.Displays(i).width();
    int y = rand() % M5.Displays(i).height();
    int r = (M5.Displays(i).width() >> 4) + 2;
    uint32_t c = rand();
    M5.Displays(i).fillCircle(x, y, r, c);
  }

  for (int i = 0; i < M5.getDisplayCount(); ++i) {
    draw_function(&M5.Displays(i));
  }
}
