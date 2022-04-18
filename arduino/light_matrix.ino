
//VARIABLES AND DEFINES HERE - NEEDED BY THE WS2812 DRIVER CODE
#define WS2812_pin 6 // only digital pin 8 works right now
#define numberOfLEDs 256// total number of RGB LEDs
byte RGB[256*3];//take your number of LEDs and multiply by 3

// FUNCTIONS HERE
void RGB_update(int LED, byte RED, byte GREEN, byte BLUE);//function to drive LEDs

void mapLed(int x, int y, byte RED, byte GREEN, byte BLUUE);

void setup() {
  pinMode(WS2812_pin, OUTPUT);
}//setup


void loop() {
//1
mapLEDXY(7,7,200,200,255);mapLEDXY(7,8,200,200,255);mapLEDXY(8,7,200,200,255);mapLEDXY(8,8,200,200,255);										
RGB_update(-1,0,0,0);
delay(50);
//2
mapLEDXY(6,6,200,150,255);mapLEDXY(6,7,200,150,255);mapLEDXY(6,8,200,150,255);mapLEDXY(6,9,200,150,255);mapLEDXY(7,6,200,150,255);mapLEDXY(7,9,200,150,255);mapLEDXY(8,6,200,150,255);mapLEDXY(8,9,200,150,255);mapLEDXY(9,6,200,150,255);mapLEDXY(9,7,200,150,255);mapLEDXY(9,8,200,150,255);mapLEDXY(9,9,200,150,255);
RGB_update(-1,0,0,0);
delay(50);
//3
mapLEDXY(5,5,150,150,255);mapLEDXY(5,6,150,150,255);mapLEDXY(5,7,150,150,255);mapLEDXY(5,8,150,150,255);mapLEDXY(5,9,150,150,255);mapLEDXY(5,10,150,150,255);mapLEDXY(6,5,150,150,255);mapLEDXY(6,10,150,150,255);mapLEDXY(7,5,150,150,255);mapLEDXY(7,10,150,150,255);mapLEDXY(8,5,150,150,255);mapLEDXY(8,10,150,150,255);mapLEDXY(9,5,150,150,255);mapLEDXY(9,10,150,150,255);mapLEDXY(10,5,150,150,255);mapLEDXY(10,6,150,150,255);mapLEDXY(10,7,150,150,255);mapLEDXY(10,8,150,150,255);mapLEDXY(10,9,150,150,255);mapLEDXY(10,10,150,150,255);
RGB_update(-1,0,0,0);
delay(50);
//4

}//loop

void mapLed(int x, int y, byte RED, byte GREEN, byte BLUE){
    int RGBlocation = 0;
    if(y % 2 == 0){
        RGBlocation = x + y * 16;
    }else{
        RGBlocation = 15 - x + y * 16;
    }
    //update rgb
    RGB[RGBlocation*3] = BLUE;
    RGB[RGBlocation*3 + 1] = RED;
    RGB[RGBlocation*3 + 2] = GREEN;
}


//WS2812 Driver Function
void RGB_update(int LED, byte RED, byte GREEN, byte BLUE) {
  // LED is the LED number starting with 0
  // RED, GREEN, BLUE is the brightness 0..255 setpoint for that LED
  byte ExistingPort, WS2812pinHIGH;//local variables here to speed up pinWrites
  
  if(LED>=0){//map the REG GREEN BLUE Values into the RGB[] array
  RGB[LED * 3] = GREEN;
  RGB[LED * 3 + 1] = RED;
  RGB[LED * 3 + 2] = BLUE;
  }
  
  noInterrupts();//kill the interrupts while we send the bit stream out...
  ExistingPort = PORTB; // save the status of the entire PORT B - let's us write to the entire port without messing up the other pins on that port
  WS2812pinHIGH = PORTB | 1; //this gives us a byte we can use to set the whole PORTB with the WS2812 pin HIGH
  int bitStream = numberOfLEDs * 3;//total bytes in the LED string

//This for loop runs through all of the bits (8 at a time) to set the WS2812 pin ON/OFF times
  for (int i = 0; i < bitStream; i++) {

    PORTB = WS2812pinHIGH;//bit 7  first, set the pin HIGH - it always goes high regardless of a 0/1 
    
    //here's the tricky part, check if the bit in the byte is high/low then right that status to the pin
    // (RGB[i] & B10000000) will strip away the other bits in RGB[i], so here we'll be left with B10000000 or B00000000
    // then it's easy to check if the bit is high or low by AND'ing that with the bit mask ""&& B10000000)"" this gives 1 or 0
    // if it's a 1, we'll OR that with the Existing port, thus keeping the pin HIGH, if 0 the pin is written LOW
    PORTB = ((RGB[i] & B10000000) && B10000000) | ExistingPort; 
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");//these are NOPS - these let us delay clock cycles for more precise timing 
    PORTB = ExistingPort;//okay, here we know we have to be LOW regardless of the 0/1 bit state
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");//minimum LOW time for pin regardless of 0/1 bit state

    // then do it again for the next bit and so on... see the last bit though for a slight change

    PORTB = WS2812pinHIGH;//bit 6
    PORTB = ((RGB[i] & B01000000) && B01000000) | ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
    PORTB = ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");

    PORTB = WS2812pinHIGH;//bit 5
    PORTB = ((RGB[i] & B00100000) && B00100000) | ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
    PORTB = ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");

    PORTB = WS2812pinHIGH;//bit 4
    PORTB = ((RGB[i] & B00010000) && B00010000) | ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
    PORTB = ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");

    PORTB = WS2812pinHIGH;//bit 3
    PORTB = ((RGB[i] & B00001000) && B00001000) | ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
    PORTB = ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");

    PORTB = WS2812pinHIGH;//bit 2
    PORTB = ((RGB[i] & B00000100) && B00000100) | ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
    PORTB = ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");

    PORTB = WS2812pinHIGH;//bit 1
    PORTB = ((RGB[i] & B00000010) && B00000010) | ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
    PORTB = ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");

    PORTB = WS2812pinHIGH;//bit 0
    __asm__("nop\n\t");//on this last bit, the check is much faster, so had to add a NOP here
    PORTB = ((RGB[i] & B00000001) && B00000001) | ExistingPort;
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t"); 
    PORTB = ExistingPort;//note there are no NOPs after writing the pin LOW, this is because the FOR Loop uses clock cycles that we can use instead of the NOPS
  }//for loop

  
  interrupts();//enable the interrupts

// all done!
}