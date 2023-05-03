#include <Servo.h>

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
#define MAX_DISTANCE 336
#define MAX_SPEED 255

Servo servo;

long getDistance(int triggerPin, int echoPin)
{
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  double temp = pulseIn(echoPin, HIGH);
  return 0.01723 * temp;
}

void setup(){
  Serial.begin(9600);
  //Servo configuration
  servo.attach(servoPin);
  servo.write(100);

  //Ultrasensors configuration
  pinMode(sigRightTrigg, OUTPUT);
  pinMode(sigRightEcho, INPUT);
  pinMode(sigFrontTrigg, OUTPUT);
  pinMode(sigFrontEcho, INPUT);
  pinMode(sigLeftTrigg, OUTPUT);
  pinMode(sigLeftEcho, INPUT);

  //Motors configuration
  pinMode(enLeft, OUTPUT);
  pinMode(enRight, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void regulateSpeed()
{
  double leftDist = getDistance(sigLeftTrigg, sigLeftEcho);
  double frontDist = getDistance(sigFrontTrigg, sigFrontEcho);
  double rightDist = getDistance(sigRightTrigg, sigRightEcho);
  
//  Serial.print("Left distance=");
//  Serial.println(leftDist);
//  Serial.print("Right distance=");
//  Serial.println(rightDist);
//  Serial.print("Front distance=");
//  Serial.println(frontDist);
  
  double frontSpeed = frontDist/MAX_DISTANCE*MAX_SPEED;
  
  double rightSpeed = (rightDist/MAX_DISTANCE*MAX_SPEED)/2;
  
  double leftSpeed = (leftDist/MAX_DISTANCE*MAX_SPEED)/2;

  Serial.print("Left speed=");
  Serial.println(leftSpeed);
  Serial.print("Right speed=");
  Serial.println(rightSpeed);
  Serial.print("Front speed=");
  Serial.println(frontSpeed);
  
  leftSpeed = frontSpeed - rightSpeed;
  rightSpeed = frontSpeed - leftSpeed;

  Serial.print("Left speed corrected=");
  Serial.println(leftSpeed);
  Serial.print("Right speed corrected=");
  Serial.println(rightSpeed);
  
  analogWrite(enLeft, leftSpeed);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  
  analogWrite(enRight, rightSpeed);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}



void loop(){
  regulateSpeed();
  delay(1000);
}
