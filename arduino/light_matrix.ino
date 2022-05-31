#include <FastLED.h>

//stripe
#define LED_PIN1 4
#define NUM_LEDS1 76
//matrix
#define LED_PIN2 6
#define NUM_LEDS2 255

CRGB leds1[NUM_LEDS1];
CRGB leds2[NUM_LEDS2];

int currentLevel = 255;
int change = 1;

int currentLevel1 = 255;
int change1 = 1;

byte levelTable[256];
byte levelTable2[256];

/**
 * Buttons light mode button states and color button states
 */
const int modeButtonPin = 2;    //this button used to control the animation to no animation
const int colorButtonPin = 3;   //this button used to control the color in animation mode

int modeButtonState = 0;
int colorButtonState = 0;

int modeButtonLastState = 0;
int colorButtonLastState = 0;

int buttonPushCounter = 0;   
int colorButtonPushCounter = 0;   


boolean animation = false;

void setup() {
  Serial.begin(9600);
  pinMode(modeButtonPin, INPUT);
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B, LED_PIN1>(leds1, NUM_LEDS1);
  FastLED.addLeds<WS2812B, LED_PIN2>(leds2, NUM_LEDS2);
  fillLevelTable();
  fillLevelTable2();
  //Scheduler.startLoop(loop2)
}

void loop() {
  modeButtonState = digitalRead(modeButtonPin);
  colorButtonState = digitalRead(colorButtonPin);
  //light animation state
  if(modeButtonLastState != modeButtonState){
    if(modeButtonState == HIGH){
      buttonPushCounter++;
      animation = false;
      //clearMatrix();
    }else{
      animation = true;
      //clearMatrix();
    }
  }
  //color 
  if(colorButtonLastState != colorButtonState){
    if(colorButtonState == HIGH){
      colorButtonPushCounter++;
    }else{
      //do nothing when not pushed
    }
  }
  
  modeButtonLastState = modeButtonState;
  colorButtonLastState = colorButtonState;

  if(buttonPushCounter % 2 == 0){
      //fixture mode one color light without animation
      //resetMatrix();
      //animation = false;
      fixLight();
    }else{
       lightAnimation();
   }
  delay(10);
}

void fixLight(){
  for (int i = 0; i < NUM_LEDS1; i++) {
      leds1[i] = CRGB(220,220,220);
  }
  //FastLED.setBrightness(255);
  //light matrix
  for(int j=0;j<NUM_LEDS2;j++){
    leds2[j].fadeLightBy(255);
  }
  fixtureMatrix();
  FastLED.show();
}

void lightAnimation(){
  if (currentLevel <= 0 || currentLevel >= 255) {
        change = -change;
      }
      currentLevel += change;
      int r = 207, g = 60, b = 245;
      if(colorButtonPushCounter % 3 == 0){
        //default color;
      }else if(colorButtonPushCounter % 3 == 1){
        r = 140;
        g = 34;
        b = 34;
      }else{
        r = 130;
        g = 160;
        b = 255;
      }
      // put your main code here, to run repeatedly:
      for (int i = 0; i < NUM_LEDS1; i++) {
        leds1[i] = CRGB(r,g,b);
//        leds1[i+1] = CRGB(r,g,b);
//        leds1[i+2] = CRGB(r,g,b);
//        
        //FastLED.setBrightness(levelTable[currentLevel]);
        
        leds1[i].fadeLightBy(levelTable[currentLevel]);
//        leds1[i+1].fadeLightBy(levelTable[currentLevel]);
//        leds1[i+2].fadeLightBy(levelTable[currentLevel]);
      }
      FastLED.show();
    
      if (currentLevel1 <= 0 || currentLevel1 >= 255) {
        change1 = -change1;
      }
      currentLevel1 += change1;
      //FastLED.setBrightness(255);
      fadeMatrix();
     
      FastLED.show();
}
//patterns for led matrix exported from the excel sheet
void fixtureMatrix(){
  mapLEDXY(1,4,220,220,220);mapLEDXY(1,5,220,220,220);mapLEDXY(1,6,220,220,220);mapLEDXY(1,7,220,220,220);mapLEDXY(1,8,220,220,220);mapLEDXY(1,9,220,220,220);mapLEDXY(1,10,220,220,220);mapLEDXY(2,3,220,220,220);mapLEDXY(2,4,220,220,220);mapLEDXY(2,5,220,220,220);mapLEDXY(2,6,220,220,220);mapLEDXY(2,7,220,220,220);mapLEDXY(2,8,220,220,220);mapLEDXY(2,9,220,220,220);mapLEDXY(2,10,220,220,220);mapLEDXY(2,11,220,220,220);mapLEDXY(3,2,220,220,220);mapLEDXY(3,3,220,220,220);mapLEDXY(3,4,220,220,220);mapLEDXY(3,5,220,220,220);mapLEDXY(3,6,220,220,220);mapLEDXY(3,7,220,220,220);mapLEDXY(3,8,220,220,220);mapLEDXY(3,9,220,220,220);mapLEDXY(3,10,220,220,220);mapLEDXY(3,11,220,220,220);mapLEDXY(3,12,220,220,220);mapLEDXY(4,1,220,220,220);mapLEDXY(4,2,220,220,220);mapLEDXY(4,3,220,220,220);mapLEDXY(4,4,220,220,220);mapLEDXY(4,5,220,220,220);mapLEDXY(4,6,220,220,220);mapLEDXY(4,7,220,220,220);mapLEDXY(4,8,220,220,220);mapLEDXY(4,9,220,220,220);mapLEDXY(4,10,220,220,220);mapLEDXY(4,11,220,220,220);mapLEDXY(4,12,220,220,220);mapLEDXY(4,13,220,220,220);mapLEDXY(5,1,220,220,220);mapLEDXY(5,2,220,220,220);mapLEDXY(5,3,220,220,220);mapLEDXY(5,4,220,220,220);mapLEDXY(5,5,220,220,220);mapLEDXY(5,6,220,220,220);mapLEDXY(5,7,220,220,220);mapLEDXY(5,8,220,220,220);mapLEDXY(5,9,220,220,220);mapLEDXY(5,10,220,220,220);mapLEDXY(5,11,220,220,220);mapLEDXY(5,12,220,220,220);mapLEDXY(5,13,220,220,220);mapLEDXY(6,1,220,220,220);mapLEDXY(6,2,220,220,220);mapLEDXY(6,3,220,220,220);mapLEDXY(6,4,220,220,220);mapLEDXY(6,5,220,220,220);mapLEDXY(6,6,220,220,220);mapLEDXY(6,7,220,220,220);mapLEDXY(6,8,220,220,220);mapLEDXY(6,9,220,220,220);mapLEDXY(6,10,220,220,220);mapLEDXY(6,11,220,220,220);mapLEDXY(6,12,220,220,220);mapLEDXY(6,13,220,220,220);mapLEDXY(7,1,220,220,220);mapLEDXY(7,2,220,220,220);mapLEDXY(7,3,220,220,220);mapLEDXY(7,4,220,220,220);mapLEDXY(7,5,220,220,220);mapLEDXY(7,6,220,220,220);mapLEDXY(7,7,220,220,220);mapLEDXY(7,8,220,220,220);mapLEDXY(7,9,220,220,220);mapLEDXY(7,10,220,220,220);mapLEDXY(7,11,220,220,220);mapLEDXY(7,12,220,220,220);mapLEDXY(7,13,220,220,220);mapLEDXY(8,1,220,220,220);mapLEDXY(8,2,220,220,220);mapLEDXY(8,3,220,220,220);mapLEDXY(8,4,220,220,220);mapLEDXY(8,5,220,220,220);mapLEDXY(8,6,220,220,220);mapLEDXY(8,7,220,220,220);mapLEDXY(8,8,220,220,220);mapLEDXY(8,9,220,220,220);mapLEDXY(8,10,220,220,220);mapLEDXY(8,11,220,220,220);mapLEDXY(8,12,220,220,220);mapLEDXY(8,13,220,220,220);mapLEDXY(9,1,220,220,220);mapLEDXY(9,2,220,220,220);mapLEDXY(9,3,220,220,220);mapLEDXY(9,4,220,220,220);mapLEDXY(9,5,220,220,220);mapLEDXY(9,6,220,220,220);mapLEDXY(9,7,220,220,220);mapLEDXY(9,8,220,220,220);mapLEDXY(9,9,220,220,220);mapLEDXY(9,10,220,220,220);mapLEDXY(9,11,220,220,220);mapLEDXY(9,12,220,220,220);mapLEDXY(9,13,220,220,220);mapLEDXY(10,1,220,220,220);mapLEDXY(10,2,220,220,220);mapLEDXY(10,3,220,220,220);mapLEDXY(10,4,220,220,220);mapLEDXY(10,5,220,220,220);mapLEDXY(10,6,220,220,220);mapLEDXY(10,7,220,220,220);mapLEDXY(10,8,220,220,220);mapLEDXY(10,9,220,220,220);mapLEDXY(10,10,220,220,220);mapLEDXY(10,11,220,220,220);mapLEDXY(10,12,220,220,220);mapLEDXY(10,13,220,220,220);mapLEDXY(11,2,220,220,220);mapLEDXY(11,3,220,220,220);mapLEDXY(11,4,220,220,220);mapLEDXY(11,5,220,220,220);mapLEDXY(11,6,220,220,220);mapLEDXY(11,7,220,220,220);mapLEDXY(11,8,220,220,220);mapLEDXY(11,9,220,220,220);mapLEDXY(11,10,220,220,220);mapLEDXY(11,11,220,220,220);mapLEDXY(11,12,220,220,220);mapLEDXY(12,3,220,220,220);mapLEDXY(12,4,220,220,220);mapLEDXY(12,5,220,220,220);mapLEDXY(12,6,220,220,220);mapLEDXY(12,7,220,220,220);mapLEDXY(12,8,220,220,220);mapLEDXY(12,9,220,220,220);mapLEDXY(12,10,220,220,220);mapLEDXY(12,11,220,220,220);mapLEDXY(13,4,220,220,220);mapLEDXY(13,5,220,220,220);mapLEDXY(13,6,220,220,220);mapLEDXY(13,7,220,220,220);mapLEDXY(13,8,220,220,220);mapLEDXY(13,9,220,220,220);mapLEDXY(13,10,220,220,220);
}

void fadeMatrix(){
  if(colorButtonPushCounter % 3 == 0){
    mapLEDXY(1,4,207,60,245);mapLEDXY(1,5,207,60,245);mapLEDXY(1,6,207,60,245);mapLEDXY(1,7,207,60,245);mapLEDXY(1,8,207,60,245);mapLEDXY(1,9,207,60,245);mapLEDXY(1,10,207,60,245);mapLEDXY(2,3,207,60,245);mapLEDXY(2,4,207,60,245);mapLEDXY(2,5,207,60,245);mapLEDXY(2,6,207,60,245);mapLEDXY(2,7,207,60,245);mapLEDXY(2,8,207,60,245);mapLEDXY(2,9,207,60,245);mapLEDXY(2,10,207,60,245);mapLEDXY(2,11,207,60,245);mapLEDXY(3,2,207,60,245);mapLEDXY(3,3,207,60,245);mapLEDXY(3,4,207,60,245);mapLEDXY(3,5,207,60,245);mapLEDXY(3,6,207,60,245);mapLEDXY(3,7,207,60,245);mapLEDXY(3,8,207,60,245);mapLEDXY(3,9,207,60,245);mapLEDXY(3,10,207,60,245);mapLEDXY(3,11,207,60,245);mapLEDXY(3,12,207,60,245);mapLEDXY(4,1,207,60,245);mapLEDXY(4,2,207,60,245);mapLEDXY(4,3,207,60,245);mapLEDXY(4,4,207,60,245);mapLEDXY(4,5,207,60,245);mapLEDXY(4,6,207,60,245);mapLEDXY(4,7,207,60,245);mapLEDXY(4,8,207,60,245);mapLEDXY(4,9,207,60,245);mapLEDXY(4,10,207,60,245);mapLEDXY(4,11,207,60,245);mapLEDXY(4,12,207,60,245);mapLEDXY(4,13,207,60,245);mapLEDXY(5,1,207,60,245);mapLEDXY(5,2,207,60,245);mapLEDXY(5,3,207,60,245);mapLEDXY(5,4,207,60,245);mapLEDXY(5,5,207,60,245);mapLEDXY(5,6,207,60,245);mapLEDXY(5,7,207,60,245);mapLEDXY(5,8,207,60,245);mapLEDXY(5,9,207,60,245);mapLEDXY(5,10,207,60,245);mapLEDXY(5,11,207,60,245);mapLEDXY(5,12,207,60,245);mapLEDXY(5,13,207,60,245);mapLEDXY(6,1,207,60,245);mapLEDXY(6,2,207,60,245);mapLEDXY(6,3,207,60,245);mapLEDXY(6,4,207,60,245);mapLEDXY(6,5,207,60,245);mapLEDXY(6,6,207,60,245);mapLEDXY(6,7,207,60,245);mapLEDXY(6,8,207,60,245);mapLEDXY(6,9,207,60,245);mapLEDXY(6,10,207,60,245);mapLEDXY(6,11,207,60,245);mapLEDXY(6,12,207,60,245);mapLEDXY(6,13,207,60,245);mapLEDXY(7,1,207,60,245);mapLEDXY(7,2,207,60,245);mapLEDXY(7,3,207,60,245);mapLEDXY(7,4,207,60,245);mapLEDXY(7,5,207,60,245);mapLEDXY(7,6,207,60,245);mapLEDXY(7,7,207,60,245);mapLEDXY(7,8,207,60,245);mapLEDXY(7,9,207,60,245);mapLEDXY(7,10,207,60,245);mapLEDXY(7,11,207,60,245);mapLEDXY(7,12,207,60,245);mapLEDXY(7,13,207,60,245);mapLEDXY(8,1,207,60,245);mapLEDXY(8,2,207,60,245);mapLEDXY(8,3,207,60,245);mapLEDXY(8,4,207,60,245);mapLEDXY(8,5,207,60,245);mapLEDXY(8,6,207,60,245);mapLEDXY(8,7,207,60,245);mapLEDXY(8,8,207,60,245);mapLEDXY(8,9,207,60,245);mapLEDXY(8,10,207,60,245);mapLEDXY(8,11,207,60,245);mapLEDXY(8,12,207,60,245);mapLEDXY(8,13,207,60,245);mapLEDXY(9,1,207,60,245);mapLEDXY(9,2,207,60,245);mapLEDXY(9,3,207,60,245);mapLEDXY(9,4,207,60,245);mapLEDXY(9,5,207,60,245);mapLEDXY(9,6,207,60,245);mapLEDXY(9,7,207,60,245);mapLEDXY(9,8,207,60,245);mapLEDXY(9,9,207,60,245);mapLEDXY(9,10,207,60,245);mapLEDXY(9,11,207,60,245);mapLEDXY(9,12,207,60,245);mapLEDXY(9,13,207,60,245);mapLEDXY(10,1,207,60,245);mapLEDXY(10,2,207,60,245);mapLEDXY(10,3,207,60,245);mapLEDXY(10,4,207,60,245);mapLEDXY(10,5,207,60,245);mapLEDXY(10,6,207,60,245);mapLEDXY(10,7,207,60,245);mapLEDXY(10,8,207,60,245);mapLEDXY(10,9,207,60,245);mapLEDXY(10,10,207,60,245);mapLEDXY(10,11,207,60,245);mapLEDXY(10,12,207,60,245);mapLEDXY(10,13,207,60,245);mapLEDXY(11,2,207,60,245);mapLEDXY(11,3,207,60,245);mapLEDXY(11,4,207,60,245);mapLEDXY(11,5,207,60,245);mapLEDXY(11,6,207,60,245);mapLEDXY(11,7,207,60,245);mapLEDXY(11,8,207,60,245);mapLEDXY(11,9,207,60,245);mapLEDXY(11,10,207,60,245);mapLEDXY(11,11,207,60,245);mapLEDXY(11,12,207,60,245);mapLEDXY(12,3,207,60,245);mapLEDXY(12,4,207,60,245);mapLEDXY(12,5,207,60,245);mapLEDXY(12,6,207,60,245);mapLEDXY(12,7,207,60,245);mapLEDXY(12,8,207,60,245);mapLEDXY(12,9,207,60,245);mapLEDXY(12,10,207,60,245);mapLEDXY(12,11,207,60,245);mapLEDXY(13,4,207,60,245);mapLEDXY(13,5,207,60,245);mapLEDXY(13,6,207,60,245);mapLEDXY(13,7,207,60,245);mapLEDXY(13,8,207,60,245);mapLEDXY(13,9,207,60,245);mapLEDXY(13,10,207,60,245);
  }else if( colorButtonPushCounter % 3 == 1){
    mapLEDXY(1,4,140,34,34);mapLEDXY(1,5,140,34,34);mapLEDXY(1,6,140,34,34);mapLEDXY(1,7,140,34,34);mapLEDXY(1,8,140,34,34);mapLEDXY(1,9,140,34,34);mapLEDXY(1,10,140,34,34);mapLEDXY(2,3,140,34,34);mapLEDXY(2,4,140,34,34);mapLEDXY(2,5,140,34,34);mapLEDXY(2,6,140,34,34);mapLEDXY(2,7,140,34,34);mapLEDXY(2,8,140,34,34);mapLEDXY(2,9,140,34,34);mapLEDXY(2,10,140,34,34);mapLEDXY(2,11,140,34,34);mapLEDXY(3,2,140,34,34);mapLEDXY(3,3,140,34,34);mapLEDXY(3,4,140,34,34);mapLEDXY(3,5,140,34,34);mapLEDXY(3,6,140,34,34);mapLEDXY(3,7,140,34,34);mapLEDXY(3,8,140,34,34);mapLEDXY(3,9,140,34,34);mapLEDXY(3,10,140,34,34);mapLEDXY(3,11,140,34,34);mapLEDXY(3,12,140,34,34);mapLEDXY(4,1,140,34,34);mapLEDXY(4,2,140,34,34);mapLEDXY(4,3,140,34,34);mapLEDXY(4,4,140,34,34);mapLEDXY(4,5,140,34,34);mapLEDXY(4,6,140,34,34);mapLEDXY(4,7,140,34,34);mapLEDXY(4,8,140,34,34);mapLEDXY(4,9,140,34,34);mapLEDXY(4,10,140,34,34);mapLEDXY(4,11,140,34,34);mapLEDXY(4,12,140,34,34);mapLEDXY(4,13,140,34,34);mapLEDXY(5,1,140,34,34);mapLEDXY(5,2,140,34,34);mapLEDXY(5,3,140,34,34);mapLEDXY(5,4,140,34,34);mapLEDXY(5,5,140,34,34);mapLEDXY(5,6,140,34,34);mapLEDXY(5,7,140,34,34);mapLEDXY(5,8,140,34,34);mapLEDXY(5,9,140,34,34);mapLEDXY(5,10,140,34,34);mapLEDXY(5,11,140,34,34);mapLEDXY(5,12,140,34,34);mapLEDXY(5,13,140,34,34);mapLEDXY(6,1,140,34,34);mapLEDXY(6,2,140,34,34);mapLEDXY(6,3,140,34,34);mapLEDXY(6,4,140,34,34);mapLEDXY(6,5,140,34,34);mapLEDXY(6,6,140,34,34);mapLEDXY(6,7,140,34,34);mapLEDXY(6,8,140,34,34);mapLEDXY(6,9,140,34,34);mapLEDXY(6,10,140,34,34);mapLEDXY(6,11,140,34,34);mapLEDXY(6,12,140,34,34);mapLEDXY(6,13,140,34,34);mapLEDXY(7,1,140,34,34);mapLEDXY(7,2,140,34,34);mapLEDXY(7,3,140,34,34);mapLEDXY(7,4,140,34,34);mapLEDXY(7,5,140,34,34);mapLEDXY(7,6,140,34,34);mapLEDXY(7,7,140,34,34);mapLEDXY(7,8,140,34,34);mapLEDXY(7,9,140,34,34);mapLEDXY(7,10,140,34,34);mapLEDXY(7,11,140,34,34);mapLEDXY(7,12,140,34,34);mapLEDXY(7,13,140,34,34);mapLEDXY(8,1,140,34,34);mapLEDXY(8,2,140,34,34);mapLEDXY(8,3,140,34,34);mapLEDXY(8,4,140,34,34);mapLEDXY(8,5,140,34,34);mapLEDXY(8,6,140,34,34);mapLEDXY(8,7,140,34,34);mapLEDXY(8,8,140,34,34);mapLEDXY(8,9,140,34,34);mapLEDXY(8,10,140,34,34);mapLEDXY(8,11,140,34,34);mapLEDXY(8,12,140,34,34);mapLEDXY(8,13,140,34,34);mapLEDXY(9,1,140,34,34);mapLEDXY(9,2,140,34,34);mapLEDXY(9,3,140,34,34);mapLEDXY(9,4,140,34,34);mapLEDXY(9,5,140,34,34);mapLEDXY(9,6,140,34,34);mapLEDXY(9,7,140,34,34);mapLEDXY(9,8,140,34,34);mapLEDXY(9,9,140,34,34);mapLEDXY(9,10,140,34,34);mapLEDXY(9,11,140,34,34);mapLEDXY(9,12,140,34,34);mapLEDXY(9,13,140,34,34);mapLEDXY(10,1,140,34,34);mapLEDXY(10,2,140,34,34);mapLEDXY(10,3,140,34,34);mapLEDXY(10,4,140,34,34);mapLEDXY(10,5,140,34,34);mapLEDXY(10,6,140,34,34);mapLEDXY(10,7,140,34,34);mapLEDXY(10,8,140,34,34);mapLEDXY(10,9,140,34,34);mapLEDXY(10,10,140,34,34);mapLEDXY(10,11,140,34,34);mapLEDXY(10,12,140,34,34);mapLEDXY(10,13,140,34,34);mapLEDXY(11,2,140,34,34);mapLEDXY(11,3,140,34,34);mapLEDXY(11,4,140,34,34);mapLEDXY(11,5,140,34,34);mapLEDXY(11,6,140,34,34);mapLEDXY(11,7,140,34,34);mapLEDXY(11,8,140,34,34);mapLEDXY(11,9,140,34,34);mapLEDXY(11,10,140,34,34);mapLEDXY(11,11,140,34,34);mapLEDXY(11,12,140,34,34);mapLEDXY(12,3,140,34,34);mapLEDXY(12,4,140,34,34);mapLEDXY(12,5,140,34,34);mapLEDXY(12,6,140,34,34);mapLEDXY(12,7,140,34,34);mapLEDXY(12,8,140,34,34);mapLEDXY(12,9,140,34,34);mapLEDXY(12,10,140,34,34);mapLEDXY(12,11,140,34,34);mapLEDXY(13,4,140,34,34);mapLEDXY(13,5,140,34,34);mapLEDXY(13,6,140,34,34);mapLEDXY(13,7,140,34,34);mapLEDXY(13,8,140,34,34);mapLEDXY(13,9,140,34,34);mapLEDXY(13,10,140,34,34);
  }else{
    mapLEDXY(1,4,130,160,255);mapLEDXY(1,5,130,160,255);mapLEDXY(1,6,130,160,255);mapLEDXY(1,7,130,160,255);mapLEDXY(1,8,130,160,255);mapLEDXY(1,9,130,160,255);mapLEDXY(1,10,130,160,255);mapLEDXY(2,3,130,160,255);mapLEDXY(2,4,130,160,255);mapLEDXY(2,5,130,160,255);mapLEDXY(2,6,130,160,255);mapLEDXY(2,7,130,160,255);mapLEDXY(2,8,130,160,255);mapLEDXY(2,9,130,160,255);mapLEDXY(2,10,130,160,255);mapLEDXY(2,11,130,160,255);mapLEDXY(3,2,130,160,255);mapLEDXY(3,3,130,160,255);mapLEDXY(3,4,130,160,255);mapLEDXY(3,5,130,160,255);mapLEDXY(3,6,130,160,255);mapLEDXY(3,7,130,160,255);mapLEDXY(3,8,130,160,255);mapLEDXY(3,9,130,160,255);mapLEDXY(3,10,130,160,255);mapLEDXY(3,11,130,160,255);mapLEDXY(3,12,130,160,255);mapLEDXY(4,1,130,160,255);mapLEDXY(4,2,130,160,255);mapLEDXY(4,3,130,160,255);mapLEDXY(4,4,130,160,255);mapLEDXY(4,5,130,160,255);mapLEDXY(4,6,130,160,255);mapLEDXY(4,7,130,160,255);mapLEDXY(4,8,130,160,255);mapLEDXY(4,9,130,160,255);mapLEDXY(4,10,130,160,255);mapLEDXY(4,11,130,160,255);mapLEDXY(4,12,130,160,255);mapLEDXY(4,13,130,160,255);mapLEDXY(5,1,130,160,255);mapLEDXY(5,2,130,160,255);mapLEDXY(5,3,130,160,255);mapLEDXY(5,4,130,160,255);mapLEDXY(5,5,130,160,255);mapLEDXY(5,6,130,160,255);mapLEDXY(5,7,130,160,255);mapLEDXY(5,8,130,160,255);mapLEDXY(5,9,130,160,255);mapLEDXY(5,10,130,160,255);mapLEDXY(5,11,130,160,255);mapLEDXY(5,12,130,160,255);mapLEDXY(5,13,130,160,255);mapLEDXY(6,1,130,160,255);mapLEDXY(6,2,130,160,255);mapLEDXY(6,3,130,160,255);mapLEDXY(6,4,130,160,255);mapLEDXY(6,5,130,160,255);mapLEDXY(6,6,130,160,255);mapLEDXY(6,7,130,160,255);mapLEDXY(6,8,130,160,255);mapLEDXY(6,9,130,160,255);mapLEDXY(6,10,130,160,255);mapLEDXY(6,11,130,160,255);mapLEDXY(6,12,130,160,255);mapLEDXY(6,13,130,160,255);mapLEDXY(7,1,130,160,255);mapLEDXY(7,2,130,160,255);mapLEDXY(7,3,130,160,255);mapLEDXY(7,4,130,160,255);mapLEDXY(7,5,130,160,255);mapLEDXY(7,6,130,160,255);mapLEDXY(7,7,130,160,255);mapLEDXY(7,8,130,160,255);mapLEDXY(7,9,130,160,255);mapLEDXY(7,10,130,160,255);mapLEDXY(7,11,130,160,255);mapLEDXY(7,12,130,160,255);mapLEDXY(7,13,130,160,255);mapLEDXY(8,1,130,160,255);mapLEDXY(8,2,130,160,255);mapLEDXY(8,3,130,160,255);mapLEDXY(8,4,130,160,255);mapLEDXY(8,5,130,160,255);mapLEDXY(8,6,130,160,255);mapLEDXY(8,7,130,160,255);mapLEDXY(8,8,130,160,255);mapLEDXY(8,9,130,160,255);mapLEDXY(8,10,130,160,255);mapLEDXY(8,11,130,160,255);mapLEDXY(8,12,130,160,255);mapLEDXY(8,13,130,160,255);mapLEDXY(9,1,130,160,255);mapLEDXY(9,2,130,160,255);mapLEDXY(9,3,130,160,255);mapLEDXY(9,4,130,160,255);mapLEDXY(9,5,130,160,255);mapLEDXY(9,6,130,160,255);mapLEDXY(9,7,130,160,255);mapLEDXY(9,8,130,160,255);mapLEDXY(9,9,130,160,255);mapLEDXY(9,10,130,160,255);mapLEDXY(9,11,130,160,255);mapLEDXY(9,12,130,160,255);mapLEDXY(9,13,130,160,255);mapLEDXY(10,1,130,160,255);mapLEDXY(10,2,130,160,255);mapLEDXY(10,3,130,160,255);mapLEDXY(10,4,130,160,255);mapLEDXY(10,5,130,160,255);mapLEDXY(10,6,130,160,255);mapLEDXY(10,7,130,160,255);mapLEDXY(10,8,130,160,255);mapLEDXY(10,9,130,160,255);mapLEDXY(10,10,130,160,255);mapLEDXY(10,11,130,160,255);mapLEDXY(10,12,130,160,255);mapLEDXY(10,13,130,160,255);mapLEDXY(11,2,130,160,255);mapLEDXY(11,3,130,160,255);mapLEDXY(11,4,130,160,255);mapLEDXY(11,5,130,160,255);mapLEDXY(11,6,130,160,255);mapLEDXY(11,7,130,160,255);mapLEDXY(11,8,130,160,255);mapLEDXY(11,9,130,160,255);mapLEDXY(11,10,130,160,255);mapLEDXY(11,11,130,160,255);mapLEDXY(11,12,130,160,255);mapLEDXY(12,3,130,160,255);mapLEDXY(12,4,130,160,255);mapLEDXY(12,5,130,160,255);mapLEDXY(12,6,130,160,255);mapLEDXY(12,7,130,160,255);mapLEDXY(12,8,130,160,255);mapLEDXY(12,9,130,160,255);mapLEDXY(12,10,130,160,255);mapLEDXY(12,11,130,160,255);mapLEDXY(13,4,130,160,255);mapLEDXY(13,5,130,160,255);mapLEDXY(13,6,130,160,255);mapLEDXY(13,7,130,160,255);mapLEDXY(13,8,130,160,255);mapLEDXY(13,9,130,160,255);mapLEDXY(13,10,130,160,255);
  }
  //mapLEDXY(6,4,100,0,10);mapLEDXY(6,6,100,0,10);mapLEDXY(8,4,100,0,10);mapLEDXY(8,6,100,0,10);
}

void clearMatrix(){
  for(int i=0;i<NUM_LEDS1;i++){
     leds1[i] = CRGB (0,0,0);
  }
  for(int i=0;i<NUM_LEDS2;i++){
     leds2[i] = CRGB (0,0,0);
  }
}
//map all leds from matrix
void mapLEDXY(int x, int y, byte RED, byte GREEN, byte BLUE){
    int RGBlocation = 0;
    if(y % 2 == 0){
        RGBlocation = x + y * 16;
    }else{
        RGBlocation = 15 - x + y * 16;
    }
    
    //update rgb
    leds2[RGBlocation] =  CRGB (RED,GREEN,BLUE);
    
    if(animation){
       leds2[RGBlocation].fadeLightBy(levelTable2[currentLevel1]);
    }
}

void clearStripe(){
  for (int i = 0; i < NUM_LEDS1; i++) {
     leds1[i] = CRGB(0,0,0);
  }
}
//level table for outter stripes
void fillLevelTable(){
   float maxValue = 255;
  // iterate over the array and calculate the right value for it:
  for (int l = 0; l <= maxValue; l++) {
    // map input to a 30-100 range:
    float angle = map(l, 0, maxValue, 30, 100);
    //here it all is in one line:
    float lightLevel = (sin((angle * PI / 180) + PI / 2) + 1) * 127.5;
    levelTable[l] = lightLevel;
  }
} 
//level table for led matrix
void fillLevelTable2(){
   float maxValue = 255;
  // iterate over the array and calculate the right value for it:
  for (int l = 0; l <= maxValue; l++) {
    // map input to a 0-179 range:
    float angle = map(l, 0, maxValue, 0, 160);
    //here it all is in one line:
    float lightLevel = (sin((angle * PI / 180) + PI / 2) + 1) * 127.5;
    levelTable2[l] = lightLevel;
  }
} 
