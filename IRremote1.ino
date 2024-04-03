#include <IRremote.h> 

#define RECV_PIN 11

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(RECV_PIN);
}

void loop() {
  if (IrReceiver.decode()) {
    delay(200);
    IrReceiver.resume();
    Serial.print(IrReceiver.decodedIRData.command, DEC);
    Serial.print("");
    Serial.println();
  }
}
