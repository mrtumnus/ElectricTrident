#include <FastLED.h> 
#include <CapacitiveSensor.h>

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)

#define NUM_LEDS      10
#define LED_DATA_PIN  4
#define NUM_MODES     12

// USER VARS
int mode = 0;

// INIT STUFF

int idex = 0;
int j = 0;
unsigned long mark;
int direct = 1;
int counter = 0;
int TOP_INDEX = 3;
int BOTTOM_INDEX = 0;
int EVENODD = 6 % 2;
int direction = 1;

// Start Sensor
CapacitiveSensor cs1 = CapacitiveSensor(0, 1); // 10M resistor between pins 0 & 1

// Start Strip
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2811, LED_DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
    long total1 = cs1.capacitiveSensor(30);    
    if (total1 > 300 && (millis() - mark) > 800) {
      j = 0;
      mark = millis();
      mode++;
    }
    // if mode greater than NUM_MODES reset
    if (mode > NUM_MODES) { mode = 0; }
    // main function
    doSomething(mode);
}


void doSomething(int var) {
    switch (var) {
    case 0:
        colorFill(CRGB::Black, 0);
        break;
    case 1:
        colorFill(CRGB::White, 0);
        break;
    case 2:
        colorFill(CRGB(255, 147, 41), 0); // soft-white
        break;
    case 3:
        flame();
        break; 
    case 4:
        twinkle(CRGB(0, 0, 31), CRGB::White, 50);
        break;
    case 5:
        chaseLights(100);
        break;  
    case 6:
        rainbow(50);
        break;
    case 7:
        rainbow(1);
        break;
    case 8:
        rainbowCycle(10);
        break;
    case 9:
        totallyRandom();
        break;
    case 10:
        colorWipe(CRGB(random(255), random(255), random(255)), 100); 
        break;
//    case 11:
//        sineFirefly(70);
//        counter++;
//        break;  
//    case 12:
//        colorFirefly(100);
//        counter++;
//        chaseLightsOddEven(100);
//        break;
    default:
        mode++;
        break;
    }
    
    if (j > 254) {
        direction = -1;
    }
    if (j < 1) {
        direction = 1;
    }

    j += direction;
}

// PATTERN FUNCTIONS
// Created, or adapted from Adafruit and Funkboxing!

// Fill the dots one after the other with a color
void colorWipe(CRGB c, uint8_t wait) {
  static int nextLed = 0;
  static CRGB color = c;

  leds[nextLed] = color;
  FastLED.show();
  delay(wait);

  if (++nextLed > NUM_LEDS) {
    nextLed = 0;
    color = c;
  }
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
    uint8_t i;

    for (i = 0; i < NUM_LEDS; i++) {
        leds[i] = Wheel((i + j) & 255);
    }
    FastLED.show();
    delay(wait);
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
    uint8_t i;

    for (i = 0; i < NUM_LEDS; i++) {
        leds[i] = Wheel(((i * 256 / NUM_LEDS) + j) & 255);
    }
    FastLED.show();
    delay(wait);
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
CRGB Wheel(byte WheelPos) {
    if (WheelPos < 85) {
        return CRGB(WheelPos * 3, 255 - WheelPos * 3, 0);
    } else if (WheelPos < 170) {
        WheelPos -= 85;
        return CRGB(255 - WheelPos * 3, 0, WheelPos * 3);
    } else {
        WheelPos -= 170;
        return CRGB(0, WheelPos * 3, 255 - WheelPos * 3);
    }
}

void chaseLights(int wait) { //-POLICE LIGHTS (TWO COLOR SINGLE LED)
    idex++;
    if (idex >= NUM_LEDS) {
        idex = 0;
    }
    int idexR = idex;
    int idexB = antipodal_index(idexR);
    for (int i = 0; i < NUM_LEDS; i++) {
        if (i == idexR) {
            leds[i] = CRGB::Red;
        } else if (i == idexB) {
            leds[i] = CRGB::Blue;
        } else {
            leds[i] = CRGB::Black;
        }
    }
    FastLED.show();
    delay(wait);
}

void chaseLightsOddEven(int wait) { //-POLICE LIGHTS (TWO COLOR ODD/EVEN)
  for (int i = 0; i < NUM_LEDS; i++) {
    if (j & 1 && i & 1) {
      leds[i] = CRGB::Red;
    } else if (((j|i) & 1) == 0) {
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


void flame() {
    int idelay = random(30, 80);

    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(random(11,34), 255, random(200,255));
    }    
    FastLED.show();
    delay(idelay);
   
}

int lastPix=0; int myPix=0;
void sineFirefly(int wait) {
        if(myPix != lastPix) {
          if(counter<16) {
            float colorV = sin((6.28/30)*(float)(counter)) *255;
            leds[myPix] = CRGB(colorV,colorV,colorV);

            FastLED.show();
            delay(wait);
          } else {
            lastPix=myPix;
            counter=0;
            colorFill(0,0);
          }
        } else {
          myPix=random(0,NUM_LEDS);
        }
	
}

void totallyRandom() {
        for (int i = 0; i < NUM_LEDS; i++) {
           leds[i] = CHSV(random(0,359), 255, 255);
        }
        FastLED.show();
        delay(50);
}

void colorFirefly(int wait) {
        if(myPix != lastPix) {
          if(counter<16) {
            float colorV = sin((6.28/30)*(float)(counter)) *255;
            leds[myPix] = CHSV((359/16)*counter, 255, colorV);
            
            FastLED.show();
            delay(wait);
          } else {
            lastPix=myPix;
            counter=0;
            colorFill(0,0);
          }
        } else {
          myPix=random(0,NUM_LEDS);
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

// horizontal index
int horizontal_index(int i) {
    //-ONLY WORKS WITH INDEX < TOPINDEX
    if (i == BOTTOM_INDEX) {
        return BOTTOM_INDEX;
    }
    if (i == TOP_INDEX && EVENODD == 1) {
        return TOP_INDEX + 1;
    }
    if (i == TOP_INDEX && EVENODD == 0) {
        return TOP_INDEX;
    }
    return 6 - i;
}
