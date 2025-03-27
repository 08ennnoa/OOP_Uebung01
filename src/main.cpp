// ****************************************************************************
// *                                                                          *
// * Aufgabe:                                                                 *
// *                                                                          *
// * -> Schreib ein Programm mit folgenden Eigenschaften:                     *
// *    Es gibt zwei Taster (TASTER1, TASTER2), zwei LEDs (LED1, LED2) und    *
// *    ein Potentiometer. Taster1 schaltet einen digitalen Blinker auf die   *
// *    beiden LEDs, Taster2 schaltet einen analogen Blinker auf die beiden   *
// *    LEDs. Die Geschwindigkeit des Blinkers soll mit dem Poti zwischen     *
// *    50ms und 1000ms eingestellt werden können. Ein langer Tastendruck     *
// *    auf einen der beiden Taster toggelt die Blinkfunktion ein/aus.        *
// *                                                                          *
// * -> Suche dir ein/zwei Mitarbeiter und forke dieses Projekt               *
// * -> Teile die Arbeit auf die Mitarbeiter so auf, dass ein fast-forward-   *
// *    merge ermöglicht wird.                                                *
// * -> Fülle die bestehenden Header-Dateien und erzeuge die entsprechenden   *
// *    Implementierungen (cpp-Dateien). Verwende ausschließlich Klassen!     *
// *                                                                          *
// * -> Erstelle einen pull-request                                           *
// *                                                                          *
// ****************************************************************************

#include <Arduino.h>
#include "digitalblinker.h"
#include "helper.h"
#include "analogblinker.h"

#define LED1 3    // Low-side switch (leuchtet mit LOW)
#define LED2 5    // Low-side switch (leuchtet mit LOW)
#define TASTER1 4 // LOW wenn gedrückt
#define TASTER2 2 // LOW wenn gedrückt
#define POT1 A7   
#define BLINKTIME 500

#define DB_ZEIT 50
#define LONGPRESSTIME 1000

#define ANALOGBLINKER_POLLTIME 10 // ms
#define ANALOGBLINKER_MIN 100 // ms
#define ANALOGBLINKER_MAX 1000 // ms

// Instanzieren der Strukturen
blinker digitalblinker;
button taster1;
analogblinker a_blinker;

bool isAnalogBlinkerActive = false;

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

    // Initialisierung der Strukturen
    digitalblinker.init(BLINKTIME, true, LED1, LED2);
    taster1.init(TASTER1, false, DB_ZEIT, LONGPRESSTIME);
    a_blinker.init(LED1, BLINKTIME, ANALOGBLINKER_POLLTIME, true);
}

void loop()
{
    // Taster abfragen
    taster1.poll();

    // Umschalten zwischen digitalem und analogem Blinker
    if (digitalRead(TASTER1) == LOW)
    {
        isAnalogBlinkerActive = false;
    }
    else if (digitalRead(TASTER2) == LOW)
    {
        isAnalogBlinkerActive = true;
    }

    // Aktiven Blinker ausführen
    if (isAnalogBlinkerActive)
    {
        a_blinker.poll();
    }
    else
    {
        digitalblinker.poll();
    }

    // Potentiometer-Wert lesen und Blinkgeschwindigkeit anpassen
    int potiValue = analogRead(POT1);
    int blinkSpeed = map(potiValue, 0, 1023, ANALOGBLINKER_MIN, ANALOGBLINKER_MAX);
    a_blinker.init(LED1, blinkSpeed, ANALOGBLINKER_POLLTIME, true);
}