#include "MyCube.h"
#include <GL\glut.h>

MyCube::MyCube(){
	this->centerPoint = MyPoint(0,0,0);
	sideLength = 0;
}

void MyCube::drawCube(){
	float x = centerPoint.getX();
	float y = centerPoint.getY();
	float z = centerPoint.getZ();
	float t = sideLength/2;
	
	glBegin(GL_LINE_LOOP);
	glVertex3f(x - t, y - t, z - t);
	glVertex3f(x + t, y - t, z - t);
	glVertex3f(x + t, y + t, z - t);
	glVertex3f(x - t, y + t, z - t);
	glEnd();
	
	glBegin(GL_LINE_LOOP);
	glVertex3f(x - t, y - t, z + t);
	glVertex3f(x + t, y - t, z + t);
	glVertex3f(x + t, y + t, z + t);
	glVertex3f(x - t, y + t, z + t);
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3f(x - t, y - t, z - t);
	glVertex3f(x - t, y - t, z + t);
	
	glVertex3f(x + t, y - t, z - t);
	glVertex3f(x + t, y - t, z + t);
	
	glVertex3f(x + t, y + t, z - t);
	glVertex3f(x + t, y + t, z + t);
	
	glVertex3f(x - t, y + t, z - t);
	glVertex3f(x - t, y + t, z + t);
	glEnd();
}

void MyCube::ZoomIn(){
	if (sideLength <= 0.25){
		return;
	}
	sideLength -= 0.25;
}

void MyCube::ZoomOut(){
	sideLength += 0.25;
}
