// ES-UNLOCKER - Okai ES200B Scooter (Arduino Nano Version)

void setup() {

  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  
  // initialize Serial:
  Serial.begin(9600);
  delay(500);
  Serial.println("Starting the UNLOCK procedure...");
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