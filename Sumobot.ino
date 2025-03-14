#include <Zumo32U4.h>

Zumo32U4ButtonA buttA;
Zumo32U4ButtonB buttB;
Zumo32U4ButtonC buttC;
//Zumo32U4Encoders encode;
Zumo32U4IMU IMU;
Zumo32U4IRPulses Ir;
//Zumo32U4LineSensors sensors;
Zumo32U4Motors motors;
//Zumo32U4OLED LED;
Zumo32U4LCD LCD;
Zumo32U4ProximitySensors proxSense;

bool isA, isB, isC;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  proxSense.initThreeSensors();
}

void stop(){
  motors.setSpeeds(0, 0);
}

void start(){
  proxSense.read();

  uint8_t leftValue = proxSense.countsFrontWithLeftLeds();
  uint8_t rightValue = proxSense.countsFrontWithRightLeds();
  
  int left_sensor = proxSense.countsLeftWithLeftLeds();
  int center_left = proxSense.countsFrontWithLeftLeds();
  int center_right = proxSense.countsFrontWithRightLeds();
  int right_sensor = proxSense.countsRightWithRightLeds();

  Serial.print(left_sensor);
  Serial.print(" ");
  Serial.print(center_left);
  Serial.print(" ");
  Serial.print(center_right);
  Serial.print(" ");
  Serial.println(right_sensor);

  if(left_sensor > right_sensor){
    motors.setRightSpeed(400);
    motors.setLeftSpeed(-200);
  }
  if(right_sensor > left_sensor){
    motors.setLeftSpeed(400);
    motors.setRightSpeed(-200);
  }
}

void rightSpeed(){
  
}

void leftSpeed(){

}

void loop() {
  // put your main code here, to run repeatedly:
  // ledRed(0);
  // delay(500);
  // ledRed(1);
  // delay(500);
  //motors.setSpeeds(300, 300);
  if(buttA.isPressed()){
    isA = true;
    isB = false;
    isC = false;
  }
  else if(buttB.isPressed()){
    isA = false;
    isB = true;
    isC = false;
  }
  else if(buttC.isPressed()){
    isA = false;
    isB = false;
    isC = true;
  }
  if(isA){
    stop();
  }
  else if(isB){
    start();
  }
}
