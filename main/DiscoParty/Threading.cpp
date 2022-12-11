//#include "Dancingrobot.cpp"
#include "MiiChannel.cpp"

unsigned long previousMillisMusic = 0;
unsigned long previousMillisDancing = 0;

long OnTime1 = 250;           // milliseconds of on-time
long OffTime1 = 750;          // milliseconds of off-time


long OnTime2 = 330;           // milliseconds of on-time
long OffTime2 = 400;          // milliseconds of off-time

int thread(){
    // check to see if it's time to change the state of the LED
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillisMusic >= OnTime1)
  {
    music();  // Turn it off
    previousMillisMusic = currentMillis;  // Remember the time
  }
      
  if(currentMillis - previousMillisDancing >= OnTime2)
  {
    Serial.println("dancing()");  // Turn it off
    previousMillisDancing = currentMillis;  // Remember the time
  }


}