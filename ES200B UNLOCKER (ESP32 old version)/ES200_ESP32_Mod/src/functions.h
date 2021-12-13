#include "commands.h"

void keepActive(int speed, bool fastAcceleration = 0, bool kph = 1, bool lightOn = 1, bool lightBlink = 0) {
  sendCommand(startCommand(fastAcceleration, kph, lightOn, lightBlink), speed);
}

void unlock(int pin, int speed, bool fastAcceleration = 0, bool kph = 1, bool lightOn = 1, bool lightBlink = 0) {
    digitalWrite(pin,HIGH);
    sendCommand(stopCommand(lightBlink));
    delay(500);
    sendCommand(startCommand(0, kph, lightOn, 0), speed);
    delay(500);
}

void lock(int pin, bool lightBlink = 0) {
    sendCommand(stopCommand(lightBlink));
    delay(500);
    digitalWrite(pin,LOW);
}


// Sequence used to reboot scooter to bypass shutdown after 2 minutes

void reboot(int relayPin, int pwrPin, int speed, bool fastAcceleration = 0, bool kph = 1, bool lightOn = 1, bool lightBlink = 0) {
  digitalWrite(relayPin,HIGH);
  sendCommand(stopCommand(lightBlink));
  digitalWrite(pwrPin,LOW);
  delay(500);
  digitalWrite(pwrPin,HIGH);
  sendCommand(startCommand(fastAcceleration, kph, lightOn, lightBlink), speed);
  delay(500);
  sendCommand(startCommand(fastAcceleration, kph, lightOn, lightBlink), speed);
  delay(500);
  sendCommand(startCommand(fastAcceleration, kph, lightOn, lightBlink), speed);
  delay(1500);
  digitalWrite(relayPin,LOW);
}