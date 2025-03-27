
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
// *                                                                          *
// ****************************************************************************

#include <Arduino.h>

#define LED1 3    // Low-side switch (leuchtet mit LOW)
#define LED2 5    // Low-side switch (leuchtet mit LOW)
#define TASTER1 4 // LOW wenn gedrückt
#define TASTER2 2 // LOW wenn gedrückt
#define POT1 A7   

void setup()
{
    Serial.begin(57600); // Baud rate
    Serial.println("..Start..\n");
    PinMode(LED1, OUTPUT);
    PinMode(LED2, OUTPUT);
    PinMode(TASTER1, INPUT_PULLUP);
    PinMode(TASTER2, INPUT_PULLUP);
    PinMode(POT1, INPUT);
}

void loop()
{
}


//änderung 2
