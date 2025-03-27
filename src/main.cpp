// ****************************************************************************
// *                                                                          *
// * Aufgabe:                                                                 *
// *                                                                          *
// * -> Schreibe ein Programm mit folgenden Eigenschaften:                    *
// *    Es gibt zwei Taster (TASTER1, TASTER2), zwei LEDs (LED1, LED2) und    *
// *    ein Potentiometer. TASTER1 schaltet einen digitalen Blinker auf die   *
// *    beiden LEDs, TASTER2 schaltet einen analogen Blinker auf die beiden   *
// *    LEDs. Die Geschwindigkeit des Blinkers soll mit dem Poti zwischen     *
// *    100ms und 1000ms eingestellt werden können. Ein langer Tastendruck    *
// *    auf einen der beiden Taster toggelt die Blinkfunktion ein/aus.        *
// *                                                                          *
// * -> Suche dir ein/zwei Mitarbeiter und forke dieses Projekt.              *
// * -> Teile die Arbeit auf die Mitarbeiter so auf, dass ein fast-forward-   *
// *    merge ermöglicht wird.                                                *
// * -> Fülle die bestehenden Header-Dateien und erzeuge die entsprechenden   *
// *    Implementierungen (cpp-Dateien). Verwende ausschließlich Klassen!     *
// *                                                                          *
// * -> Erstelle einen Pull-Request.                                          *
// *                                                                          *
// ****************************************************************************

#include <Arduino.h>
#include "digitalblinker.h"
#include "helper.h"
#include "analogblinker.h"

// Definition der Pins und Konstanten
#define LED1 3    // Low-side switch (leuchtet mit LOW)
#define LED2 5    // Low-side switch (leuchtet mit LOW)
#define TASTER1 4 // LOW wenn gedrückt
#define TASTER2 2 // LOW wenn gedrückt
#define POT1 A7   // Potentiometer-Pin
#define BLINKTIME 500

#define DB_ZEIT 50
#define LONGPRESSTIME 1000

#define ANALOGBLINKER_POLLTIME 10 // ms
#define ANALOGBLINKER_MIN 100     // ms
#define ANALOGBLINKER_MAX 1000    // ms

// Instanzieren der Klassen
blinker digitalblinker;
analogblinker a_blinker;

bool isAnalogBlinkerActive = false;
bool isBlinkerEnabled = true;

unsigned long taster1PressedTime = 0;
unsigned long taster2PressedTime = 0;

void setup()
{
    Serial.begin(57600);
    Serial.println("..Start..\n");

    // Pins initialisieren
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(TASTER1, INPUT_PULLUP);
    pinMode(TASTER2, INPUT_PULLUP);
    pinMode(POT1, INPUT);

    // Initialisierung der Klassen
    digitalblinker.init(BLINKTIME, true, LED1, LED2);
    a_blinker.init(LED1, BLINKTIME, ANALOGBLINKER_POLLTIME, true);
}

void loop()
{
    // Taster1 abfragen
    if (digitalRead(TASTER1) == LOW)
    {
        if (taster1PressedTime == 0)
        {
            taster1PressedTime = millis();
        }
        else if (millis() - taster1PressedTime > LONGPRESSTIME)
        {
            isBlinkerEnabled = !isBlinkerEnabled; // Toggle Blinker ein/aus
            taster1PressedTime = 0;
        }
    }
    else
    {
        if (taster1PressedTime > 0 && millis() - taster1PressedTime <= LONGPRESSTIME)
        {
            isAnalogBlinkerActive = false; // Digitaler Blinker aktivieren
        }
        taster1PressedTime = 0;
    }

    // Taster2 abfragen
    if (digitalRead(TASTER2) == LOW)
    {
        if (taster2PressedTime == 0)
        {
            taster2PressedTime = millis();
        }
        else if (millis() - taster2PressedTime > LONGPRESSTIME)
        {
            isBlinkerEnabled = !isBlinkerEnabled; // Toggle Blinker ein/aus
            taster2PressedTime = 0;
        }
    }
    else
    {
        if (taster2PressedTime > 0 && millis() - taster2PressedTime <= LONGPRESSTIME)
        {
            isAnalogBlinkerActive = true; // Analoger Blinker aktivieren
        }
        taster2PressedTime = 0;
    }

    // Blinker ausführen, wenn aktiviert
    if (isBlinkerEnabled)
    {
        if (isAnalogBlinkerActive)
        {
            // Potentiometer-Wert lesen und Blinkgeschwindigkeit anpassen
            int potiValue = analogRead(POT1);
            int blinkSpeed = map(potiValue, 0, 1023, ANALOGBLINKER_MIN, ANALOGBLINKER_MAX);
            a_blinker.init(LED1, blinkSpeed, ANALOGBLINKER_POLLTIME, true);
            a_blinker.poll();
        }
        else
        {
            digitalblinker.poll();
        }
    }
    else
    {
        // LEDs ausschalten, wenn Blinker deaktiviert ist
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
    }
}