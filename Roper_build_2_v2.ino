#include <FastLED.h>
#define NUM_LEDS 5
#define DATA_PIN 6
#define DELAY_TIME 75
int PRPin = A0;
int PRThreshold = 35 0;
int PRVal;

CRGB leds[NUM_LEDS];
int LEDCount;
int HSVCount;
int C[NUM_LEDS][3];  //Current values, dont define

int D[NUM_LEDS][3]={
  {0,255,255},
  {96,255,255},
  {96,255,255},
  {96,255,255},
  {96,255,255},
};
int N[NUM_LEDS][3]={
  {0,0,0},
  {255,0,0},
  {0,0,0},
  {0,0,0},
  {255,0,0},
};

void setup() { 
Serial.begin(9600);       
LEDS.addLeds<WS2811,DATA_PIN, RGB>(leds, NUM_LEDS);
//  Desired values when Photoresitor detects bright room
// Need to make C = D here
for (LEDCount=0;LEDCount<NUM_LEDS;LEDCount++){
  C[LEDCount][0]=D[LEDCount][0];
  C[LEDCount][1]=D[LEDCount][1];
  C[LEDCount][2]=D[LEDCount][2];
}
}

void loop() { 
PRVal=analogRead(A0);
Serial.println(PRVal);
FastLED.show(); 
delay(DELAY_TIME);

for (LEDCount=0;LEDCount<NUM_LEDS;LEDCount++){
 //if photoiresistor says it's night
    if(PRVal<PRThreshold){
        if (C[LEDCount][0]<N[LEDCount][0]) {    C[LEDCount][0]=C[LEDCount][0]+1;}
        if (C[LEDCount][1]<N[LEDCount][1]) {    C[LEDCount][1]=C[LEDCount][1]+1;}
        if (C[LEDCount][2]<N[LEDCount][2]) {    C[LEDCount][2]=C[LEDCount][2]+1;}
      
        if (C[LEDCount][0]>N[LEDCount][0]) {    C[LEDCount][0]=C[LEDCount][0]-1;}
        if (C[LEDCount][1]>N[LEDCount][1]) {    C[LEDCount][1]=C[LEDCount][1]-1;}
        if (C[LEDCount][2]>N[LEDCount][2]) {    C[LEDCount][2]=C[LEDCount][2]-1;}
    }  

 //if photoiresistor says it's day
    if(PRVal>PRThreshold){
        if (C[LEDCount][0]<D[LEDCount][0]) {    C[LEDCount][0]=C[LEDCount][0]+1;}
        if (C[LEDCount][1]<D[LEDCount][1]) {    C[LEDCount][1]=C[LEDCount][1]+1;}
        if (C[LEDCount][2]<D[LEDCount][2]) {    C[LEDCount][2]=C[LEDCount][2]+1;}
      
        if (C[LEDCount][0]>D[LEDCount][0]) {    C[LEDCount][0]=C[LEDCount][0]-1;}
        if (C[LEDCount][1]>D[LEDCount][1]) {    C[LEDCount][1]=C[LEDCount][1]-1;}
        if (C[LEDCount][2]>D[LEDCount][2]) {    C[LEDCount][2]=C[LEDCount][2]-1;}
    } 

    
  leds[LEDCount] = CHSV( C[LEDCount][0],C[LEDCount][1],C[LEDCount][2]);
    
}
 



  
 
}
