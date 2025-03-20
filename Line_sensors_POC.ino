#include <Zumo32U4.h>

Zumo32U4ButtonA buttonA;
// Zumo32U4ButtonB buttonB;
// Zumo32U4ButtonC buttonC;
// Zumo32U4Buzzer  buzzer;
//Zumo32U4Encoders 
//Zumo32U4IMU
//Zumo32U4IRPulses
//Zumo32U4LCD
Zumo32U4LineSensors sensors;
// Zumo32U4Motors motors;
Zumo32U4OLED display;
// Zumo32U4ProximitySensors proxSensors;
//ledRed()
//ledGreen()
//ledYellow()
//usbPowerPresent()
//readBatteryMillivolts()

#define THRESHOLD 1000  // Microseconds 

unsigned int sensorVals[3];

void setup() {
  sensors.initThreeSensors();

  display.clear();
  display.print(" Ready  ");
  display.gotoXY(0,1);
  display.print(" Press A");

  //Don't proceed until button A is pressed
  buttonA.waitForButton();

  display.clear();
}

void loop() {
  //Read values of the sensors into the array
  sensors.read(sensorVals);

  //Check left sensor, print R to screen if it detects reflection
  if (sensorVals[0] < THRESHOLD)
  {
    display.gotoXY(0,0);
    display.print("L");
  }
  else
  {
    display.gotoXY(0,0);
    display.print(" ");
  }

  //Check right sensor, print R to screen if it detects reflection
  if (sensorVals[2] < THRESHOLD)
  {
    display.gotoXY(6, 0);
    display.print("R");
  }
  else
  {
    display.gotoXY(6,0);
    display.print(" ");
  }
}
