#include <Servo.h>
#include <NewPing.h>
#include <Wire.h>


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

Servo servo;
NewPing frontSensor(sigFrontTrigg, sigFrontEcho, MAX_DISTANCE);
NewPing leftSensor(sigLeftTrigg, sigLeftEcho, MAX_DISTANCE);
NewPing rightSensor(sigRightTrigg, sigRightEcho, MAX_DISTANCE);

void setup(){
  Serial.begin(9600);
  //Servo configuration
  servo.attach(servoPin);
  servo.write(60);

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
  Wire.onRequest(requestEvents);
  Wire.onReceive(receiveEvents);
}

int n = 0;

void requestEvents()
{
  Serial.println(F("---> recieved request"));
  Serial.print(F("sending value : "));
  Serial.println(n);
  Wire.write(n);
}

void receiveEvents(int numBytes)
{  
  Serial.println(F("---> recieved events"));
  Serial.print(numBytes);
  Serial.println(F("bytes recieved"));
  Serial.print(F("recieved value : "));
  Wire.requestFrom(I2C_SLAVE_ADDRESS, 1);    // request 6 bytes from peripheral device #8
  Serial.print("Wire available");
  while (Wire.available()) { // peripheral may send less than requested
    Serial.print("Wire available in");
    char c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
  }
}

void reward(){
  servo.write(-30);
  delay(1500);
  servo.write(60);
  delay(1500);
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

bool catDetected = true;

void loop(){
  delay(100);
  double leftDist = leftSensor.ping_median() / US_ROUNDTRIP_CM;
  double frontDist = frontSensor.ping_median() / US_ROUNDTRIP_CM;
  double rightDist = rightSensor.ping_median() / US_ROUNDTRIP_CM;
  
  //Serial.print("Left distance=");
  //Serial.println(leftDist);
  //Serial.print("Right distance=");
  //Serial.println(rightDist);
  //Serial.print("Front distance=");
  //Serial.println(frontDist);

  if (catDetected){
    if (leftDist > rightDist){
      //turnLeft();
      //turnLeft();
    }else{
      //turnRight();
      //turnRight();
    } 
    catDetected = false;
  }
  
  if (frontDist > 0){
    if (frontDist < 30){
      if(frontDist > 20 || leftDist > 20 || rightDist > 20){
        //goBack();
      }else{
        //if (leftDist > rightDist) turnLeft();
        //else turnRight();
      }
    }else{
      //goFront();
    }
  }else{
    //goFront();
  }
}