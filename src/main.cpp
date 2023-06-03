// // #include <Adafruit_NeoPixel.h>
// // #include <M5Atom.h>
// #include <GlobalDefines.h>

// // #include <M5UnitOLED.h>
// #include <M5Unified.h>

// // M5UnitOLED display;

// // M5Canvas canvas(&display);

// static constexpr char text[] = "Hello world !";

// // Adafruit_NeoPixel pixels = Adafruit_NeoPixel(
// //     NUMPIXELS, PIN,
// //     NEO_GRB + NEO_KHZ800);  // set number of LEDs, pin number, LED type.

// void setup() {
//   auto cfg = M5.config();
//     cfg.external_display.unit_oled      = true;  // default=true. use
//     UnitOLED
//   M5.begin(cfg);

//   // Get the number of available displays
//   int display_count = M5.getDisplayCount();

//   for (int i = 0; i < display_count; ++i) {
//   // All displays are available in M5.Displays.
//   // ※ Note that the order of which displays are numbered is the order in
//   which they are detected, so the order may change.

//     int textsize = M5.Displays(i).height() / 60;
//     if (textsize == 0) { textsize = 1; }
//     M5.Displays(i).setTextSize(textsize);
//     M5.Displays(i).printf("No.%d\n", i);
//   }

//   M5.setPrimaryDisplayType( {
//       m5::board_t::board_M5ModuleDisplay,
//       m5::board_t::board_M5AtomDisplay,
//     m5::board_t::board_M5UnitOLED,
//   } );
//   int index_unit_oled = M5.getDisplayIndex(m5::board_t::board_M5UnitOLED);
//   if (index_unit_oled >= 0) {
//     M5.Displays(index_unit_oled).print("This is Unit OLED\n");
//   }

//     vTaskDelay(5000);

//   M5.begin();      // Init M5Atom
//   // pixels.begin();  // Init the NeoPixel library
// }

// // // Input a value 0 to 255 to get a color value.
// // // The colours are a transition r - g - b - back to r.
// // uint32_t Wheel(byte WheelPos) {
// //   WheelPos = 255 - WheelPos;
// //   if (WheelPos < 85) {
// //     return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
// //   }
// //   if (WheelPos < 170) {
// //     WheelPos -= 85;
// //     return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
// //   }
// //   WheelPos -= 170;
// //   return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
// // }

// // void rainbow(uint8_t wait) {
// //   uint16_t i, j;

// //   for (j = 0; j < 256; j++) {
// //     for (i = 0; i < pixels.numPixels(); i++) {
// //       pixels.setPixelColor(i, Wheel((i + j) & 255));
// //       while (M5.Btn.read() == 1)
// //         ;
// //     }
// //     pixels.show();
// //     delay(wait);
// //   }
// // }

// void loop() {
//   // rainbow(20);
// }

#if defined(ARDUINO)

#include <Arduino.h>
#include <SD.h>
#include <SPIFFS.h>

#endif

#include <M5UnitOLED.h>
#include <M5Unified.h>

void setup(void) {
  auto cfg = M5.config();

  // external display setting. (Pre-include required)

  cfg.external_display.unit_oled = true;  // default=true. use UnitOLED

  /*
   Display with auto-detection
   - module_display
   - atom_display
   - unit_glass
   - unit_oled
   - unit_lcd

   Displays that cannot be auto-detected
   - module_rca
   - unit_rca

  ※ Note that if you enable a display that cannot be auto-detected,
     it will operate as if it were connected, even if it is not actually
  connected. When RCA is enabled, it consumes a lot of memory to allocate the
  frame buffer.
  //*/

  // begin M5Unified.
  M5.begin(cfg);

  // Get the number of available displays
  int display_count = M5.getDisplayCount();

  for (int i = 0; i < display_count; ++i) {
    // All displays are available in M5.Displays.
    // ※ Note that the order of which displays are numbered is the order in
    // which they are detected, so the order may change.

    int textsize = M5.Displays(i).height() / 60;
    if (textsize == 0) {
      textsize = 1;
    }
    M5.Displays(i).setTextSize(textsize);
    M5.Displays(i).printf("No.%d\n", i);
  }

  // If an external display is to be used as the main display, it can be listed
  // in order of priority.
  M5.setPrimaryDisplayType({
      m5::board_t::board_M5ModuleDisplay, m5::board_t::board_M5AtomDisplay,
      //    m5::board_t::board_M5UnitOLED,
  });

  // The primary display can be used with M5.Display.
  M5.Display.print("primary display\n");

  // Examine the indexes of a given type of display
  int index_module_display =
      M5.getDisplayIndex(m5::board_t::board_M5ModuleDisplay);
  int index_atom_display = M5.getDisplayIndex(m5::board_t::board_M5AtomDisplay);
  int index_module_rca = M5.getDisplayIndex(m5::board_t::board_M5ModuleRCA);
  int index_unit_glass = M5.getDisplayIndex(m5::board_t::board_M5UnitGLASS);
  int index_unit_oled = M5.getDisplayIndex(m5::board_t::board_M5UnitOLED);
  int index_unit_lcd = M5.getDisplayIndex(m5::board_t::board_M5UnitLCD);
  int index_unit_rca = M5.getDisplayIndex(m5::board_t::board_M5UnitRCA);

  if (index_unit_oled >= 0) {
    M5.Displays(index_unit_oled).print("This is Unit OLED\n");
  }
  vTaskDelay(50000);
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
  vTaskDelay(1);

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
