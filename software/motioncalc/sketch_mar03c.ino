#include <Servo.h>
#include <stdio.h>
#include "Calculation.h"

void setup();
void loop();
void printAngles(double angles[4]);
void goTo(double to[4], int count = 100);
void calcAndGo(const Vector3D& p, int count = 100);
void drawLine(const Vector3D& start, const Vector3D& fin);
void drawPoint(const Vector3D& v);

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
double lastAngles[4];

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

void goTo(double to[4], int count){
	printAngles(to);
  for(int i = 0; i <= count; ++i){
    double ratio = (double) i / count;
		double angles[4];
		angles[0] = lastAngles[0] - ratio * (lastAngles[0] - to[0]);
		angles[1] = lastAngles[1] - ratio *(lastAngles[1] - to[1]);
		angles[2] = lastAngles[2] - ratio *(lastAngles[2] - to[2]);
		angles[3] = lastAngles[3] - ratio *(lastAngles[3] - to[3]);
		writeAngles(angles);
    delay(20);
  }
  lastAngles[0] = to[0];
  lastAngles[1] = to[1];
  lastAngles[2] = to[2];
  lastAngles[3] = to[3];
}

void calcAndGo(const Vector3D& p, int count){
  double to[4];
  Calculation::calcAngles(&p, to);
  goTo(to, count);
}

void drawLine(const Vector3D& start, const Vector3D& fin){
  double to[4];
	Vector3D pointer = start;
	pointer.y += 3;
  calcAndGo(pointer);
  delay(2000);
  pointer.y -= 3;
  calcAndGo(pointer, 20);
  delay(2000);
  
  Vector3D d = fin - pointer;
  while(d.getLength() > 0.2){
     // go 2mm
     pointer = pointer + (0.2 / d.getLength()) * d;
     calcAndGo(pointer, 5);
     d = fin - pointer;
     delay(20);
  }
  calcAndGo(fin, 10);
  delay(500);
}

void drawPoint(const Vector3D& p){
  double to[4];
  p.y += 0.5;
  Calculation::calcAngles(&p, to);
  goTo(to);
  delay(500);
  p.y -= 0.5;
  Calculation::calcAngles(&p, to);
  goTo(to, 20);
  delay(500);
  p.y += 1;
  Calculation::calcAngles(&p, to);
  goTo(to, 20);
  delay(500);
}

void writeAngles(double angles[4]){
    servo1.write(90 + (int)(angles[0] / 3.14 * 180));
    servo2.write(99 - (int)(angles[1] / 3.14 * 180));
    servo3.write(-(int)(angles[2] / 3.14 * 180));
    servo4.write(80 - (int)(angles[3] / 3.14 * 180));
}

