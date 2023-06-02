//libraries:
#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

//variables:
int lrandlight; //used
int rrandlight; //used
float midi[127]; //used
int A_four = 440; //used
volatile int userr = 0; //used
volatile int userl = 9; //used
int colorr; //used
int colorg; //used
int colorb; //used
int score;
volatile int gametime=5000; //used
volatile bool lactuation =0; //used
volatile bool ractuation =0; //used
AsyncDelay tImer; //used

//functions:
void generateMIDI(){
  for (int x = 0; x < 127; ++x)
  {
    midi[x] = (A_four / 32.0) * pow(2.0, ((x - 9.0) / 12.0));
    Serial.println(midi[x]);
  }
}
void randomcolors(){
  colorr = random(255);
  colorg = random(255);
  colorb = random(255);
  lrandlight = random(4)+5;
  rrandlight = random(4)+1;
  CircuitPlayground.setPixelColor(lrandlight, colorr, colorg, colorb);
  CircuitPlayground.setPixelColor(rrandlight, colorr, colorg, colorb);
}
void breathing(){
  for(int i=0; i<2; i++){
    for(int i=0;i<255;i++)
    {
    CircuitPlayground.setPixelColor(1, i, 0, 0);
    CircuitPlayground.setPixelColor(2, i, 0, 0);
    CircuitPlayground.setPixelColor(3, i, 0, 0);
    CircuitPlayground.setPixelColor(4, i, 0, 0);
    CircuitPlayground.setPixelColor(5, i, 0, 0);
    CircuitPlayground.setPixelColor(6, i, 0, 0);
    CircuitPlayground.setPixelColor(7, i, 0, 0);
    CircuitPlayground.setPixelColor(8, i, 0, 0);
    CircuitPlayground.setPixelColor(9, i, 0, 0);
    CircuitPlayground.setPixelColor(0, i, 0, 0);
    }
    for(int i=255;i>0;i--)
    {
    CircuitPlayground.setPixelColor(1, i, 0, 0);
    CircuitPlayground.setPixelColor(2, i, 0, 0);
    CircuitPlayground.setPixelColor(3, i, 0, 0);
    CircuitPlayground.setPixelColor(4, i, 0, 0);
    CircuitPlayground.setPixelColor(5, i, 0, 0);
    CircuitPlayground.setPixelColor(6, i, 0, 0);
    CircuitPlayground.setPixelColor(7, i, 0, 0);
    CircuitPlayground.setPixelColor(8, i, 0, 0);
    CircuitPlayground.setPixelColor(9, i, 0, 0);
    CircuitPlayground.setPixelColor(0, i, 0, 0);
    }
  }
}
void singlePressl() {
  lactuation = 1;
}
void singlePressr() {
  ractuation = 1;
}
void loose(){
    CircuitPlayground.clearPixels();
    //CircuitPlayground.playTone(midi[5],1000);
    breathing();
    gametime - 100;
    delay(1500);
}
void reset(){
    CircuitPlayground.clearPixels();
    tImer.repeat();
    userr = 0;
    userl = 9;
}
//setup:
void setup(){
  Serial.begin(9600);
  CircuitPlayground.begin();
  generateMIDI();
  attachInterrupt(digitalPinToInterrupt(5), singlePressl, FALLING);
  attachInterrupt(digitalPinToInterrupt(4), singlePressr, FALLING);
}
//loop:
void loop() {
  randomSeed(random());
  tImer.start(gametime, AsyncDelay::MILLIS);
  randomcolors();
  CircuitPlayground.setPixelColor(userl, 255, 255, 255);
  CircuitPlayground.setPixelColor(userr, 255, 255, 255);
  while(!tImer.isExpired()){
    if(lactuation && (userl >= lrandlight)){
      userl--;
      Serial.print("left: "); Serial.println(userl);
      CircuitPlayground.setPixelColor(userl+1, 0, 0, 0);
      CircuitPlayground.setPixelColor(userl, 255, 255, 255);
      lactuation =0;
    }
    else if(!(userl >= lrandlight)){
        break;
        }
    if(ractuation && (userr <= rrandlight)){
      userr++;
      Serial.print("right: "); Serial.println(userr);
      CircuitPlayground.setPixelColor(userr-1, 0, 0, 0);
      CircuitPlayground.setPixelColor(userr, 255, 255, 255);
      ractuation =0;
    }
    else if(!(userr <= rrandlight)){
      gametime=5000;
      break;
      }
    else if(!(userl >= lrandlight)){
      gametime=5000;
      break;
      }
    if(userr==rrandlight && userl==lrandlight){
    CircuitPlayground.clearPixels();
    gametime-200;
    break;
    }
  }
  loose();
  reset();
}