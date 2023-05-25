// #include <Adafruit_NeoPixel.h>
// #include <M5Atom.h>
#include <GlobalDefines.h>

// #include <M5UnitOLED.h>
#include <M5Unified.h>

// M5UnitOLED display;

// M5Canvas canvas(&display);

static constexpr char text[] = "Hello world !";

// Adafruit_NeoPixel pixels = Adafruit_NeoPixel(
//     NUMPIXELS, PIN,
//     NEO_GRB + NEO_KHZ800);  // set number of LEDs, pin number, LED type.

void setup() {
  auto cfg = M5.config();
  cfg.external_display.unit_lcd       = true;  // default=true. use UnitLCD
  M5.begin(cfg);

  // Get the number of available displays
  int display_count = M5.getDisplayCount();

  for (int i = 0; i < display_count; ++i) {
  // All displays are available in M5.Displays.
  // ※ Note that the order of which displays are numbered is the order in which they are detected, so the order may change.

    int textsize = M5.Displays(i).height() / 60;
    if (textsize == 0) { textsize = 1; }
    M5.Displays(i).setTextSize(textsize);
    M5.Displays(i).printf("No.%d\n", i);
  }

  M5.setPrimaryDisplayType( {
      m5::board_t::board_M5ModuleDisplay,
      m5::board_t::board_M5AtomDisplay,
    m5::board_t::board_M5UnitOLED,
  } );


  // M5.begin();      // Init M5Atom
  // pixels.begin();  // Init the NeoPixel library
}

// // Input a value 0 to 255 to get a color value.
// // The colours are a transition r - g - b - back to r.
// uint32_t Wheel(byte WheelPos) {
//   WheelPos = 255 - WheelPos;
//   if (WheelPos < 85) {
//     return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
//   }
//   if (WheelPos < 170) {
//     WheelPos -= 85;
//     return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
//   }
//   WheelPos -= 170;
//   return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
// }

// void rainbow(uint8_t wait) {
//   uint16_t i, j;

//   for (j = 0; j < 256; j++) {
//     for (i = 0; i < pixels.numPixels(); i++) {
//       pixels.setPixelColor(i, Wheel((i + j) & 255));
//       while (M5.Btn.read() == 1)
//         ;
//     }
//     pixels.show();
//     delay(wait);
//   }
// }

void loop() { 
  // rainbow(20); 
}
