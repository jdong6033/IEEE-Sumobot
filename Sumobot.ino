#include <Zumo32U4.h>

Zumo32U4ButtonA buttA;
Zumo32U4ButtonB buttB;
Zumo32U4ButtonC buttC;
Zumo32U4IRPulses Ir;
//Zumo32U4LineSensors sensors;
Zumo32U4Motors motors;
Zumo32U4OLED display;
Zumo32U4ProximitySensors proxSense;

bool fiveCheck = false; //checking if five seconds have passed

void setup() {
  proxSense.initThreeSensors(); //initializing the sensors
  display.clear(); //clearing the display
}

void stop(){
  motors.setSpeeds(0, 0); //initial state
}

void start(){
  proxSense.read(); //reading in values from the proximity sensors
  
  int left_sensor = proxSense.countsLeftWithLeftLeds();
  int center_left = proxSense.countsFrontWithLeftLeds();
  int center_right = proxSense.countsFrontWithRightLeds();
  int right_sensor = proxSense.countsRightWithRightLeds();

  display.gotoXY(0, 0);
  display.print(left_sensor); //displaying value of left sensor
  display.gotoXY(2, 0);
  display.print(center_left); //displaying value of center_left
  display.gotoXY(6, 0);
  display.print(right_sensor); //displaying value of right sensor
  display.gotoXY(4, 0);
  display.print(center_right); //displaying value of center_right

  if(left_sensor >= 2 && left_sensor > right_sensor){
    motors.setSpeeds(-400, 400); //checking if object is on left side of bot, if it is, it will turn left
  }
  else if(right_sensor >= 2 && left_sensor < right_sensor){
    motors.setSpeeds(400, -400); //chekcing if object is on right side of bot, if it is, it will turn right
  }
  else{
    if(center_left >= 2 && center_right >= 2){
      motors.setSpeeds(400, 400); //checking if object is in front of it, if it is, it will try to push it out of the ring
    }
    else motors.setSpeeds(0, 0); //else, it won't move
  }
  delay(100); //delay for testing
}

void loop() {
  if(fiveCheck == false && buttC.isPressed()){ //conditional if it goes past 5 seconds
    stop();
    delay(5000);
    fiveCheck = true;
  }
 else if(fiveCheck == true){
    start();
 }
}
