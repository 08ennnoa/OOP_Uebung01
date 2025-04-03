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
//Ändere das letze Beispiel so, das es die zusätzlich Möglichkeit gibt        *
//zwischen analogem und digitalem Blinken umzuschalten.                       *
//Außerdem soll mit der Taste 's' die synchronisierung der Blinker            *
//getoggelt werden können.                                                    *
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

#define ANALOGBLINKER_POLLTIME 10
#define ANALOGBLINKER_MIN 100
#define ANALOGBLINKER_MAX 1000

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

    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(TASTER1, INPUT_PULLUP);
    pinMode(TASTER2, INPUT_PULLUP);
    pinMode(POT1, INPUT);

    blinker(BLINKTIME, true, LED1, LED2);
    a_blinker.init(LED1, BLINKTIME, ANALOGBLINKER_POLLTIME, true);
}

void loop()
{
    if (digitalRead(TASTER1) == LOW)
    {
        if (taster1PressedTime == 0)
        {
            taster1PressedTime = millis();
        }
        else if (millis() - taster1PressedTime > LONGPRESSTIME)
        {
            isBlinkerEnabled = !isBlinkerEnabled;
            taster1PressedTime = 0;
        }
    }
    else
    {
        if (taster1PressedTime > 0 && millis() - taster1PressedTime <= LONGPRESSTIME)
        {
            isAnalogBlinkerActive = false;
        }
        taster1PressedTime = 0;
    }

    if (digitalRead(TASTER2) == LOW)
    {
        if (taster2PressedTime == 0)
        {
            taster2PressedTime = millis();
        }
        else if (millis() - taster2PressedTime > LONGPRESSTIME)
        {
            isBlinkerEnabled = !isBlinkerEnabled;
            taster2PressedTime = 0;
        }
    }
    else
    {
        if (taster2PressedTime > 0 && millis() - taster2PressedTime <= LONGPRESSTIME)
        {
            isAnalogBlinkerActive = true;
        }
        taster2PressedTime = 0;
    }

    if (isBlinkerEnabled)
    {
        if (isAnalogBlinkerActive)
        {
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
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
    }
}