#include "ColorRecognition.h"

/**************************************************************************************
 * Hier werden die Pins deklariert
*****************************************************************************************/
void ColorRec::esp_setup(int s0,int s1,int s2,int s3,int out,int redLED,int greenLED,int blueLED)
{

    pinMode(s0, OUTPUT); //Die Kontakte des Farbsensors werden als Output oder...
    pinMode(s1, OUTPUT); // (Warum als Output? Die Frequenzwerte (s0-s3) sollen im
    pinMode(s2, OUTPUT); // seriellen Monitor ausgegeben werden.)
    pinMode(s3, OUTPUT);
    pinMode(out, INPUT); // ...Input festgelegt
    pinMode(redLED, OUTPUT); //Die LEDs werden als Output festgelegt
    pinMode(greenLED, OUTPUT);
    pinMode(blueLED, OUTPUT);
    digitalWrite(s0, HIGH); //Die vier weißen LEDs am Farbsensor sollen leuchten
    digitalWrite(s1, HIGH);
}


/**************************************************************************************
 * Hier werden die entsprechenden LEDs geschaltet
*****************************************************************************************/
int ColorRec::led_color(int s0,int s1,int s2,int s3,int out,int redLED,int greenLED,int blueLED)
{
    
    digitalWrite(s2, LOW);
    digitalWrite(s3, LOW);
    red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
    digitalWrite(s3, HIGH);
    blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
    digitalWrite(s2, HIGH);
    green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
    Serial.print(" Wert Rot: "); //Auf dem seriellen Monitor soll jeweils „Wert“
    Serial.print(red, DEC); //mit der entsprechenden Farbe angezeigt
    Serial.print(" Wert Gruen: ");//werden und dahinter der Wert, welcher in der
    Serial.print(green, DEC); //void color(); Funktion ausgelesen wurde.
    Serial.print(" Wert Blau: ");
    Serial.print(blue, DEC);
   
   // Hier folgen die Befehle für die LEDs
    if (red < blue && red < green && red < 20 && green > 15) //Wenn der Filterwert für rot //kleiner ist als alle anderen Werte..
    {
        Serial.println(" – (Rote Farbe)"); //..soll “Rote Farbe“ am seriellen //Monitor angezeigt werden und..
        digitalWrite(redLED, HIGH); //…ie rote LED leuchtet auf, die anderen
        digitalWrite(greenLED, LOW); //bleiben aus
        digitalWrite(blueLED, LOW);
        colorResult = 1;
    }
    else if (blue < red && blue < green) //Das gleiche bei Blau und Grün
    {
        Serial.println(" – (Blaue Farbe)");
        digitalWrite(redLED, LOW);
        digitalWrite(greenLED, LOW);
        digitalWrite(blueLED, HIGH);
        colorResult = 3;
    }
    else if (green < red && green < blue || green < blue && green < 15)
    {
        Serial.println(" – (Gruene Farbe)");
        digitalWrite(redLED, LOW);
        digitalWrite(greenLED, HIGH);
        digitalWrite(blueLED, LOW);
        colorResult = 2;
    }
    else
    { //Wenn keine Werte vorhanden sind..
        Serial.println(); //..nichts auf dem seriellen Monitor anzeigen und..
    }

    delay(300);

    return colorResult;

}
