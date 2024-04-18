/**
* Auswertung einer Infrarot-Fernsteuerung (Remote Control):
* - Decodierung der gedrückten Ziffern-Taste
* - Ignorieren von Repeat-Commands
* - Zusammenbau der eingegebenen mehrstelligen Zahl aus den emfangenen Ziffern
*
* Bibliothek IRremote ab Version 3.6.1 (z.B. 4.3.1)
*
* Siehe Arbeitsheft 'Arduino Lernen' Kap. 4.13
*/

#include <IRremote.hpp>

#define RECV_PIN 11

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(RECV_PIN);
}

void loop() {
  if (IrReceiver.decode()) {
    // Es wurden Daten empfangen
    // IrReceiver.printIRResultShort(&Serial);

    // Emfangene Daten auswerten
    int num = decodeIrNumber();
    if (num >= 0) {
      // Eine Zahl wurde eingegeben
      Serial.println(" -> " + String(num));
    }

    IrReceiver.resume();
    delay(200);
  }
}

// Puffer zur Dekodierung der eingegebene Zahl.
int irNumber = 0;

/**
* Dekodiert eine auf der Infrarot-Fernbedienung eingegebene Zahl.
* - Wenn die Eingabe der Zahl abgeschlossen ist, wird diese zurückgegeben.
* - Wenn die Eingabe der Zahl noch nicht abgeschlossen ist, wird ein negativer Wert zurückgegeben.
*/
int decodeIrNumber() {
  // Ziffer auswerten
  int dig = decodeIrDigit();
  if (dig == -1) {
    // Abschluss der Ziffern-Eingabe
    int ret = irNumber;
    //Serial.println(" -> " + String(ret));
    irNumber = 0;  // und wieder von vorne ...
    return ret;
  } else if (dig >= 0) {
    // Ziffer empfangen: Nächste Stelle
    irNumber = irNumber * 10 + dig;
  }
  return -1;  // Eingabe ist noch nicht fertig
}

/**
* Dekodiert die Ziffer der auf der Infrarot-Fernbedienung gedrückten Taste.
* - Wenn ein Repeat-Code empfangen wurde, wird -2 zurückgegeben.
* - Wenn eine andere Taste gedrückt wurde, wird -1 zurückgegeben.
* - Wenn eine Ziffern-Taste gedrückt wurde, wird die betreffende Ziffer zurückgegeben.
*/
int decodeIrDigit() {

  // Repeat-Flag auswerten
  // Serial.print("Flags ");
  // Serial.print(IrReceiver.decodedIRData.flags, BIN);
  if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT) {
    // Serial.print(" Repeat");
    return -2;
  }

  switch (IrReceiver.decodedIRData.command) {
    case 0x07:
      return 0;
    case 0x16:
      return 1;
    case 0x19:
      return 2;
    case 0x0D:
      return 3;
    case 0x0C:
      return 4;
    case 0x18:
      return 5;
    case 0x5E:
      return 6;
    case 0x08:
      return 7;
    case 0x1C:
      return 8;
    case 0x5A:
      return 9;
  }
  return -1;
}