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

bool fiveCheck = false;

void setup() {
  // put your setup code here, to run once:
  LCD.init();
  LCD.clear();
  LCD.gotoXY(0,0);
  LCD.print("Hello");
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

  if(left_sensor == 0 && center_left == 0 && center_right == 0 && right_sensor == 0){
    motors.setSpeeds(400, -400);
  }
  else{
    if(left_sensor > right_sensor){
      motors.setSpeeds(400, -400);
    }
    if(right_sensor > left_sensor){
      motors.setSpeeds(-400, 400);
    }
    else{
      motors.setSpeeds(400, 400);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  LCD.blink();
  if(fiveCheck == false && buttC.isPressed()){
    stop();
    delay(5000);
    fiveCheck = true;
  }
  else if(fiveCheck == true){
    start();
  }
}
