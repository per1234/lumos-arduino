#include "defs.h"
#include "Action.h"
#include "Colors.h"
#include "Effect.h"
#include "Log.h"
#include "Runner.h"

int8_t const PIN = 13;
neoPixelType const STRIP_FLAGS = (NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip;

void setup() {
  // Initiate Serial communication.
  Serial.begin(9600);

  // Initialize the LED strip.
  strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, STRIP_FLAGS);
  strip.begin();
  strip.setBrightness(255);
  strip.show(); // Initialize all pixels to 'off'
}

PixelsArray pixels1;
//PixelsArray pixels2;
//PixelsArray pixels3;

void loop() {
  long startTime = millis();

  testBlink();
  
//  setGradient(pixels2, 7, VIOLET, INDIGO, BLUE, GREEN, YELLOW, ORANGE, RED);
//  //  setGradient(pixels2, 2, BLACK, BLUE);
//  reversePattern(pixels3, pixels2);
//  for (int ratio = 0; ratio <= 100; ratio += 3) {
//    blendPatterns(pixels, pixels2, pixels3, ratio);
//    applyPixels(pixels);
//    strip.show();
//    delay(20);
//  }
//  delay(1000);
//  for (int ratio = 0; ratio <= 100; ratio += 3) {
//    blendPatterns(pixels, pixels3, pixels2, ratio);
//    applyPixels(pixels);
//    strip.show();
//    delay(20);
//  }
//  delay(100);
//  rotateRight(3000, 20);
//  rotateLeft(250, 240);
//  delay(2000);
//
//    setSineWave(pixels, RED, BLUE, 60, 0);
//    applyPixels(pixels);
//    strip.show();
//    rotateRight(2000, 30);
//    delay(100);
//    rotateLeft(250, 240);
//    delay(1000);
//
//    setGradient(pixels, 7, VIOLET, INDIGO, BLUE, GREEN, YELLOW, ORANGE, RED);
//    applyPixels(pixels);
//    strip.show();
//    rotateRight(2000, 30);
//    delay(100);
//    rotateLeft(250, 240);
//    delay(1000);
//
//    fadeTo(1000, RED);
//    fadeTo(1000, WHITE);
//    fadeTo(1000, BLUE);
//
////    setGradient(3, RED, GREEN, BLUE);
////    delay(2000);
//
//    setSolidColor(pixels, BLACK);
//    setGradient(pixels, 3, RED, GREEN, BLUE);
//    applyPixels(pixels);
//    strip.show();
//    delay(2000);
//  
//    setSolidColor(pixels, BLACK);
//    setGradient(pixels, 3, RED, GREEN, RED);
//    applyPixels(pixels);
//    strip.show();
//    delay(2000);
//  
//  //  setSolidColor(BLACK);
//  //  setGradient(13, YELLOW, BLUE, YELLOW, RED, YELLOW, BLUE, YELLOW, RED, YELLOW, BLUE, YELLOW, RED, YELLOW);
//  //  strip.show();
//  //  delay(2000);

  long stopTime = millis();
  Log::logFloat((char*)"elapsed=", (stopTime - startTime) / 1000.0, 3);
  Log::logLn();
}

void testBlink() {
  // Operator new doesn't work right with virtual methods, use this workaround instead.
  // NOTE: Don't try to delete this object.
  Blink blink1(pixels1, 1000, 20, 25, PURPLE, CYAN);
  Blink blink2(pixels1, 1000, 40, 45, RED, ORANGE);
  FadeTo fader(pixels1, 5000, 0, 10, BLUE);
  Flicker flicker(Colors::blend(WHITE, YELLOW, 80));
  Fuse fuse(12);
  Rotate rotate(20, RIGHT);

  Patterns::setGradient(pixels1, 3, RED, GREEN, BLUE);
  Patterns::applyPixels(pixels1);
  strip.show();


  DualAction multiAction(&flicker, &blink1);

  fader.setup();
//  blink1.setup();
//  rotate.setup();
  fuse.setup();
//  Runner::runForDurationMS(2000, &flicker);
//  Runner::runForever(&blink1);
  Runner::runUntilDone(&fuse);
//  Runner::runUntilDone(&fader);
}

