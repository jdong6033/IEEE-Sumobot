#include <Zumo32U4.h>

Zumo32U4ButtonA buttA;
Zumo32U4ButtonB buttB;
Zumo32U4ButtonC buttC;
Zumo32U4IRPulses Ir;
Zumo32U4LineSensors sensors;
Zumo32U4Motors motors;
Zumo32U4OLED display;
Zumo32U4ProximitySensors proxSense;

#define PROX_SENSOR_THRESHOLD 2     //Integer threshold for proximity sensors
#define LINE_SENSOR_THRESHOLD 100  // Threshold for Line sensors
#define DRIVE_SPEED 350             //Speed at which the bot drives (in magic bot units)
#define FIVE_SECONDS 5000           //milliseconds

#define LEFT_LS 0
#define CENTER_LS 1
#define RIGHT_LS 2

int sensorVals[3];

bool fiveCheck = false; //checking if five seconds have passed

void setup() {
  proxSense.initThreeSensors(); //initializing the sensors
  sensors.initThreeSensors(); //initialize line sensors
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

  sensors.read(sensorVals);

  // display.gotoXY(0, 0);
  // display.print(left_sensor); //displaying value of left sensor

  // display.gotoXY(2, 0);
  // display.print(center_left); //displaying value of center_left

  // display.gotoXY(6, 0);
  // display.print(right_sensor); //displaying value of right sensor

  // display.gotoXY(4, 0);
  // display.print(center_right); //displaying value of center_right

  if(sensorVals[LEFT_LS] <= LINE_SENSOR_THRESHOLD || sensorVals[RIGHT_LS] <= LINE_SENSOR_THRESHOLD || sensorVals[CENTER_LS] <= LINE_SENSOR_THRESHOLD) //
  {
    turnAroundAtBorder();
  }

  //FRONT CHECK
  if(center_left >= PROX_SENSOR_THRESHOLD || center_right >= PROX_SENSOR_THRESHOLD)
  {
      motors.setSpeeds(DRIVE_SPEED, DRIVE_SPEED); //checking if object is in front of it, if it is, it will try to push it out of the ring
  }

  //LEFT CHECK
  else if(left_sensor >= PROX_SENSOR_THRESHOLD && left_sensor > right_sensor){
    motors.setSpeeds(-DRIVE_SPEED, DRIVE_SPEED); //checking if object is on left side of bot, if it is, it will turn left
  }

  //RIGHT CHECK
  else if(right_sensor >= PROX_SENSOR_THRESHOLD && left_sensor < right_sensor){
    motors.setSpeeds(DRIVE_SPEED, -DRIVE_SPEED); //chekcing if object is on right side of bot, if it is, it will turn right
  }

  //If sense Notho
  // else if(center_left == 0 && center_right == 0)
  // {
  //   if (right_sensor == 0 && left_sensor == 0)
  //   {
  //     motors.setSpeeds(-DRIVE_SPEED, DRIVE_SPEED);
  //     delay(400);
  //   }
  // }
  else{
    motors.setSpeeds(DRIVE_SPEED, DRIVE_SPEED);
  }
  delay(50); //delay for testing
}

void turnAroundAtBorder()
{
  motors.setSpeeds(-DRIVE_SPEED, -DRIVE_SPEED);
  delay(200);
  motors.setSpeeds(-DRIVE_SPEED, DRIVE_SPEED);
  delay(400);
  motors.setSpeeds(0,0);
}

void loop() {
  
  if(fiveCheck == false && buttC.isPressed()){ //conditional if it goes past 5 seconds
    display.gotoXY(0,0);
    display.print("Waiting...");
    stop();
    delay(FIVE_SECONDS);
    display.clear();
    fiveCheck = true;

    proxSense.read(); //reading in values from the proximity sensors
  
    int left_sensor = proxSense.countsLeftWithLeftLeds();
    int right_sensor = proxSense.countsRightWithRightLeds();

    motors.setSpeeds(-DRIVE_SPEED, DRIVE_SPEED);
    delay(100);
    if(left_sensor >= PROX_SENSOR_THRESHOLD && left_sensor > right_sensor){
      motors.setSpeeds(-DRIVE_SPEED, DRIVE_SPEED); //checking if object is on left side of bot, if it is, it will turn left
    }
    else
    {
      motors.setSpeeds(DRIVE_SPEED, -DRIVE_SPEED);
    }
  }
  else if(fiveCheck == true){

    start();
  }
  else
  {
    display.gotoXY(0,0);
    display.print("Press C");
  }
}
