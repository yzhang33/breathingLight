#include <FastLED.h>

#define LED_PIN 6
#define NUM_LEDS 256

//byte RGB[256*3];//take your number of LEDs and multiply by 3

CRGB leds[NUM_LEDS];
byte levelTable[255];
int change = 1;
int fadeIncremet = 10;
int currentLevel = 1; // current light level

void setup() {
  //pinMode(WS2812_pin, OUTPUT);
  Serial.begin(9600);
  FastLED.addLeds<SK6812, LED_PIN>(leds, NUM_LEDS);
  fillLevelTable();
}//setup

void loop() {
  clearAll();
  //1
  mapLEDXY(7,7,200,200,255);mapLEDXY(7,8,200,200,255);mapLEDXY(8,7,200,200,255);mapLEDXY(8,8,200,200,255);                    
  FastLED.show();
  delay(1000);
  //2
  mapLEDXY(5,7,207,60,245);mapLEDXY(6,6,207,60,245);mapLEDXY(6,7,207,60,245);mapLEDXY(6,8,207,60,245);mapLEDXY(7,5,207,60,245);mapLEDXY(7,6,207,60,245);mapLEDXY(7,8,207,60,245);mapLEDXY(7,9,207,60,245);mapLEDXY(8,5,207,60,245);mapLEDXY(8,6,207,60,245);mapLEDXY(8,8,207,60,245);mapLEDXY(8,9,207,60,245);mapLEDXY(9,6,207,60,245);mapLEDXY(9,7,207,60,245);mapLEDXY(9,8,207,60,245);mapLEDXY(10,7,207,60,245);
  FastLED.show();
  delay(1000);
  //3
  mapLEDXY(3,7,207,60,245);mapLEDXY(4,6,207,60,245);mapLEDXY(4,7,207,60,245);mapLEDXY(4,8,207,60,245);mapLEDXY(5,5,207,60,245);mapLEDXY(5,6,207,60,245);mapLEDXY(5,8,207,60,245);mapLEDXY(5,9,207,60,245);mapLEDXY(6,4,207,60,245);mapLEDXY(6,5,207,60,245);mapLEDXY(6,9,207,60,245);mapLEDXY(6,10,207,60,245);mapLEDXY(7,4,207,60,245);mapLEDXY(7,10,207,60,245);mapLEDXY(8,4,207,60,245);mapLEDXY(8,10,207,60,245);mapLEDXY(9,4,207,60,245);mapLEDXY(9,5,207,60,245);mapLEDXY(9,9,207,60,245);mapLEDXY(9,10,207,60,245);mapLEDXY(10,5,207,60,245);mapLEDXY(10,6,207,60,245);mapLEDXY(10,8,207,60,245);mapLEDXY(10,9,207,60,245);mapLEDXY(11,6,207,60,245);mapLEDXY(11,7,207,60,245);mapLEDXY(11,8,207,60,245);mapLEDXY(12,7,207,60,245);
  FastLED.show();
  delay(1000);
  //
  clearAll();
  mapLEDXY(1,1,207,60,245);mapLEDXY(1,5,207,60,245);mapLEDXY(2,2,207,60,245);mapLEDXY(2,4,207,60,245);mapLEDXY(3,3,207,60,245);mapLEDXY(4,2,207,60,245);mapLEDXY(4,4,207,60,245);mapLEDXY(4,12,207,60,245);mapLEDXY(4,13,207,60,245);mapLEDXY(4,14,207,60,245);mapLEDXY(5,1,207,60,245);mapLEDXY(5,5,207,60,245);mapLEDXY(5,9,207,60,245);mapLEDXY(5,12,207,60,245);mapLEDXY(5,14,207,60,245);mapLEDXY(6,8,207,60,245);mapLEDXY(6,9,207,60,245);mapLEDXY(6,12,207,60,245);mapLEDXY(6,14,207,60,245);mapLEDXY(7,7,207,60,245);mapLEDXY(7,8,207,60,245);mapLEDXY(7,9,207,60,245);mapLEDXY(7,12,207,60,245);mapLEDXY(7,14,207,60,245);mapLEDXY(8,8,207,60,245);mapLEDXY(8,9,207,60,245);mapLEDXY(8,12,207,60,245);mapLEDXY(8,14,207,60,245);mapLEDXY(9,1,207,60,245);mapLEDXY(9,5,207,60,245);mapLEDXY(9,9,207,60,245);mapLEDXY(9,12,207,60,245);mapLEDXY(9,14,207,60,245);mapLEDXY(10,2,207,60,245);mapLEDXY(10,4,207,60,245);mapLEDXY(10,12,207,60,245);mapLEDXY(10,13,207,60,245);mapLEDXY(10,14,207,60,245);mapLEDXY(11,3,207,60,245);mapLEDXY(12,2,207,60,245);mapLEDXY(12,4,207,60,245);mapLEDXY(13,1,207,60,245);mapLEDXY(13,5,207,60,245);
  FastLED.show();
  delay(1000);
}//loop

void clearAll(){
  for(int i=0;i<NUM_LEDS;i++){
    leds[i] =  CRGB (0,0,0);
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
    Serial.println(RGBlocation);
    leds[RGBlocation] =  CRGB (RED,GREEN,BLUE);
    //leds[RGBlocation].fadeLightBy(levelTable[currentLevel]);
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