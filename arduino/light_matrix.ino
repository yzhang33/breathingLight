#include <FastLED.h>

#define LED_PIN1 5
#define NUM_LEDS1 60

#define LED_PIN2 6
#define NUM_LEDS2 255

CRGB leds1[NUM_LEDS1];
CRGB leds2[NUM_LEDS2];

uint8_t gBrightness = 128;

int counter=1;

byte levelTable[256];
int change = 1;
int fadeIncremet = 10;
int currentLevel = 1; // current light level

int i=0;
boolean fadeUp = true;

void setup() {
  //pinMode(5,OUTPUT);
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, LED_PIN1>(leds1, NUM_LEDS1);
  FastLED.addLeds<WS2812B, LED_PIN2>(leds2, NUM_LEDS2);
  //initGridPosition();
  fillLevelTable();
}

void loop(){
  for(i=0;i+2<NUM_LEDS1;i++){
    leds1[i] = CRGB (207,60,245);
    leds1[i+1] = CRGB (207,60,245);
    leds1[i+2] = CRGB (207,60,245);
    FastLED.show();
    leds1[i] = CRGB (0,0,0);
    leds1[i+1] = CRGB (0,0,0);
    leds1[i+2] = CRGB (0,0,0);
    
    fadeMatrix();
    delay(100);
  }
  fadeUp = !fadeUp;
}

void fadeMatrix(){
  mapLEDXY(0,5,207,60,245);mapLEDXY(0,6,207,60,245);mapLEDXY(0,7,207,60,245);mapLEDXY(1,4,207,60,245);mapLEDXY(1,5,207,60,245);mapLEDXY(1,6,207,60,245);mapLEDXY(1,7,207,60,245);mapLEDXY(1,8,207,60,245);mapLEDXY(1,9,207,60,245);mapLEDXY(2,3,207,60,245);mapLEDXY(2,4,207,60,245);mapLEDXY(2,5,207,60,245);mapLEDXY(2,6,207,60,245);mapLEDXY(2,7,207,60,245);mapLEDXY(2,8,207,60,245);mapLEDXY(2,9,207,60,245);mapLEDXY(2,10,207,60,245);mapLEDXY(3,2,207,60,245);mapLEDXY(3,3,207,60,245);mapLEDXY(3,4,207,60,245);mapLEDXY(3,5,207,60,245);mapLEDXY(3,6,207,60,245);mapLEDXY(3,7,207,60,245);mapLEDXY(3,8,207,60,245);mapLEDXY(3,9,207,60,245);mapLEDXY(3,10,207,60,245);mapLEDXY(3,11,207,60,245);mapLEDXY(4,1,207,60,245);mapLEDXY(4,2,207,60,245);mapLEDXY(4,3,207,60,245);mapLEDXY(4,4,207,60,245);mapLEDXY(4,5,207,60,245);mapLEDXY(4,6,207,60,245);mapLEDXY(4,7,207,60,245);mapLEDXY(4,8,207,60,245);mapLEDXY(4,9,207,60,245);mapLEDXY(4,10,207,60,245);mapLEDXY(4,11,207,60,245);mapLEDXY(4,12,207,60,245);mapLEDXY(5,1,207,60,245);mapLEDXY(5,2,207,60,245);mapLEDXY(5,3,207,60,245);mapLEDXY(5,4,207,60,245);mapLEDXY(5,5,207,60,245);mapLEDXY(5,6,207,60,245);mapLEDXY(5,7,207,60,245);mapLEDXY(5,8,207,60,245);mapLEDXY(5,9,207,60,245);mapLEDXY(5,10,207,60,245);mapLEDXY(5,11,207,60,245);mapLEDXY(5,12,207,60,245);mapLEDXY(6,1,207,60,245);mapLEDXY(6,2,207,60,245);mapLEDXY(6,3,207,60,245);mapLEDXY(6,4,207,60,245);mapLEDXY(6,5,207,60,245);mapLEDXY(6,6,207,60,245);mapLEDXY(6,7,207,60,245);mapLEDXY(6,8,207,60,245);mapLEDXY(6,9,207,60,245);mapLEDXY(6,10,207,60,245);mapLEDXY(6,11,207,60,245);mapLEDXY(6,12,207,60,245);mapLEDXY(7,1,207,60,245);mapLEDXY(7,2,207,60,245);mapLEDXY(7,3,207,60,245);mapLEDXY(7,4,207,60,245);mapLEDXY(7,5,207,60,245);mapLEDXY(7,6,207,60,245);mapLEDXY(7,7,207,60,245);mapLEDXY(7,8,207,60,245);mapLEDXY(7,9,207,60,245);mapLEDXY(7,10,207,60,245);mapLEDXY(7,11,207,60,245);mapLEDXY(7,12,207,60,245);mapLEDXY(8,1,207,60,245);mapLEDXY(8,2,207,60,245);mapLEDXY(8,3,207,60,245);mapLEDXY(8,4,207,60,245);mapLEDXY(8,5,207,60,245);mapLEDXY(8,6,207,60,245);mapLEDXY(8,7,207,60,245);mapLEDXY(8,8,207,60,245);mapLEDXY(8,9,207,60,245);mapLEDXY(8,10,207,60,245);mapLEDXY(8,11,207,60,245);mapLEDXY(8,12,207,60,245);mapLEDXY(9,1,207,60,245);mapLEDXY(9,2,207,60,245);mapLEDXY(9,3,207,60,245);mapLEDXY(9,4,207,60,245);mapLEDXY(9,5,207,60,245);mapLEDXY(9,6,207,60,245);mapLEDXY(9,7,207,60,245);mapLEDXY(9,8,207,60,245);mapLEDXY(9,9,207,60,245);mapLEDXY(9,10,207,60,245);mapLEDXY(9,11,207,60,245);mapLEDXY(9,12,207,60,245);mapLEDXY(10,2,207,60,245);mapLEDXY(10,3,207,60,245);mapLEDXY(10,4,207,60,245);mapLEDXY(10,5,207,60,245);mapLEDXY(10,6,207,60,245);mapLEDXY(10,7,207,60,245);mapLEDXY(10,8,207,60,245);mapLEDXY(10,9,207,60,245);mapLEDXY(10,10,207,60,245);mapLEDXY(10,11,207,60,245);mapLEDXY(11,3,207,60,245);mapLEDXY(11,4,207,60,245);mapLEDXY(11,5,207,60,245);mapLEDXY(11,6,207,60,245);mapLEDXY(11,7,207,60,245);mapLEDXY(11,8,207,60,245);mapLEDXY(11,9,207,60,245);mapLEDXY(11,10,207,60,245);mapLEDXY(12,4,207,60,245);mapLEDXY(12,5,207,60,245);mapLEDXY(12,6,207,60,245);mapLEDXY(12,7,207,60,245);mapLEDXY(12,8,207,60,245);mapLEDXY(12,9,207,60,245);mapLEDXY(13,5,207,60,245);mapLEDXY(13,6,207,60,245);mapLEDXY(13,7,207,60,245);
}

void clearMatrix(){
  for(int i=0;i<NUM_LEDS2;i++){
     leds2[i] = CRGB (0,0,0);
  }
}

void mapLEDXY(int x, int y, byte RED, byte GREEN, byte BLUE){
    int RGBlocation = 0;
    if(y % 2 == 0){
        RGBlocation = x + y * 16;
    }else{
        RGBlocation = 15 - x + y * 16;
    }
    //update rgb
    leds2[RGBlocation] =  CRGB (RED,GREEN,BLUE);
    //fade by mapping
    int idx = 0;
    if(fadeUp){
      idx = map(i,0,58,0,255);
    }else{
      idx = map(i,0,58,200,0);
    }
   
    leds2[RGBlocation].fadeLightBy(levelTable[idx]);
}

void fillLevelTable(){
   float maxValue = 255;
  // iterate over the array and calculate the right value for it:
  for (int l = 0; l <= maxValue; l++) {
    // map input to a 0-179 range:
    float angle = map(l, 0, maxValue, 0, 179);
    //here it all is in one line:
    float lightLevel = (sin((angle * PI / 180) + PI / 2) + 1) * 127.5;
    levelTable[l] = lightLevel;
  }
} 