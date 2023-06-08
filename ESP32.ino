#include <WiFi.h>
#include <PubSubClient.h>
#include "ThingSpeak.h"
#include "Credentials/Credentials.h" // Einbinden der SSID, der ChannelNumber, usw.
#include "ColorRecognition.h"

// WLAN Einstellungen
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWD;

// MQTT Broker Einstellungen
const char* mqtt_server = MQTT_Server;
const char* mqtt_user = MQTT_User;
const char* mqtt_password = MQTT_Passwd;

// ThingSpeak Channel Einstellungen
unsigned long myChannelNumber = CH_Number; // Kanalnummer
const char* myWriteAPIKey = APIKey_Write; // API Schluessel zum Schreiben
const char* myReadAPIKey = APIKey_Read; // API Schluessel zum Lesen

// Deklarierung der Instanzen
WiFiClient espClient;
WiFiClient thinkspeak;
PubSubClient client(espClient);
ColorRec colorrec;

// Verbindung der Farbsensorkontakte
const int s0 = 14;
const int s1 = 27;
const int s2 = 26;
const int s3 = 25;
const int out = 33;

// Variablen fuer LEDs benennen
int redLED = 18; 
int greenLED = 19;
int blueLED = 21;

// Einstellungen fuer MQTT-Topic und Nachrichten
#define LED_TOPIC "esp/color"
long lastMsg = 0;
char msg[10];

void setup() {
  Serial.begin(9600);

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
  
  // Aufruf der Funktion fuer die Konfiguration des Farbsensors
  colorrec.esp_setup(s0, s1, s2, s3, out, redLED, greenLED, blueLED);


}

void loop() {
  /*
  int test = 1;
  int httpCode1 = ThingSpeak.writeField(myChannelNumber, 1, test, myWriteAPIKey);
  int httpCode2 = ThingSpeak.readLongField(myChannelNumber, 1, myReadAPIKey);
  Serial.println(httpCode2);
  */

  // Erneuter Verbindungsaufbau, sofern MQTT Verbindung abgebrochen ist
  if (!client.connected()) {
    mqttconnect();
  }

  // Aufruf der Funktion fuer die Farberkennung
  int result = colorrec.led_color(s0, s1, s2, s3, out, redLED, greenLED, blueLED);

  // Senden des Farbergebnis ueber MQTT
  if (!isnan(result)) {
    switch(result){
      case 1:
        snprintf (msg, 10, "Rot");
        break;
      case 2:
        snprintf (msg, 10, "Gruen");
        break;
      case 3:
        snprintf (msg, 10, "Blau");
        break;
    }
    client.publish(LED_TOPIC, msg);
    Serial.println(msg);
    Serial.println(result);
    int httpCode = ThingSpeak.writeField(myChannelNumber, 1, result, myWriteAPIKey);
  }

  delay(500);
  client.loop();


}


/**************************************************************************
 Funktion zum Verbindungsaufbau mit MQTT
**************************************************************************/
void mqttconnect() {
  /* MQTT Schleife (Verbindung aufbauen, Topic Subscribe, Wiederholter Verbindungsaufbau bei Abbruch nach Schleife). */
  while (!client.connected()) {
    Serial.print("MQTT Verbindung herstellen .... ");
    String clientId = "ESP32Client";
    /* Verbindung mit Mqtt-Nutzername und Mqtt-Passwort */
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_password)) {
      Serial.println("VERBUNDEN");
    } else {
      Serial.println("MQTT Verbindung fehlgeschlagen, erneuter Verbindungsaufbau in 5 Sekunden....");
      delay(5000);
    }
  }
}