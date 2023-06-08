#ifndef COLORRECOGNITION_H
#define COLORRECOGNITION_H

#include <Arduino.h>


class ColorRec
{
    private:
        // Variablen fuer Farben benennen 
            int red; 
            int green;
            int blue;
            int s0;
            int s1;
            int s2;
            int s3;
            int out;
            int redLED;
            int greenLED;
            int blueLED;
            int colorResult;

    public:
        // Funktion zur Deklarierung der Pins
            void esp_setup(int s0, int s1, int s2, int s3, int out, int redLED, int greenLED, int blueLED);

        // Funktion zur Schaltung der LEDs
            int led_color(int s0, int s1, int s2, int s3, int out, int redLED, int greenLED, int blueLED);

};

#endif