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
    Stop();
    delay(100);
    L = leftsee();
    servo.write(spoint);
    R = rightsee();
    servo.write(spoint);
    delay(500);
    if (L < R)
    {
      right();
      delay(500);// 700 delay is the exactly 90 degree turn
      Stop();
      delay(100);
    }
    else if (L > R)
    {
      left();
      delay(500);
      Stop();
      delay(100);
    }
    else
    {
      left();
      delay(100);
      Stop();
      delay(100);
    }
  }
  else
  {
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
