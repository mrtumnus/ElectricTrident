#include <FastLED.h>
#include <trident.h>
#include <tridentanimation.h>

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)

#define NUM_LEDS        Trident::NUM_LEDS
#define PIN_LEDS_MOSI   0
#define PIN_BUTTON      3
#define PIN_LED         4

// USER VARS
int mode = 0;

// INIT STUFF

uint8_t counter = 0;
int dir = 1;

// Start Strip
CRGB leds[NUM_LEDS];
Trident trident(leds);
TridentAnimation animation(&trident);

void setup() {
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_LED, OUTPUT);
  FastLED.addLeds<WS2811, PIN_LEDS_MOSI>(leds, NUM_LEDS);
}

void loop() {
    static unsigned long lastButtonTime = 0;
    int buttonVal = digitalRead(PIN_BUTTON);
    digitalWrite(PIN_LED, buttonVal);

    // Button press with debounce
    if ((buttonVal == LOW) && (millis() - lastButtonTime) > 2000) {
      lastButtonTime = millis();
      animation.reset();
    }

    animation.step();
    FastLED.show();
    delay(10);
}
