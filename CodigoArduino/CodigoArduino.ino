#include <Servo.h>
#include <NewPing.h>
#include <Wire.h>
#include <CapacitiveSensor.h>


#define in1 4
#define in2 2
#define in3 A0
#define in4 A1
#define enLeft 6
#define enRight 5
#define sigRightEcho 9
#define sigRightTrigg 8
#define sigFrontEcho 10
#define sigFrontTrigg 11
#define sigLeftEcho 13
#define sigLeftTrigg 12
#define servoPin 3
#define MAX_DISTANCE 100

#define I2C_SLAVE_ADDRESS 11
#define PAYLOAD_SIZE 2

#define TOUCHY_PIN A2
#define COTOUCHY_PIN A3
#define TOUCH_TOLERANCE 10000

Servo servo;
NewPing frontSensor(sigFrontTrigg, sigFrontEcho, MAX_DISTANCE);
NewPing leftSensor(sigLeftTrigg, sigLeftEcho, MAX_DISTANCE);
NewPing rightSensor(sigRightTrigg, sigRightEcho, MAX_DISTANCE);

CapacitiveSensor touchSensor = CapacitiveSensor(COTOUCHY_PIN, TOUCHY_PIN);

void setup(){
  Serial.begin(9600);
  //Servo configuration
  servo.attach(servoPin);
  servo.write(80);

  //Ultrasensors configuration
  //pinMode(sigRightTrigg, OUTPUT);
  //pinMode(sigRightEcho, INPUT);
  //pinMode(sigFrontTrigg, OUTPUT);
  //pinMode(sigFrontEcho, INPUT);
  //pinMode(sigLeftTrigg, OUTPUT);
  //pinMode(sigLeftEcho, INPUT);

  //Motors configuration
  pinMode(enLeft, OUTPUT);
  pinMode(enRight, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  Wire.begin(I2C_SLAVE_ADDRESS);
  Serial.println("-------------------------------------I am Slave1");
  delay(1000);               
  Wire.onReceive(receiveEvents);
}

bool catDetected = false;

void receiveEvents(int numBytes)
{  
  Serial.println("Gato detectado");
  catDetected = true;
}

void reward(){
  stop();
  servo.write(110);
  delay(1000);
  servo.write(80);
  delay(1000);
}

void goFront()
{
  digitalWrite(enLeft, HIGH);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(enRight, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void goBack()
{
  analogWrite (enLeft, 150);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enRight, 150);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(400);
  stop();
}

void turnLeft()
{
  analogWrite (enLeft, 150);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite (enRight, 150);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(400);
  stop();
}

void turnRight()
{
  analogWrite (enLeft, 150);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite (enRight, 150);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(400);
  stop();
}

void stop(){
  digitalWrite(enLeft, 0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(enRight, 0);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void loop(){
  delay(100);
  double leftDist = leftSensor.ping_median() / US_ROUNDTRIP_CM;
  double frontDist = frontSensor.ping_median() / US_ROUNDTRIP_CM;
  double rightDist = rightSensor.ping_median() / US_ROUNDTRIP_CM;

  long touchingValue = touchSensor.capacitiveSensor(30);
  //Serial.print("Value of touching = ");
  //Serial.println(touchingValue);

  if (touchingValue >= TOUCH_TOLERANCE) reward();  
  
  //Serial.print("Left distance=");
  //Serial.println(leftDist);
  //Serial.print("Right distance=");
  //Serial.println(rightDist);
  //Serial.print("Front distance=");
  //Serial.println(frontDist);

  if (catDetected){
    if (leftDist > rightDist){
      turnLeft();
      turnLeft();
    }else{
      turnRight();
      turnRight();
    } 
    catDetected = false;
  }
  
  if (frontDist > 0){
    if (frontDist < 30){
      if(frontDist > 20 || leftDist > 20 || rightDist > 20){
        goBack();
      }else{
        if (leftDist > rightDist) turnLeft();
        else turnRight();
      }
    }else{
      goFront();
    }
  }else{
    goFront();
  }
}
