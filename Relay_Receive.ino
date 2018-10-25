/*
  Remote control Receiver for Construal 3M
  Uses State machine to only allow moving in one direction at a time
*/
#include <SoftwareSerial.h>

#define RX 10
#define TX 11

enum States {ON, OFF};   //The two possible states
States switchState[4] = {OFF, OFF, OFF, OFF};  // All Switches start states are OFF
byte switchPin[4] = {4, 5, 6, 7};  // The pins for the Switches

States machineState = OFF; // machine starts OFF

int inByte = 0;  // for incoming serial data

SoftwareSerial mySerial(RX, TX);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  for (byte i = 0 ; i <= 3 ; i++) {
    pinMode(switchPin[i], OUTPUT);
  }
  turnAllOFF();

}

void loop() {
  if (mySerial.available() > 0) {
    inByte = mySerial.read() - 48;
    Serial.print("received: ");
    Serial.println(inByte);
    switch (inByte) {
      case 0:
        turnAllOFF();
        break;
      case 4:
          turnON(inByte);
        break;
      case 5:
        turnON(inByte);
        break;
      case 6:
        turnON(inByte);
        break;
      case 7:
        turnON(inByte);
        break;
      default:
        turnAllOFF();
        break;

    }
  }

}

void turnOFF (int pin) {
  switch (machineState) {
    case OFF: {
        Serial.println("Not moving now");
        break;
      }
    case ON: {
        digitalWrite(pin, HIGH); // Stop Moving
        switchState[pin] = OFF;
        machineState = OFF; // Report stop
        Serial.println("Stopped!");
        break;
      }
  }

}

void turnON(int pin) {
  switch (machineState) {
    case OFF: {
        digitalWrite(pin, LOW); // Move
        switchState[pin] = ON;
        machineState = ON; // Report Moving
        Serial.println("Running!");
        break;
      }
    case ON: {
        Serial.println("already moving");
//        turnAllOFF;
        //        break;
      }
  }
}

void turnAllOFF() {
  for (byte i = 0 ; i <= 3 ; i++) {
    digitalWrite(switchPin[i], HIGH);
    switchState[i] = OFF;
    machineState = OFF;
  }
}

void turnAllON() {
  for (byte i = 0 ; i <= 3 ; i++) {
    digitalWrite(switchPin[i], LOW);
    switchState[i] = ON;
    machineState = ON;
  }
}
