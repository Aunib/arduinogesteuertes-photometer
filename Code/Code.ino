/*
   Der Beispielcode wurde von Adafruit übernommen

   Dieser Code wurde von Simon Steinberg im Rahmen der vorbereitung auf die MSA-Präsentationsprüfung im Schuljahr 2019/2020 erstellt.

*/


/*
   Bibliothek für ...
*/

#include <Wire.h>                 //Serielle Kommunikation
#include <Adafruit_Sensor.h>      //Sensoren von Adafruit
#include <Adafruit_TSL2561_U.h>   //Lichtsensor TSL_2561_U von Adafruit
#include <math.h>                 //Mathematische berechnungen


/*
   Variablendefinitionen:
*/
int readed;             //Aktuelle Eingabe aus dem Seriellen Monitor
char text;              //readed als Buchstabe
int ausgabeformat;      //Aktuelle Einstellung des Ausgabeformates: 0=lux, 1=Extinktion
int lux;                //Aktueller Messwert
int leer;               //Wert der Leerprobe
#define messung_led 5   //Pin, an den die LED angeschlossen ist

Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345); //Initialisierung des Lichtsensors

void displaySensorDetails(void) //Aus dem Beispielcode übernommene Funktion um Sensoreinstellungen anzuzeigen
{
  sensor_t sensor;
  tsl.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" lux");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" lux");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" lux");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

/**************************************************************************/
/*
    Configures the gain and integration time for the TSL2561
*/
/**************************************************************************/
void configureSensor(void)    //Aus dem Beispielcode übernommene Funktion um den Sensor zu konfigurieren
{
  tsl.enableAutoRange(true);            /* Auto-gain ... switches automatically between 1x and 16x */

  /* Changing the integration time gives you better sensor resolution (402ms = 16-bit data) */
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);      /* fast but low resolution */

  /* Update these values depending on what you've set above! */
  Serial.println("------------------------------------");
  Serial.print  ("Gain:         "); Serial.println("Auto");
  Serial.print  ("Timing:       "); Serial.println("13 ms");
  Serial.println("------------------------------------");
}

void menue()    //Von mir geschriebene Funktion, um den Sensor mithilfe des Seriellen Monitors anzusteuern
{
  char equal = '\=';              //Definition zweier Variablen, um die Menügestaltung zu realisieren(Wenn ich diese Texte jeweils in die Strings schreiben würde, würde der RAM vollaufen.
  char newline = '\n';            //
  readed = Serial.read();     //Auslesen des Inputs aus dem seriellen Monitor
  Serial.print(newline);          //
  for (int i = 0; i <= 32; i++)   //
  { //Ausgabe der Formatierungsstruktur für den Seriellen Monitor
    Serial.print(equal);          //
  }                               //
  Serial.print(newline);          //
  Serial.print("Herzlich Willkommen im Hauptmenue des Arduinogesteuerten Photometers.\nBitte gib \"a\" ein und bestätige, um das Ausgabeformat einzustellen.\nBitte gib \"m\" ein und bestätige, um eine Messung durchzuführen.");//Ausgabe des Hauptmenüs
  Serial.print(newline);          //
  for (int i = 0; i <= 32; i++)   //
  { //
    Serial.print(equal);          //
  }                               //
  for (int i = 0; i <= 4; i++)    //Ausgabe der Formatierungsstruktur für den Seriellen Monitor
  { //
    Serial.print(newline);        //
  }                               //
  readed = Serial.read();     //
  while (readed == -1) {      //
    delay(100);               //Warten auf eine Eingabe durch den Seriellen Monitor
    readed = Serial.read();   //
  }                           //
  text = char(readed);            //Umformen der Eingabe zum Buchstaben
  switch (text)                       //
  { //Auswahl der Untermenüs
    case 'a' :                            //Für den Fall 'a'
      Serial.print(newline);                  //
      for (int i = 0; i <= 32; i++)           //
      { //
        Serial.print(equal);                  //Ausgabe der Formatierungsstruktur für den Seriellen Monitor
      }                                       //
      Serial.print(newline);                  //
      Serial.print("Hier kannst du das Ausgabeformat einstellen.\nWenn du die Ausgabe in Form von LUX haben möchtest, gib bitte \"l\" ein und bestätige.\nWenn du die Ausgabe in Form eines Extinktionswertes haben möchtest, gib bitte \"e\" ein und bestätige.");   //Ausgabe des Menüs für die Ausgabeart
      Serial.print(newline);                  //
      for (int i = 0; i <= 32; i++)           //
      { //
        Serial.print(equal);                  //
      }                                       //Ausgabe der Formatierungsstruktur für den Seriellen Monitor
      for (int i = 0; i <= 4; i++)            //
      { //
        Serial.print(newline);                //
      }                                       //
      readed = Serial.read();             //
      do {                                //
        delay(100);                       //Warten auf eine Eingabe durch den Seriellen Monitor
        readed = Serial.read();           //
      } while (readed == -1);             //
      text = char(readed);            //Umformen der Eingabe zum Buchstaben
      switch (text)                       //
      { //Auswahl der Untermenüs
        case 'l' :                            //Für den Fall 'l'
          ausgabeformat = 0;               //Setze die Variable 'ausgabeformat' auf "0"
          Serial.print(newline);              //
          for (int i = 0; i <= 32; i++)       //
          { //
            Serial.print(equal);              //Ausgabe der Formatierungsstruktur für den Seriellen Monitor
          }                                   //
          Serial.print(newline);              //
          Serial.print("0");
          Serial.print("Das Ausgabeformat wurde Erfolgreich auf \"LUX\" eingestellt.");   //Ausgabe der Bestätigungsnachricht auf den Seriellen Monitor
          Serial.print(newline);              //
          for (int i = 0; i <= 32; i++)       //
          { //
            Serial.print(equal);              //
          }                                   //Ausgabe der Formatierungsstruktur für den Seriellen Monitor
          for (int i = 0; i <= 4; i++)        //
          { //
            Serial.print(newline);            //
          }                                   //
          break;                          //Beendigung des Falls 'l'
        case 'e' :                            //Für den Fall 'e':
          ausgabeformat = 1;              //Setze die Variable 'ausgabeformat' auf "1"
          Serial.print(newline);              //
          for (int i = 0; i <= 32; i++)       //
          { //
            Serial.print(equal);              //Ausgabe der Formatierungsstruktur für den Seriellen Monitor
          }                                   //
          Serial.print(newline);              //
          Serial.print("1");
          Serial.print("Das Ausgabeformat wurde Erfolgreich auf \"Extinktionsswert\" eingestellt.");   //Ausgabe der Bestätigungsnachricht auf den Seriellen Monitor
          Serial.print(newline);              //
          for (int i = 0; i <= 32; i++)       //
          { //
            Serial.print(equal);              //
          }                                   //
          for (int i = 0; i <= 4; i++)        //Ausgabe der Formatierungsstruktur für den Seriellen Monitor
          { //
            Serial.print(newline);            //
          }                                   //
          break;                          //Beendigung des Falls 'e'

      }
      break;                          //Beendigung des Falls 'l'
    case 'm' :                            //Für den Fall 'm'
      Serial.print(newline);          //
      for (int i = 0; i <= 32; i++)   //
      { //Ausgabe der Formatierungsstruktur für den Seriellen Monitor
        Serial.print(equal);          //
      }                               //
      Serial.print(newline);          //
      Serial.print("Wenn du eine Leerprobe durchführen und das Ergebnis speichern möchtest, gebe bitte \"l\" ein und bestätige.\nWenn du eine Messung durchführen möchtest, gebe bitte \"m\" ein und bestätige.");//Ausgabe des Messungsmenüs über den Seriellen Monitor
      Serial.print(newline);          //
      for (int i = 0; i <= 32; i++)   //
      { //
        Serial.print(equal);          //
      }                               //
      for (int i = 0; i <= 4; i++)    //Ausgabe der Formatierungsstruktur für den Seriellen Monitor
      { //
        Serial.print(newline);        //
      }                               //
      readed = Serial.read();     //
      do {                        //
        delay(100);               //Warten auf eingabe durch den Seriellen Monitor
        readed = Serial.read();   //
      } while (readed == -1);     //
      switch (readed)                 //Auswahl für Funktionen
      { //
        case 'l':                         //Falls 'l' :
          lux = messung();            //Durchführung der Messung
          Serial.print(newline);          //
          for (int i = 0; i <= 32; i++)   //
          { //
            Serial.print(equal);          //Ausgabe der Formatierungsstruktur über den Seriellen Monitor
          }                               //
          Serial.print(newline);          //
          Serial.print("Das Ergebnis der Leerprobe ist ");//Ausgabe des Rahmens über den Seriellen Monitor
          Serial.print(lux);              //Ausgabe des Messwertes
          leer = lux;                         //Speicherung des Messwertes in der Variable "leer"
          Serial.print(" LUX.\nDieser Wert wurde erfolgreich als Wert der Leerprobe abgespeichert.");//Ausgabe über den Seriellen Monitor
          Serial.print(newline);          //
          for (int i = 0; i <= 32; i++)   //
          { //
            Serial.print(equal);          //
          }                               //
          for (int i = 0; i <= 4; i++)    //Ausgabe der Formatierungsstruktur über den Seriellen Monitor
          { //
            Serial.print(newline);        //
          }                               //
          break;                      //Beendigung des Falls 'l'
        case 'm':                         //Falls 'm'
          lux = messung();                    //Durchführung der Messung
          Serial.print(newline);          //
          for (int i = 0; i <= 32; i++)   //
          { //
            Serial.print(equal);          //Ausgabe der Formatierungsstruktur über den Seriellen Monitor
          }                               //
          Serial.print(newline);          //
          Serial.print("Das Ergebnis der Probe ist ");//Ausgabe des Rahmens über den Seriellen Monitor
          switch (ausgabeformat) {            //Auswahl für Ausgabeformate
            case 0:                             //falls '0' (LUX)
              Serial.print(lux);              //Ausgabe des Messwertes
              Serial.print("LUX.");               //Ausgabe über den Seriellen Monitor
              break;                          //
            case 1:                     //falls '1' (Extinktion)
              Serial.print(berechneExtinktion(lux, leer));
              break;
              for (int i = 0; i <= 32; i++)   //
              { //
                Serial.print(equal);          //
              }                               //
              for (int i = 0; i <= 4; i++)    //Ausgabe der Formatierungsstruktur über den Seriellen Monitor
              { //
                Serial.print(newline);        //
              }                               //
          }
          break;                      //Beendigung des Falls 'm'
      }
  }
}

float berechneExtinktion(int I0, int I1)//selbstgeschriebene Funktion, um die Extinktion zu berechnen.
{
  return (I0 / I1);//Eigendliche Berechnung
}

int messung() {                     //selbstgeschriebene Funktion, um die Messung durchzuführen
  int ergebnis;                         //neuer Integer, um das Ergebnis zwischenzuspeichern
  digitalWrite(messung_led, HIGH);  //LED anschalten
  delay(250);                           //250 ms warten
  sensors_event_t event;            //
  tsl.getEvent(&event);             //
  if (event.light)                  //
  { //aus dem Beispielcode übernommene Codezeilen, um jetzt wirklich zu messen.
    ergebnis = (event.light);       //
  }                                 //
  delay(250);                           //250 ms warten
  digitalWrite(messung_led, LOW);   //LED ausschalten
  return (ergebnis);            //Funktion beenden und den Inhalt von 'ergebnis' zurückgeben
}

void setup(void)                    //Setup-Funktion des Arduinos
{
  Serial.begin(9600);                   //Beginn der Seriellen Kommunikation mit dem Seriellen Monitor (Geschwindigkeit 9600 Baud)
  Serial.println("Light Sensor Test"); Serial.println("");                          //
  //
  if (!tsl.begin())                                                                 //
  { //
    /* There was a problem detecting the TSL2561 ... check your connections */      //
    Serial.print("Ooops, no TSL2561 detected ... Check your wiring or I2C ADDR!");  //
    while (1);                                                                      //
  }                                                                                 //Aus dem Beispielcode übernommen
  //
  /* Display some basic information on this sensor */                               //
  displaySensorDetails();                                                           //
  //
  /* Setup the sensor gain and integration time */                                  //
  configureSensor();                                                                //
  //
  /* We're ready to go! */                                                          //
  Serial.println("");                                                               //
  //
  pinMode(messung_led, OUTPUT);                                                 //Den LED-Pin auf Ausgang stellen
}

void loop(void)                   //Wiederholt sich immer
{
  menue();                    //Aufrufen der Menü-funktion
  delay(250);                     //250 ms warten
}
