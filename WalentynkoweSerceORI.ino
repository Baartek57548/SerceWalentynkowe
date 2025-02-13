#include <Adafruit_NeoPixel.h>

#define PIN 0           // Pin sterujący
#define NUMPIXELS 18    // Liczba diod

uint8_t randomValue1, randomValue2, randomValue3;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);



void setup() {
  strip.begin();
  strip.show();


  heartbeatEffect(10);

  sparkleEffect(20, 2, 1);

  strip.setBrightness(255);

  colorWipe(strip.Color(255, 0, 0), 30);
  colorWipe(strip.Color(0, 255, 0), 30);
  colorWipe(strip.Color(0, 0, 255), 30);

  for (int p = 0; p <= 4; p++) {
    RndX(randomValue1, randomValue2, randomValue3);
    theaterChase(strip.Color(randomValue1, randomValue2, randomValue3), 100);
  }

  ledChaser(30, 2);
  ledChaserReverse(30, 2);

  theaterChaseRainbow(20);

  rainbowCycleReverse(10);
  gradientEffect(strip.Color(255, 20, 0), strip.Color(0, 255, 20), 10, 100);
}


void loop() {

  theaterChaseRainbow(90);
  for (int r = 0; r <= 10; r++) {
    RndX(randomValue1, randomValue2, randomValue3);
    gradientEffect(strip.Color(randomValue1, randomValue3, randomValue2), strip.Color(randomValue3, randomValue2, randomValue1), 5, 300);
  }
  for (int z = 0; z <= 20; z++) {
    RndX(randomValue1, randomValue2, randomValue3);
    colorWipe(strip.Color(randomValue1, randomValue2, randomValue3), 30);
  }

  for (int t = 0; t <= 20; t++) {
    rainbowCycleReverse(40);
  }
  for (int g = 0; g <= 20; g++) {
    ledChaser(50, 1);
    ledChaserReverse(50, 1);
  }
  sparkleEffect(30, 10, 30);
}
void RndX(uint8_t &randomValue1, uint8_t &randomValue2, uint8_t &randomValue3) {
  randomValue1 = random(0, 255);
  randomValue2 = random(0, 255);
  randomValue3 = random(0, 255);
}


void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
void heartbeatEffect(int reps) {
  for (int beat = 0; beat < reps; beat++) {
    strip.setBrightness(255);
    for (int i = 0; i < NUMPIXELS; i++) {
      strip.setPixelColor(i, strip.Color(255, 0, 0));
    }
    strip.show();
    delay(100);
    strip.clear();
    strip.show();
    delay(150);
    for (int i = 0; i < NUMPIXELS; i++) {
      strip.setPixelColor(i, strip.Color(150, 0, 0));
    }
    strip.show();
    delay(120);

    strip.clear();
    strip.show();
    delay(300);
  }
}
void sparkleEffect(int repets, int del1, int del2) {
  for (int k = 0; k <= repets; k++) {
    strip.clear();
    int idx = random(NUMPIXELS);
    int choice1 = random(0, 255);
    int choice2 = random(0, 255);
    int choice3 = random(0, 255);

    for (int jasnosc = 0; jasnosc <= 254; jasnosc = jasnosc + 5) {
      strip.setBrightness(jasnosc);
      strip.setPixelColor(idx, strip.Color(choice1, choice2, choice3));
      strip.show();
      delay(del2);
      strip.clear();
    }
    for (int jasnosc = 254; jasnosc >= 0; jasnosc = jasnosc - 5) {
      strip.setBrightness(jasnosc);
      strip.setPixelColor(idx, strip.Color(choice1, choice2, choice3));
      strip.show();
      delay(del2);
      strip.clear();
    }
    delay(del1);
  }
}
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
void rainbowCycleReverse(uint8_t wait) {
  uint16_t i, j;
  for (j = 0; j < 256 * 5; j++) { 
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) - j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
void gradientEffect(uint32_t colorStart, uint32_t colorEnd, uint8_t del, int wait) {
  uint8_t rStart = (colorStart >> 16) & 0xFF;
  uint8_t gStart = (colorStart >> 8) & 0xFF;
  uint8_t bStart = colorStart & 0xFF;

  uint8_t rEnd = (colorEnd >> 16) & 0xFF;
  uint8_t gEnd = (colorEnd >> 8) & 0xFF;
  uint8_t bEnd = colorEnd & 0xFF;

  uint8_t num = NUMPIXELS - 1;

  for (uint16_t i = 0; i < NUMPIXELS; i++) {
    uint16_t ratio = ((uint16_t)i * 255) / num;

    uint8_t r = rStart + (((int)rEnd - rStart) * ratio) / 255;
    uint8_t g = gStart + (((int)gEnd - gStart) * ratio) / 255;
    uint8_t b = bStart + (((int)bEnd - bStart) * ratio) / 255;

    // Rozjaśnianie diody od 0 do 255
    for (int brightness = 0; brightness <= 255; brightness += 5) {
      uint8_t rScaled = (r * brightness) / 255;
      uint8_t gScaled = (g * brightness) / 255;
      uint8_t bScaled = (b * brightness) / 255;

      strip.setPixelColor(i, strip.Color(rScaled, gScaled, bScaled));
      strip.show();
      delay(del);
    }
  }

  delay(wait);
}

void theaterChase(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) {
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, c);
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0); 
      }
    }
  }
}
void ledChaser(uint8_t wait, int rep) {
  const uint16_t numLeds = strip.numPixels();

  // Włącz pierwszy LED
  strip.setPixelColor(0, randomValue1);
  strip.show();
  delay(wait);

  for (int l = 0; l <= rep; l++) {
    for (uint16_t i = 1; i < numLeds; i++) {
      strip.setPixelColor(i, randomValue2); 
      strip.setPixelColor(i - 1, 0); 
      strip.show();
      delay(wait);
    }
    strip.setPixelColor(numLeds - 1, 0);
    strip.show();
    delay(wait);
  }
}

void ledChaserReverse(uint8_t wait, int rep) {
  uint16_t numLeds = strip.numPixels();

  strip.setPixelColor(numLeds, randomValue3);
  strip.show();
  delay(wait);
  for (int l = rep; l >= 0; l--) {
    for (int i = numLeds; i >= 0; i--) {
      strip.setPixelColor(i, randomValue1);
      strip.setPixelColor(i + 1, 0);
      strip.show();
      strip.setPixelColor(0, 0);
      strip.show();
      delay(wait);
    }
  }
}
void theaterChaseRainbow(uint8_t wait) {
  for (int j = 0; j < 256; j++) {
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, Wheel((i + j) % 255));
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);
      }
    }
  }
  strip.clear();
}
