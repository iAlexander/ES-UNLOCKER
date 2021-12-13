
//////////////////////////////////////////////
//        include libraries                 //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library
#define REMOTEXY_MODE__ESP32CORE_BLE

#include "RemoteXY.h"
#include <Arduino.h>
#include "FastCRC.h"
#include "functions.h"



// RemoteXY connection settings
#define REMOTEXY_BLUETOOTH_NAME "OKAI_Scooter"

// RemoteXY configurate
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
{ 255,5,0,3,0,146,0,8,16,1,
2,0,3,90,57,7,163,26,24,16,
85,110,108,111,99,107,0,76,111,99,
107,0,65,7,3,2,9,9,130,1,
4,54,56,21,27,129,0,25,56,15,
6,16,76,105,103,104,116,0,3,131,
21,65,22,8,162,26,130,1,4,17,
56,31,27,129,0,16,20,31,6,16,
77,97,120,32,83,112,101,101,100,0,
7,52,22,31,20,5,2,26,1,129,
0,44,32,7,3,16,107,109,47,104,
0,2,0,44,40,12,5,162,26,31,
31,79,78,0,79,70,70,0,129,0,
8,41,34,4,16,70,97,115,116,32,
65,99,99,101,108,101,114,97,116,105,
111,110,0 };
// this structure defines all the variables of your control interface
struct {

    // input variable
  uint8_t lockState; // =1 if switch ON and =0 if OFF
  uint8_t light_select; // =0 if select position A, =1 if position B, =2 if position C, ...
  int16_t speed;  // −32767.. +32767
  uint8_t fastAcceleration; // =1 if switch ON and =0 if OFF

    // output variable
  uint8_t status_LED_r; // =0..255 LED Red brightness
  uint8_t status_LED_g; // =0..255 LED Green brightness
  uint8_t status_LED_b; // =0..255 LED Blue brightness

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//                  Setup                  //
/////////////////////////////////////////////

#define PIN_SWITCH_1 13
#define PIN_RELAY 14
#define INTERVAL 500
#define REBOOTINTERVAL 240

unsigned long start_time = 0;
int run_once = 0;
int tick = 0;
bool isUnlocked = false;
int defaultSpeed = 25;

bool defaultFastAcceleration = 1;
bool defaultKph = 0; // 0 for MP/H, 1 for KM/H
bool defaultLightOn = 0;
bool defaultLightBlink = 0; // Will overwrite lightOn if activated


// If your scooter turns off after 2 minutes you need to enable reboot mode.
// DON'T USE THIS WITHOUT ADDING RELAYS TO YOUR MOTOR CABLES!
bool isRebootMode = false;


////////////////////////////////////////////
//                   Main                 //
///////////////////////////////////////////

void setup()
{
  RemoteXY_Init ();
  Serial.begin(115200);
  Serial2.begin(9600);
  pinMode (PIN_SWITCH_1, OUTPUT);
  pinMode (PIN_RELAY, OUTPUT);
}

void loop()
{
  RemoteXY_Handler ();

  // Check for changes in RemoteXY
  int speed = RemoteXY.speed > 0 ? RemoteXY.speed : defaultSpeed;
  bool lightOn = RemoteXY.light_select == 0 ? 1 : 0;
  bool lightBlink = RemoteXY.light_select == 2 ? 1 : 0;
  bool fastAcceleration = RemoteXY.fastAcceleration == 1 ? 1 : defaultFastAcceleration;

  digitalWrite(PIN_SWITCH_1, (RemoteXY.lockState == 0 || tick > REBOOTINTERVAL)?LOW:HIGH);
  Serial.print(RemoteXY.lockState);
   if(RemoteXY.lockState == 1){
    if(millis() > start_time + INTERVAL){
      if(isRebootMode) tick++;
      if(!isUnlocked){
        unlock(PIN_SWITCH_1, speed, fastAcceleration, defaultKph, lightOn, lightBlink);
        isUnlocked = true;
      }
      if(isRebootMode && tick > REBOOTINTERVAL) {
        reboot(PIN_RELAY, PIN_SWITCH_1, speed);
        tick = 0;
      } else {
        keepActive(speed, fastAcceleration, defaultKph, lightOn, lightBlink);
        run_once = 0;
        start_time = millis();
      }
      }
      // Status LED
      RemoteXY.status_LED_r = 0;
      RemoteXY.status_LED_g = 255;
      RemoteXY.status_LED_b = 0;
    }
    else{
      if (run_once == 0){
      sendCommand(stopCommand(lightBlink));
      isUnlocked = false;
      run_once = 1;
      }
      if(tick > 0) {
        tick = 0;
      }
      // Status LED
      RemoteXY.status_LED_r = 255;
      RemoteXY.status_LED_g = 0;
      RemoteXY.status_LED_b = 0;
    }
}
