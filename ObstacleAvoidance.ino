#include <Servo.h>
#include <AFMotor.h>

#define Echo A0
#define Trig A1
#define motor 10
#define Speed 150
#define spoint 90

char value;
int distance;
int Left;
int Right;
int L = 0;
int R = 0;
int L1 = 0;
int R1 = 0;

Servo servo;
AF_DCMotor M1(1);
AF_DCMotor M2(2);
AF_DCMotor M3(3);
AF_DCMotor M4(4);

void setup() {
  Serial.begin(9600);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  servo.attach(motor);
  M1.setSpeed(Speed);
  M2.setSpeed(Speed);
  M3.setSpeed(Speed);
  M4.setSpeed(Speed);
}
void loop()
{
  Obstacle();
}

void Obstacle()
{
  distance = ultrasonic();
  if( distance <= 30)
  {
    Serial.println(distance);
    delay(2000);
    Stop();
    delay(100);
    Serial.println("Moving backward");
    delay(100);
    backward();
    Serial.println("Moved backward");
    delay(100);
    Stop();
    Serial.println("Moving LeftSide");
    delay(100);
    L = leftsee();
    delay(500);
    Serial.println("Moved to left side");
    delay(2500);
    Serial.println("Object distance on left side is");
    Serial.println(L);
    delay(2500);
    Serial.println("Moving to  servo position");
    delay(2500);
    servo.write(spoint);
    delay(500);
    Serial.println("Moving Right Side");
    delay(2500);
    R = rightsee();
    delay(500);
    Serial.println("Moved to right side");
    delay(2500);
    Serial.println("Object distance on right side is:");
    Serial.print(R);
    delay(2500);
    Serial.println("Moving to  servo position");
    delay(2500);
    servo.write(spoint);
    delay(500);
    if (L < R)
    {
      Serial.println("Right side object distance is more so moving to right side");
      delay(500);
      right();
      delay(1500);// 700 delay is the exactly 90 degree turn
      Stop();
      Serial.println("Moved to right side");
      delay(1000);
    }
    else if (L > R)
    {
      Serial.println("Left side object distance is more so moving to left side");
      delay(500);
      left();
      delay(1500);
      Stop();
      Serial.println("Moved to left side");
      delay(1000);
    }
    else
    {
      Serial.println("Both on left side and right side object distance is same so moving to left side");
      delay(500);
      left();
      delay(1000);
      Stop();
      Serial.println("Moved to left side");
      delay(1000);
    }
  }
  else
  {
    Serial.println("No object is found moving forward");
    forward();
  }

}
int ultrasonic() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(4);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  long t = pulseIn(Echo, HIGH);
  long cm = t / 29 / 2; 
  return cm;
}

void forward() {
  M1.run(FORWARD);
  M2.run(FORWARD);
  M3.run(FORWARD);
  M4.run(FORWARD);
}
void backward() {
  M1.run(BACKWARD);
  M2.run(BACKWARD);
  M3.run(BACKWARD);
  M4.run(BACKWARD);
}
void right() {
  M1.run(BACKWARD);
  M2.run(BACKWARD);
  M3.run(FORWARD);
  M4.run(FORWARD);
}
void left() {
  M1.run(FORWARD);
  M2.run(FORWARD);
  M3.run(BACKWARD);
  M4.run(BACKWARD);
}
void Stop() {
  M1.run(RELEASE);
  M2.run(RELEASE);
  M3.run(RELEASE);
  M4.run(RELEASE);
}
int rightsee() {
  servo.write(1);
  delay(800);
  Left = ultrasonic();
  return Left;
}

int leftsee() {
  servo.write(180);
  delay(800);
  Right = ultrasonic();
  return Right;
}
