#include <IRremote.hpp>

#define RECV_PIN 11

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(RECV_PIN);
}

void loop() {
  if (IrReceiver.decode()) {
    // Es wurden Daten empfangen
    IrReceiver.printIRResultShort(&Serial);

    // Ziffer auswerten
    int dig = decodeIrDigit();
    Serial.println(" -> " + String(dig));

    IrReceiver.resume();
    delay(200);
  }
}


int irNumber = 0;



int irNumberS() {

  if(dig == -1)
}
/**
* Dekodiert die Ziffer der auf der Infrarot-Fernbedienung gedrückten Taste.
* - Wenn ein Repeat-Code empfangen wurde, wird -2 zurückgegeben.
* - Wenn eine andere Taste gedrückt wurde, wird -1 zurückgegeben.
* - Wenn eine Ziffern-Taste gedrückt wurde, wird die betreffende Ziffer zurückgegeben.
*/
int decodeIrDigit() {

  // Repeat-Flag auswerten
  Serial.print("Flags ");
  Serial.print(IrReceiver.decodedIRData.flags, BIN);
  if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT) {
    Serial.print(" Repeat");
    return -2;
  }

  switch (IrReceiver.decodedIRData.command) {
    case 0x16:
      return 1;
    case 0x19:
      return 2;
    case 0xD:
      return 3;
    case 0xC:
      return 4;
    case 0x18:
      return 5;
    case 0x5E:
      return 6;
    case 0x8:
      return 7;
    case 0x1C:
      return 8;
    case 0x5A:
      return 9;
    case 0x7:
      return 0;
  }
  return -1;
}
