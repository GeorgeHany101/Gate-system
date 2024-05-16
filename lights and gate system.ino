#include <Servo.h>

//define the LED pins
const int LedPin[]={2,3,4,5,6,7};

//define the ultrasonic sensor pins
const int TrigPin = 8;
const int EchoPin = 9;

//define servo pin
const int ServoPin = 10;
//create a servo object (name the servo)
Servo myServo;

void setup() {
  //initialize serial communication
  Serial.begin(9600);

  //initialize ultrasonic sensor pins (pin number,input or output)
  pinMode (TrigPin,OUTPUT);
  pinMode (EchoPin,INPUT);

  //initialize LED pins (pin number, input or output)
  for (int i=0;i<6;i++){
    pinMode (LedPin[i],OUTPUT);
  }
  
  //initialize servo pin (pin number)
  myServo.attach(ServoPin);
}

void loop() {
  //measure distance using the ultrasonic sensor
  long duration, distance;
  digitalWrite(TrigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin,LOW);
  duration = pulseIn(EchoPin,HIGH);
  distance = (duration*0.034)/2;

  //control LEDs & servo motor based on the distance from the sensor
  if (distance>0 && distance < 50){
    myServo.write(90);

    for (int i=0;i<6;i++){
      digitalWrite(LedPin[i],HIGH);
      delay (250);
    }
    delay (3000);
  }
  //turn off LEDs and lower the servo arm
  else {
    myServo.write(0);

    for (int i=0;i<6;i++){
      digitalWrite(LedPin[i],LOW);
      delay (250);
    }
  }
  //display the distance on the serial monitor 
  Serial.print("distance: ");
  Serial.println(distance);
}