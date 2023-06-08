#include "PickAndPlace/PickAndPlaceRoutine.h"
#include "ControlRoboter/RoboterControl.h"
#include "DiscoParty/Dancingrobot.cpp"
#include <Servo.h>
#include <Braccio.h>

#define PickAndPlace 44 // Analog Wert des Tasters (Pin A0)
#define Control 106 // Analog Wert des Tasters (Pin A0)
#define Disco 178 // Analog Wert des Tasters (Pin A0)
#define Standby 0 // Deklarierter Wert fuer den Wechsel in Standby

// Initialisierung der Servos des Braccio Roboterarmes
Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

// Objekt fuer den Aufruf der 'PickAndPlace'-Routine
PickAndPlaceRoutine Routine;

// Objekt fuer den Aufruf der 'Controlling'-Funktion
RoboterControl Controls;

// Initalisierung der Modus-Taster auf den Analog-Pin A0
const int modusTaster = A0;

// Initialisierung der Modus-Variable
int modus; // 44 = Pick-And-Place ; 106 = Control ; 178 = Disco ; 10 = Standby

// Initalisierung des Fototransistors auf den Analog-Pin A1
const int fototransistor = A1;

// Initialisierung einer Variable zur Speicherung des Wertes des Transistors
int helligkeit;

// Initalisierung der Control-Taster auf den Analog-Pin A2
const int controlTaster = A2;

// Initialisierung der controlroboter-Variable
int controlroboter; // 44 = M1 ; 106 = M2 ; 178 = M3 ; 511 = M4 ; 696 = M5

// Initalisierung der Control-Potentiometers auf den Analog-Pin A3
const int controlPoti = A3;

// Initialisierung der controlspeed-Variable
int controlspeed;


/******************************************************************************************** 
  Setup -> Deklarierung der einzelnen PINs und Initialiserung des Braccio Roboterarmes
**********************************************************************************************/

void setup(){
  
  // Initialisierung des seriellen Monitors
  Serial.begin(9600);

  // Initialisierung der LEDs als Output
  pinMode(2, OUTPUT); // blaue LED fuer "Disco"-Modus
  pinMode(4, OUTPUT); // gelbe LED fuer "Control"-Modus
  pinMode(7, OUTPUT); // gruene LED fuer "Pick-And-Place"-Modus
  pinMode(8, OUTPUT); // rote LED fuer "Standby"-Modus

  // Pin 12 muss High geschalten werden, um einen "Soft-Start" mit dem Roboter starten zu koennen
  pinMode(12, OUTPUT);  
  digitalWrite(12, HIGH);

  // Initialisierung des Braccio Roboterarmes mit "Soft-Start"
  Braccio.begin(SOFT_START_DISABLED);
  

};
 

/******************************************************************************************** 
  Loop -> Switch Cases fuer die Wahl des Modus mit Aufruf der einzelnen Funktionen
**********************************************************************************************/

void loop(){

  // Auslesen des Fototransistors, Zuweisung der Variable helligkeit
  helligkeit = analogRead(fototransistor);

  // Auslesen des Analogen Taster-Wertes, Zuweisung der Varaible modus
  modus = analogRead(modusTaster);

  // Auslesen des Analogen Taster-Wertes, Zuweisung der Varaible controlroboter
  controlroboter = analogRead(controlTaster);

  // Auslesen des Analogen Potentiometer-Wertes, Zuweisung der Varaible controlspeed
  controlspeed = analogRead(controlPoti);

  // Bei Dunkelheit wird der Standby-Modus aktiviert
  if (helligkeit < 10){
    // Ausgabe der Variable helligkeit auf dem seriellen Monitor
    Serial.print("Helligkeit: ");
    Serial.println(helligkeit);
    Serial.println("Licht aus");
    modus = Standby;
  }


  switch(modus) {

    // Pick-And-Place Routine
    case PickAndPlace:
      // Ausgabe der Variable helligkeit auf dem seriellen Monitor
      Serial.print("Helligkeit: ");
      Serial.println(helligkeit);

      // Modus LEDs anschalten
      digitalWrite(2, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(7, LOW);
      digitalWrite(8, LOW);

      // Serielle Ausgabe des aktiven Modus
      Serial.println("Pick-And-Place"); // Bisher nur eine Bewegung

      // Aufruf der PickAndPlace-Routine
      Routine.Routine(3);
      break;

    // Control Roboter
    case Control:
      // Ausgabe der Variable helligkeit auf dem seriellen Monitor
      Serial.print("Helligkeit: ");
      Serial.println(helligkeit);

      // Modus LEDs anschalten
      digitalWrite(2, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(7, LOW);
      digitalWrite(8, LOW);

      // Serielle Ausgabe des aktiven Modus
      Serial.println("Control");

      // Aufruf der Controlling-Methode
      //if((modus != PickAndPlace) || (modus != Disco) || (modus != Standby)){
        Controls.Controlling(controlroboter, controlspeed); // Problem: Bisher muss Modus-Taster noch gedrueckt werden
      //}
      break;

    // Disco Party
    case Disco:
      // Ausgabe der Variable helligkeit auf dem seriellen Monitor
      Serial.print("Helligkeit: ");
      Serial.println(helligkeit);

      // Modus LEDs anschalten
      digitalWrite(2, LOW);
      digitalWrite(4, LOW);
      digitalWrite(7, HIGH);
      digitalWrite(8, LOW);
      delay(2000); // kurzes delay zur Erkennung der Modus-LED

      // Serielle Ausgabe des aktiven Modus
      Serial.println("Disco");

      // Aufruf der Music/Disco-Methode
      dancing();

      break;
    
    // Standby
    case Standby:
      // Ausgabe der Variable helligkeit auf dem seriellen Monitor
      Serial.print("Helligkeit: ");
      Serial.println(helligkeit);

      // Modus LEDs anschalten
      digitalWrite(2, LOW);
      digitalWrite(4, LOW);
      digitalWrite(7, LOW);
      digitalWrite(8, HIGH);

      // Serielle Ausgabe des aktiven Modus
      Serial.println("Standby");
      break;

  }

}