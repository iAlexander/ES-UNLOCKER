FastCRC8 CRC8; //Checksum Library
uint32_t crc;

// Generate 4th byte with commands
unsigned char GenCommandByte(bool fastAcceleration, bool kph, bool lightOn, bool lightBlink, bool powerOn)
{
  // bool bits[8] = {
  //   0,
  //   0,
  //   fastAcceleration,
  //   kph,
  //   0,
  //   lightOn,
  //   lightBlink,
  //   powerOn};
  bool bits[8] = {
    powerOn,
    lightBlink,
    lightOn,
    0,
    kph,
    fastAcceleration,
    0,
    0};
    unsigned char c = 0;
    for (int i=0; i < 8; ++i)
        if (bits[i])
            c |= 1 << i;
    return c;
}

// Shortcut startup / keep alive command
uint8_t startCommand(bool fastAcceleration, bool kph, bool lightOn, bool lightBlink) 
{
  return GenCommandByte(fastAcceleration, kph, lightOn, lightBlink, 1);
}

// Shortcut stop scooter command
uint8_t stopCommand(bool lightBlink) 
{
  return GenCommandByte(0, 1, 0, lightBlink, 0);
}

// Combine commands, calculate CRC and transmit to ESC

void sendCommand(uint8_t commandByte, int speed = 20)
{   
  uint8_t buf[6];
  buf[0] = 0xA6; buf[1] = 0x12; buf[2] = 0x02;
  buf[3] = commandByte;
  buf[4] = speed;
  buf[5] = CRC8.maxim(buf, 5);
  Serial2.write(buf, sizeof(buf));
}

