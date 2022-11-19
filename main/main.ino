#include "PickAndPlace/PickAndPlaceRoutine.h"
#include "ControlRoboter/RoboterControl.h"
//#include "DiscoParty/Nevergonnagiveyouup.cpp"
//#include "DiscoParty/Takeonme.cpp"
//#include "DiscoParty/Thelionsleepstonight.cpp"
//#include "DiscoParty/MerryChristmas.cpp"
#include "DiscoParty/MiiChannel.cpp"
//#include "DiscoParty/Pinkpanther.cpp"
//#include "DiscoParty/GameofThrones.cpp"
//#include "DiscoParty/KeyboardCat.cpp"
//#include "DiscoParty/ProfessorLayton.cpp"
//#include "DiscoParty/SuperMarioBros.cpp"
#include <Servo.h>
#include <Braccio.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;
PickAndPlaceRoutine Routine;
RoboterControl Controls;
int start = 1;
int modus ; // 0 = Pick-And-Place ; 1 = Control ; 2 = Disco ; 3 = Stoerung

const int Fototransistor = A0;
int Helligkeit = 0;


void setup(){
  
  Serial.begin(9600);
  pinMode(3, OUTPUT); // blaue LED fuer "Disco"-Modus
  pinMode(4, OUTPUT); // gelbe LED fuer "Control"-Modus
  pinMode(5, OUTPUT); // gruene LED fuer "Pick-And-Place"-Modus
  pinMode(6, OUTPUT); // rote LED fuer "Stoerung"-Modus
  pinMode(8, INPUT); // Taster fuer "Pick-And-Place"-Modus
  pinMode(9, INPUT); // Taster fuer "Control"-Modus
  pinMode(10, INPUT); // Taster fuer "Disco"-Modus
  

};
 
void loop(){

  int PickPlaceTaster = digitalRead(8); // Tasterzustand einlesen
  int ControlTaster = digitalRead(9); // Tasterzustand einlesen
  int DiscoTaster = digitalRead(10); // Tasterzustand einlesen
  Helligkeit = analogRead(Fototransistor);

  //  output info to te serial monitor
  Serial.print("Helligkeit: ");
  Serial.println(Helligkeit);


  if (PickPlaceTaster == HIGH) { 
    Serial.print("P");
    modus = 0;
  } 
  if (ControlTaster == HIGH) { 
    Serial.print("C");
    modus = 1;
  } 
  if (DiscoTaster == HIGH) { 
    Serial.print("D");
    modus = 2;
  } 
  if(PickPlaceTaster == LOW && ControlTaster == LOW && DiscoTaster == LOW) { 
    Serial.print("LOW");
    modus = 3;
    } 
  if (Helligkeit < 30){
    Serial.println("Licht aus");
    modus = 3;
  }


  switch(modus) {

    // Pick-And-Place Routine
    case 0:
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      digitalWrite(3, HIGH);
      digitalWrite(6, LOW);
      Serial.println("Pick-And-Place");
      delay(10000);
      //Routine.Routine(start);
      break;

    // Control Roboter
    case 1:
      digitalWrite(3, LOW);
      digitalWrite(5, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(6, LOW);
      Serial.println("Control");
      delay(10000);
      //Controls.Control(M1, M2, M3, M4, M5, M6);
      break;

    // Disco Party
    case 2:
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(6, LOW);
      delay(2000);
      Serial.println("Disco");
      music();
      delay(10000);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(6, LOW);
      break;

    // Stoerung
    case 3:
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, HIGH);
      delay(2000);
      Serial.println("Standby");

  }

}