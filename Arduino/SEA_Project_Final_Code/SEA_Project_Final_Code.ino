#include <Servo.h>

#define S0 13
#define S1 12
#define S2 11
#define S3 10
#define sensorOut 9

Servo gear_servo;
Servo flap_servo;
int gear_servo_pos = 0;
int flap_servo_pos = 0;

int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

void setup() {
  gear_servo.attach(7);
  flap_servo.attach(8);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  // Set Colour Sensor frequency to 2%
  digitalWrite(S0,LOW);
  digitalWrite(S1,HIGH);
  Serial.begin(9600);
}

void loop() {
  for (gear_servo_pos = 165; gear_servo_pos >= 90; gear_servo_pos -= 1) {
    gear_servo.write(gear_servo_pos);
    delay(10);
  }
  
  // Reading RED filtered photodiodes
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  redFrequency = pulseIn(sensorOut, LOW);
  delay(100);

  // Reading GREEN filtered photodiodes
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  greenFrequency = pulseIn(sensorOut, LOW);
  delay(100);

  // Reading BLUE (B) filtered photodiodes
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  blueFrequency = pulseIn(sensorOut, LOW);
  delay(100);

  // Print values for Debugging
  Serial.println("R       G       B");
  Serial.print(redFrequency);
  Serial.print(" ");
  Serial.print(greenFrequency);
  Serial.print(" ");
  Serial.println(blueFrequency);

  if (redFrequency < blueFrequency and flap_servo_pos != 111) {
    for (flap_servo_pos=60; flap_servo_pos <= 110; flap_servo_pos += 1) {
      flap_servo.write(flap_servo_pos);
      delay(10);
    }
  }
  
  else if (redFrequency > blueFrequency and flap_servo_pos != 59) {
    for (flap_servo_pos=110; flap_servo_pos >= 60; flap_servo_pos -= 1) {
      flap_servo.write(flap_servo_pos);
      delay(10);
    }
  }

  for (gear_servo_pos; gear_servo_pos >= 15; gear_servo_pos -= 1) {
    gear_servo.write(gear_servo_pos);
    delay(10);
  }

  for (gear_servo_pos; gear_servo_pos <= 165; gear_servo_pos += 1) {
    gear_servo.write(gear_servo_pos);
    delay(10);
  }
}
