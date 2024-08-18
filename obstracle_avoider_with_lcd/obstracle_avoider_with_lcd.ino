#include<Servo.h>
#include<AFMotor.h>
#include <LiquidCrystal_I2C.h>
int trig=A0;
int echo=A1;
long duration;
float distance;
int d;
int Ldis;
int Rdis;
int left;
int right;
Servo s;
AF_DCMotor m1(1);
AF_DCMotor m2(2);
AF_DCMotor m3(3);
AF_DCMotor m4(4);
LiquidCrystal_I2C lcd(0x3F,16,2); 
void setup() 
{
lcd.init();                      
lcd.backlight();
pinMode(echo,INPUT);
pinMode(trig,OUTPUT);
m1.setSpeed(255);
m2.setSpeed(255);
m3.setSpeed(255);
m4.setSpeed(255);
s.attach(10);
 start();
lcd.clear();
}

void forward()
{
lcd.setCursor(2,0);
lcd.print("I am moving");
lcd.setCursor(3,1);
lcd.print("Forward...");
m1.run(FORWARD);
m2.run(FORWARD);
m3.run(FORWARD);
m4.run(FORWARD);
}
void backward()
{
m1.run(BACKWARD);
m2.run(BACKWARD);
m3.run(BACKWARD);
m4.run(BACKWARD);    
}
void moveleft()
{
m1.run(BACKWARD);
m2.run(BACKWARD);
m3.run(FORWARD);
m4.run(FORWARD); 
}
void moveright(){
m1.run(FORWARD);
m2.run(FORWARD);
m3.run(BACKWARD);
m4.run(BACKWARD);

}
int ultrasonic(){
  digitalWrite(trig,LOW);
  delay(2);
  digitalWrite(trig,HIGH);
  delay(10);
  digitalWrite(trig,LOW);
  duration=pulseIn(echo,HIGH);
  distance=(duration/2)/29.1;
  return distance;
}
int seeleft(){
  s.write(180);
  delay(500);
  left=ultrasonic();
  return left;
}
int seeright(){
  s.write(0);
  delay(500);
  right=ultrasonic();
  return right;
}
void Stop(){
m1.run(RELEASE);
m2.run(RELEASE);
m3.run(RELEASE);
m4.run(RELEASE);
}
void start()
{
lcd.setCursor(0,0);
lcd.print("I am Activated..");
delay(5000);
s.write(90);
delay(500);
}
void distleft()
{      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("I am turning");
       lcd.setCursor(0,1);
      lcd.print("Right...");
      delay(1000);
}
void distright()
{      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("I am turning");
       lcd.setCursor(0,1);
      lcd.print("left...");
      delay(1000);
      
}

void loop() 
{
  d = ultrasonic();

  if (d <= 30) 
  {
    Stop();
     lcd.clear();
     lcd.setCursor(2,0);
     lcd.print("I am moving");
     lcd.setCursor(3,1);
    lcd.print("Backward...");  
    backward();
    delay(300);
    Stop();
    Ldis = seeleft();
     lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Left Distance                           is:");
    lcd.setCursor(6,1);
    lcd.print(Ldis);
    delay(1000);
    s.write(90);
    Rdis = seeright();
     lcd.clear();
     lcd.setCursor(0,0);
      lcd.print("Right Distance                          is:");
      lcd.setCursor(6,1);
      lcd.print(Rdis);
      delay(1000);
    s.write(90);
    if (Ldis < Rdis)
    {
       lcd.clear();
      distleft();
      moveleft();
      delay(250);
      Stop();
      delay(500);
    }
     else if (Ldis > Rdis)
     {
       lcd.clear();
      distright();
      moveright();
      delay(250);
      Stop();
      delay(1000);
    }
     lcd.clear();
  } 
  else 
  {
 // lcd.clear();
    
  forward();
     

  }
}
