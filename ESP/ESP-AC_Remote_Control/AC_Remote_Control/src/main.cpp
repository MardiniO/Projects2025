#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

// Pin Definitions
int kRecvPin = 22; // Pin used to receive IR communication
IRrecv irrecv(kRecvPin); // Binds GPIO pin to the IR receiver module's data pin

decode_results results; 

void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn(); 
  while (!Serial){
    delay(50);
  }
  Serial.println("");
  Serial.print("IRrecvDemo is now up and running on pin: ");
  Serial.print(kRecvPin);
}

void loop() {
  if (irrecv.decode(&results)){
    serialPrintUint64(results.value, HEX);
    Serial.println();
    irrecv.resume();
  }
  delay(100);
}
