#include <Servo.h>
#include <stdio.h>
#include "../motioncalc/Vector3D.h"
#include "../motioncalc/MotionPerform.h"

void setup();
void loop();
void printAngles(double angles[4]);
void writeAngles(double angles[4]);


Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
MotionPerform motion (&writeAngles, &delay);

Vector3D p1 (6, 0, -8);
Vector3D p2 (8, 0, 2.5);
Vector3D p3 (8, 0, 2);
Vector3D p4 (6, 0, 8);


void setup() {
  Serial.begin(9600);
  servo1.attach(8);
  servo2.attach(9);
  servo3.attach(10);
  servo4.attach(11);
	motion 
  Vector3D p (5, 5, 5);
  Calculation::calcAngles(&p, lastAngles);
  writeAngles(lastAngles);
  printAngles(lastAngles);
}

void loop() {    
    if(Serial.available()){
      if(Serial.read() == 'j')
        drawLine(p1, p4);
    }
}

void printAngles(double angles[4]){
  Serial.println(angles[0] /3.14 * 180);
  Serial.println(angles[1] /3.14 * 180);
  Serial.println(angles[2] /3.14 * 180);
  Serial.println(angles[3] /3.14 * 180);
  Serial.println("");
}

void writeAngles(double angles[4]){
    servo1.write(90 + (int)(angles[0] / 3.14 * 180));
    servo2.write(99 - (int)(angles[1] / 3.14 * 180));
    servo3.write(-(int)(angles[2] / 3.14 * 180));
    servo4.write(80 - (int)(angles[3] / 3.14 * 180));
}

