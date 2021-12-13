// ES-STARTER - Okai ES200B Scooter (Arduino Nano Version)

/*
   -- Simple version of ES-UNLOCKER --
   ES-UNLOCKER is released under the MIT license. Check the LICENSE file for details.
   Copyright © 2021 <a href="http://iashchuk.com">Alexander Iashchuk</a>.
*/

void setup() {

  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  
  // initialize Serial:
  Serial.begin(9600);
  delay(500);
  Serial.println("Starting the STARTER UNLOCK procedure...");
  delay(500);
  Serial.write(0xA6);
  Serial.write(0x12);
  Serial.write(0x02);
  Serial.write(0x10);
  Serial.write(0x14);
  Serial.write(0xCF);
  delay(500);
  Serial.write(0xA6);
  Serial.write(0x12);
  Serial.write(0x02);
  Serial.write(0x11);
  Serial.write(0x14);
  Serial.write(0x0B);
}

void loop() {
  delay(500);
  Serial.write(0xA6);
  Serial.write(0x12);
  Serial.write(0x02);
  Serial.write(0x15);
  Serial.write(0x14);
  Serial.write(0x30);
}