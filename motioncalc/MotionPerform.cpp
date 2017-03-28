#include "MotionPerform.h"
#include "Calculation.h"
#include "Vector3D.h"

MotionPerform::MotionPerform(void (*writeAngles)(double [4]), void (*waitForMotion)(int)){
	this->writeAngles = writeAngles;
	this->waitForMotion = waitForMotion;
	this->lastAngles[0] = 0;
	this->lastAngles[1] = 0;
	this->lastAngles[2] = 0;
	this->lastAngles[3] = 0;
}

MotionPerform::MotionPerform(void (*writeAngles)(double [4]), void (*waitForMotion)(int), double lastAngles[4]){	
	this->writeAngles = writeAngles;
	this->waitForMotion = waitForMotion;
	this->lastAngles[0] = lastAngles[0];
	this->lastAngles[1] = lastAngles[1];
	this->lastAngles[2] = lastAngles[2];
	this->lastAngles[3] = lastAngles[3];
}


void MotionPerform::calcAndGo(const Vector3D& point, int count){
  double to[4];
  Calculation::calcAngles(point, to);
  this->goTo(to, count);
}

void MotionPerform::goTo(double to[4], int count){
  for(int i = 1; i <= count; ++i){
    double ratio = (double) i / count;
		double angles[4];
		angles[0] = this->lastAngles[0] - ratio * (this->lastAngles[0] - to[0]);
		angles[1] = this->lastAngles[1] - ratio *(this->lastAngles[1] - to[1]);
		angles[2] = this->lastAngles[2] - ratio *(this->lastAngles[2] - to[2]);
		angles[3] = this->lastAngles[3] - ratio *(this->lastAngles[3] - to[3]);
		this->writeAngles(angles);
    this->waitForMotion(20);
  }
  this->lastAngles[0] = to[0];
  this->lastAngles[1] = to[1];
  this->lastAngles[2] = to[2];
  this->lastAngles[3] = to[3];
	
}

void MotionPerform::drawLine(const Vector3D& start, const Vector3D& fin){
  double to[4];
	Vector3D pointer = start;
	pointer.y += 3;
  this->calcAndGo(pointer);
  this->waitForMotion(2000);
  pointer.y -= 3;
  this->calcAndGo(pointer, 20);
  this->waitForMotion(2000);
  
  Vector3D d = fin - pointer;
  while(d.getLength() > 0.2){
     // go 2mm
     pointer = pointer + (0.2 / d.getLength()) * d;
     this->calcAndGo(pointer, 5);
     d = fin - pointer;
     this->waitForMotion(20);
  }
  this->calcAndGo(fin, 10);
  this->waitForMotion(500);
}

void MotionPerform::drawPoint(const Vector3D& point){
  double to[4];
	Vector3D pointer = point;
  pointer.y += 0.5;
	this->calcAndGo(pointer);
  this->waitForMotion(500);
  pointer.y -= 0.5;
  this->calcAndGo(pointer, 20);
  this->waitForMotion(500);
  pointer.y += 1;
  this->calcAndGo(pointer, 20);
  this->waitForMotion(500);
}
