#include <Zumo32U4.h>

Zumo32U4ButtonA buttA;
Zumo32U4ButtonB buttB;
Zumo32U4ButtonC buttC;
Zumo32U4IRPulses Ir;
Zumo32U4LineSensors sensors;
Zumo32U4Motors motors;
Zumo32U4OLED display;
Zumo32U4ProximitySensors proxSense;

#define PROX_SENSOR_THRESHOLD 1     //Integer threshold for proximity sensors
#define LINE_SENSOR_THRESHOLD 100  // Threshold for Line sensors
#define DRIVE_SPEED 400             //Speed at which the bot drives (in magic bot units)
#define FIVE_SECONDS 5000           //milliseconds

#define LEFT_LS 0
#define CENTER_LS 1
#define RIGHT_LS 2

//Will hold the value for each sensor
int left_sensor = 0;
int right_sensor = 0;

int sensorVals[3];

void setup() {
  //Initialize the sensors
  proxSense.initThreeSensors(); 
  sensors.initThreeSensors();

  //Display info to screen and wait 5 seconds after button C is pressed
  display.clear();
  display.print("Press C");
  buttC.waitForButton(); //Wait until button C is pressed
  display.gotoXY(0,0);
  display.print("Waiting...");
  delay(FIVE_SECONDS);
  display.clear();


  //turn left
  motors.setSpeeds(-DRIVE_SPEED, DRIVE_SPEED);
  delay(150);

  //get left prox val
  proxSense.read(); //reading in values from the proximity sensors
  left_sensor = proxSense.countsLeftWithLeftLeds();

  //If we detect something to the left, turn left
  if(left_sensor >= 0 && left_sensor > right_sensor){
    motors.setSpeeds(-DRIVE_SPEED, DRIVE_SPEED); //checking if object is on left side of bot, if it is, it will turn left
  }
  //otherwise, turn right
  else
  {
    motors.setSpeeds(DRIVE_SPEED, -DRIVE_SPEED);
    delay(400);
  }
}

void stop(){
  motors.setSpeeds(0, 0); //initial state
}

void start(){

  proxSense.read(); //reading in values from the proximity sensors
  
  left_sensor = proxSense.countsLeftWithLeftLeds();
  // center_left = proxSense.countsFrontWithLeftLeds();
  // center_right = proxSense.countsFrontWithRightLeds();
  right_sensor = proxSense.countsRightWithRightLeds();

  //Check if we hit a line
  sensors.read(sensorVals); // Read in line sensor values
  if(sensorVals[LEFT_LS] <= LINE_SENSOR_THRESHOLD || sensorVals[RIGHT_LS] <= LINE_SENSOR_THRESHOLD || sensorVals[CENTER_LS] <= LINE_SENSOR_THRESHOLD) 
  {
    turnAroundAtBorder();
  }

  //LEFT CHECK
  if(left_sensor >= PROX_SENSOR_THRESHOLD && left_sensor > right_sensor){
    motors.setSpeeds(-DRIVE_SPEED, DRIVE_SPEED); //checking if object is on left side of bot, if it is, it will turn left
  }

  //RIGHT CHECK
  else if(right_sensor >= PROX_SENSOR_THRESHOLD && left_sensor < right_sensor){
    motors.setSpeeds(DRIVE_SPEED, -DRIVE_SPEED); //chekcing if object is on right side of bot, if it is, it will turn right
  }

  //Otherwise just go straight
  else{
    motors.setSpeeds(DRIVE_SPEED, DRIVE_SPEED);
  }

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
  start();
}
