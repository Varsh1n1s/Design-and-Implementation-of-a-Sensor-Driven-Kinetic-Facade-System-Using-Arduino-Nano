#include <Servo.h>
Servo servo1;
Servo servo2;
const int servoPin1 = 9;
const int servoPin2 = 10;

#define LDRpin A0
int LDRValue;

#define RainPin 3
int rainValue;

bool servosOpen = false;
bool servosClosed = false;

int servo_motor_open(int x);
int servo_motor_close(int x);

void setup() {
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  pinMode(LDRpin, INPUT);
  pinMode(RainPin, INPUT);
  Serial.begin(9600);

  servosClosed = true;
  servosOpen = false; // Ensure this is false initially
}


void loop(){
  LDRValue = analogRead(LDRpin);
  Serial.println(LDRValue);
  rainValue = digitalRead(RainPin);

  if(rainValue == 0){
    if(!servosClosed){
      servo_motor_close(90);
      servosClosed = true;
      servosOpen = false;
    }
  }
  else{
    if(LDRValue <= 700){
      if(!servosOpen){
        servo_motor_open(0);
        servosOpen = true;
        servosClosed = false;
      }
    }
    else{
      if(!servosClosed){
        servo_motor_close(90);
        servosClosed = true;
        servosOpen = false;
      }
    }
  }
  delay(50);
}

int servo_motor_open(int x){
  for(x=0;x<=90;x++){
    servo1.write(x);
    servo2.write(x);
    delay(50);
  }
}

int servo_motor_close(int x){
  for(x=90;x>=0;x--){
    servo1.write(x);
    servo2.write(x);
    delay(50);
  }
}
