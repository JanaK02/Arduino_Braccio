#include <WiFiNINA.h>
#include <PubSubClient.h>
#include "ThingSpeak.h"
#include <Servo.h>
#include <Braccio.h>
#include "Credentials/Credentials.h" // Einbinden der SSID, der ChannelNumber, usw.
#include "PickAndPlace/PickAndPlaceRoutine.h"
#include "ControlRoboter/RoboterControl.h"
#include "DiscoParty/Dancingrobot.cpp"


#define PickAndPlace 45 // Analog Wert des Tasters (Pin A0)
#define Control 108 // Analog Wert des Tasters (Pin A0)
#define Disco 180 // Analog Wert des Tasters (Pin A0)
#define Standby 0 // Deklarierter Wert fuer den Wechsel in Standby

// WLAN Einstellungen
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWD;

// Deklarierung der WiFi-Instanz
WiFiClient arduinoClient;

// MQTT Broker Einstellungen
const char* mqtt_server = MQTT_Server;
const char* mqtt_user = MQTT_User;
const char* mqtt_password = MQTT_Passwd;

// Deklarierung der PubSub-Instanz
PubSubClient client(arduinoClient);

// MQTT Topics
#define InPosition_Topic "arduino/inposition"
#define Color_Topic "esp/color"

// Deklarierung der Variable fuer die Farbe der Schwaemme
char Color = '0';

// ThingSpeak Channel Einstellungen
unsigned long myChannelNumber = CH_Number; // Kanalnummer
const char* myWriteAPIKey = APIKey_Write; // API Schluessel zum Schreiben
const char* myReadAPIKey = APIKey_Read; // API Schluessel zum Lesen

// Deklarierung der Thingspeak-Instanz
WiFiClient thinkspeak;

// Deklarierung der Variable fuer das Senden der ThingSpeak-Nachricht
int httpCode;

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



/**************************************************************************
 Funktion zum Verbindungsaufbau mit MQTT
**************************************************************************/
void mqttconnect() {
  /* MQTT Schleife (Verbindung aufbauen, Topic Subscribe, Wiederholter Verbindungsaufbau bei Abbruch nach Schleife). */
  while (!client.connected()) {
    Serial.print("MQTT Verbindung herstellen .... ");
    String clientId = "ArduinoClient";
    /* Verbindung mit Mqtt-Nutzername und Mqtt-Passwort */
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_password)) {
      Serial.println("VERBUNDEN");
      client.subscribe(Color_Topic);
    } else {
      Serial.println("MQTT Verbindung fehlgeschlagen, erneuter Verbindungsaufbau in 5 Sekunden....");
      delay(5000);
    }
  }
}



void receivedCallback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("Message arrived in topic: ");
  Serial.println(Color_Topic);

  Serial.print("Message:");
  for (int i = 0; i < length; i++) 
  {
    Serial.print((char)payload[i]);
    Color = (char)payload[i];

  }

  Serial.println();
  Serial.println("-----------------------");
 
}


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
  
  // Verbindungsaufbau mit konfigurierten WLAN
  Serial.println("Verbindung zu Wlan Netzwerk. SSID: " + String(ssid)  );
  delay(500);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(" .");
  }

  // Konfiguration MQTT Server mit Hostname und Port
  client.setServer(mqtt_server, 1883);

  // Verbindung zur Thingspeak herstellen
  ThingSpeak.begin(thinkspeak);

  // Serielle Ausgabe zur erfolgreichen Verbindung
  Serial.println("");
  Serial.println("WLAN VERBUNDEN. ");
  Serial.print("IP Adresse: ");
  Serial.println(WiFi.localIP());


  client.setCallback(receivedCallback);

};
 

/******************************************************************************************** 
  Loop -> Switch Cases fuer die Wahl des Modus mit Aufruf der einzelnen Funktionen
**********************************************************************************************/

void loop(){

  // Erneuter Verbindungsaufbau, sofern MQTT Verbindung abgebrochen ist
  if (!client.connected()) {
    mqttconnect();
  }

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
  client.loop();
  Color = '0';

    // Pick-And-Place Routine
    if(modus == PickAndPlace)
    {
      // Schreiben des Modus in die Cloud, Wert = 1 steht fuer PickAndPlace
      httpCode = ThingSpeak.writeField(myChannelNumber, 1, 1, myWriteAPIKey);

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
      // Aufheben des ersten Schwammes
      Routine.RoutineFirst();
      Routine.SensorPosition(); // Bewegung ueber den Sensor
      delay(2000);
      client.publish(InPosition_Topic, "1"); // Signalisiert, dass der ESP starten kann
      client.loop();
      Color = '0';
      while(Color == '0')
      {
         client.loop();   
          if (!client.connected()) 
          {
            mqttconnect();
          };
      }
      client.publish(InPosition_Topic, "0"); // Signalisiert, dass der ESP stoppen kann
      Routine.ColorSort(Color); // Methode zur Sortierung
      Color = '0';

      // Aufheben des zweiten Schwammes
      Routine.RoutineSecond();
      Routine.SensorPosition(); // Bewegung ueber den Sensor
      delay(2000);
      client.publish(InPosition_Topic, "1"); // Signalisiert, dass der ESP starten kann
      client.loop();
      Color = '0';
      while(Color == '0')
      {
         client.loop();
          if (!client.connected()) 
          {
            mqttconnect();
          };
      }
      client.publish(InPosition_Topic, "0"); // Signalisiert, dass der ESP stoppen kann
      Routine.ColorSort(Color); // Methode zur Sortierung
      Color = '0';

      // Aufheben des dritten Schwammes
      Routine.RoutineThird();
      Routine.SensorPosition(); // Bewegung ueber den Sensor
      delay(2000);
      client.publish(InPosition_Topic, "1"); // Signalisiert, dass der ESP starten kann
      client.loop();
      Color = '0';
      while(Color == '0')
      {
         client.loop();
          if (!client.connected()) 
          {
            mqttconnect();
          };
      }
      client.publish(InPosition_Topic, "0"); // Signalisiert, dass der ESP stoppen kann
      Routine.ColorSort(Color); // Methode zur Sortierung
      Color = '0';

    };

    // Control Roboter
    while(modus == Control)
    {
      // Schreiben des Modus in die Cloud, Wert = 2 steht fuer Control
      httpCode = ThingSpeak.writeField(myChannelNumber, 1, 2, myWriteAPIKey);

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
        Controls.Controlling(controlroboter, controlspeed);

        modus = analogRead(modusTaster);
    };

    // Disco Party
    if(modus == Disco)
    {
      // Schreiben des Modus in die Cloud, Wert = 2 steht fuer Disco
      httpCode = ThingSpeak.writeField(myChannelNumber, 1, 3, myWriteAPIKey);

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

    };
    
    // Standby
    if (modus == Standby)
    {
      // Schreiben des Modus in die Cloud, Wert = 0 steht fuer Standby
      httpCode = ThingSpeak.writeField(myChannelNumber, 1, 0, myWriteAPIKey);

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
    };

    client.loop();

}
