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

#define NUM_LEDS        50
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
    delay(20);
}


void doSomething(int var) {
    switch (var) {
    case 0:
//        colorFill(CRGB(58, 30, 4), 0);
        colorFill(CRGB(3,1,0), 0);
        break;
    case 1:
//        colorWipe(CRGB(60, 20, 0), max(0xff - counter*10,10));
//        colorWipe(CRGB(counter & 0x1f,(counter >> 5) & 0x3,0), 100);

        colorWipe(CRGB(240, 80, 0), max(0xff - counter*10,10));
        break;
    default:
        mode = 0;
        break;
    }
    
    counter += dir;
}

// PATTERN FUNCTIONS
// Created, or adapted from Adafruit and Funkboxing!

// Fill the dots one after the other with a color
void colorWipe(CRGB c, uint8_t wait) {
  if (counter < NUM_LEDS) {
    leds[counter] = c;
    FastLED.show();
  }
  delay(wait);
}

// Fill the entire strip with a single color at once
void colorFill(CRGB c, uint8_t wait) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = c;
  }
  FastLED.show();
  delay(wait);
}


void rainbow(uint8_t wait) {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = Wheel((i + counter) & 255);
    }
    FastLED.show();
    delay(wait);
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = Wheel(((i * 256 / NUM_LEDS) + counter) & 255);
    }
    FastLED.show();
    delay(wait);
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
CRGB Wheel(byte WheelPos) {
  return CHSV(WheelPos, 255, 255);
}

void chaseLights(CRGB c1, CRGB c2, int wait) { //-POLICE LIGHTS (TWO COLOR SINGLE LED)
    if (counter >= NUM_LEDS) {
        counter = 0;
    }
    int idexR = counter;
    int idexB = antipodal_index(idexR);
    for (int i = 0; i < NUM_LEDS; i++) {
        if (i == idexR) {
            leds[i] = c1;
        } else if (i == idexB) {
            leds[i] = c2;
        } else {
            leds[i] = CRGB::Black;
        }
    }
    FastLED.show();
    delay(wait);
}

void chaseLightsOddEven(int wait) { //-POLICE LIGHTS (TWO COLOR ODD/EVEN)
  for (int i = 0; i < NUM_LEDS; i++) {
    if (counter & 1 && i & 1) {
      leds[i] = CRGB::Red;
    } else if (((counter|i) & 1) == 0) {
      leds[i] = CRGB::Blue;
    } else {
      leds[i] = CRGB::Black;
    }
  }
  FastLED.show();
  delay(wait);
}

void twinkle(CRGB base, CRGB twinkle, int wait) {
    leds[random(NUM_LEDS)] = twinkle;
    FastLED.show();
    delay(wait);
    colorFill(base, random(30,500));
}

void randomize(int minHue, int maxHue, int minVal, int maxVal, int wait) {
  for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(random(minHue,maxHue), 255, random(minVal,maxVal));
  }    
  FastLED.show();
  delay(wait);
}

// This table generated from: sin((6.28/30)*(float)(counter)) *255;
static const uint8_t brightnessTable[] = {0,52,103,149,189,220,242,253,253,242,220,189,150,104,53,0};
void sineFirefly(int wait) {
  static int myPix = 0;
  if(counter < sizeof(brightnessTable)) {
    leds[myPix] = CHSV(brightnessTable[counter], brightnessTable[counter], brightnessTable[counter]);
    
    FastLED.show();
    delay(wait);
  } else {
    myPix = random(0,NUM_LEDS);
    counter = 0;
    colorFill(0,0);
  }
}

void colorFirefly(int wait) {
  static int myPix = 0;
  if(counter < sizeof(brightnessTable)) {
    leds[myPix] = CHSV(60, 255, brightnessTable[counter]);
//    leds[myPix] = CHSV((256/sizeof(brightnessTable))*counter, 255, brightnessTable[counter]);
    
    FastLED.show();
    delay(wait);
  } else {
    if (random(20) == 0) {
      myPix = random(0,NUM_LEDS);
      counter = 0;
      colorFill(0,0);
    } else {
      delay(wait);
    }
  }
}



// HELPER FUNCTIONS, DERIVED FROM FUNKBOXING FAST_SPI!
// YAYAYAYAYAYYAYA

// antipodal point
int antipodal_index(int i) {
    //int N2 = int(NUM_LEDS/2);
    int iN = i + NUM_LEDS / 2;
    if (i >= (NUM_LEDS / 2)) {
        iN = (i + (NUM_LEDS / 2)) % NUM_LEDS;
    }
    return iN;
}
