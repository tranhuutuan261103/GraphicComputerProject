#include "MyModelGL.h"
#include <GL\glut.h>
#include <iostream>
#include <math.h>
#include "MyRotation.h"
#include "Matrix.h"

using namespace std;

MyModelGL::MyModelGL(){
	this->cameraPoint = MyPoint(3,3,5);
	this->targetPoint = MyPoint(0,0,0);
	this->model.IdentityMatrix();
	v = 0.25;
}

void MyModelGL::LoadModelGL(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.5,1.5,-1.5,1.5,1.5,30);
	//gluLookAt(cameraPoint.getX(),cameraPoint.getY(),cameraPoint.getZ(),targetPoint.getX(),targetPoint.getY(),targetPoint.getZ(),0,1,0);
	this->model = CameraLookAt();
}

Matrix MyModelGL::CameraLookAt(){
	MyPoint up = MyPoint(0,1,0);
	
	MyPoint f = MyPoint();
	f = cameraPoint - targetPoint;
	f = f.Normalize();
	MyPoint r = up * f;
	r = r.Normalize();
	MyPoint u = f * r;
	u = u.Normalize();
	
	Matrix m = Matrix(4);
	for (int i=0;i<3;i++)
	{
		m(0,i) = r(i);
		m(1,i) = u(i);
		m(2,i) = f(i);
		m(3,i) = 0;
		m(i,3) = 0;
	}
	m(3,3)=1;
	
	m = m.Transpose();
	
	double m2[4][4];
	
	for (int i = 0 ;i <4 ;i++){
		for (int j = 0;j<4 ;j++){
			m2[i][j] = m(i,j);
		}
	}
	glMultMatrixd(&m2[0][0]);
	glTranslated(-cameraPoint.getX(),-cameraPoint.getY(),-cameraPoint.getZ());
	
	double temp[4][4];
	glGetDoublev(GL_PROJECTION_MATRIX,&temp[0][0]);
	
	
	for(int i = 0;i<4;i++){
		for(int j = 0;j<4;j++){
			model(i,j) = temp[i][j];
		}
	}
	
	return model;
}

float MyModelGL::Mul2Vector(MyPoint go){
	float xa = targetPoint.getX() - cameraPoint.getX();
	float ya = targetPoint.getY() - cameraPoint.getY();
	float za = targetPoint.getZ() - cameraPoint.getZ();
	MyPoint a = MyPoint(xa, ya, za);
	
	return a.Mul2Vector(a, go);
}

void MyModelGL::CameraMove(MyPoint go){
	cameraPoint.addXYZ(go);
	targetPoint.addXYZ(go);
}

void MyModelGL::CameraMoveUp(){
	MyPoint go = MyPoint(0, v, 0);
	CameraMove(go);
}

void MyModelGL::CameraMoveDown(){
	MyPoint go = MyPoint(0, -v, 0);
	CameraMove(go);
}

void MyModelGL::CameraMoveForward(){
	float x = targetPoint.getX() - cameraPoint.getX();
	float y = targetPoint.getY() - cameraPoint.getY();
	float z = targetPoint.getZ() - cameraPoint.getZ();
	MyPoint p = MyPoint(x,y,z);
	
	MyPoint go = MyPoint(x * 0.25 / p.Dimention(), y * 0.25 / p.Dimention(), z * 0.25 / p.Dimention());
	CameraMove(go);
}

void MyModelGL::CameraMoveBackward(){
	float x = targetPoint.getX() - cameraPoint.getX();
	float y = targetPoint.getY() - cameraPoint.getY();
	float z = targetPoint.getZ() - cameraPoint.getZ();
	MyPoint p = MyPoint(x,y,z);
	
	MyPoint go = MyPoint(-x * 0.25 / p.Dimention(), -y * 0.25 / p.Dimention(), -z * 0.25 / p.Dimention());
	CameraMove(go);
}

void MyModelGL::CameraMoveLeft(){
	float x = targetPoint.getX() - cameraPoint.getX();
	float y = targetPoint.getY() - cameraPoint.getY();
	float z = targetPoint.getZ() - cameraPoint.getZ();
	MyPoint p = MyPoint(x,y,z);
	MyPoint l = MyPoint(x,0,z);
	MyPoint go = go.LinearAlgebra(l, p);
	go.setX(go.getX() * 0.25 / go.Dimention());
	go.setY(go.getY() * 0.25 / go.Dimention());
	go.setZ(go.getZ() * 0.25 / go.Dimention());
	
	CameraMove(go);
}

void MyModelGL::CameraMoveRight(){
	float x = targetPoint.getX() - cameraPoint.getX();
	float y = targetPoint.getY() - cameraPoint.getY();
	float z = targetPoint.getZ() - cameraPoint.getZ();
	MyPoint p = MyPoint(x,y,z);
	MyPoint l = MyPoint(x,0,z);
	MyPoint go = go.LinearAlgebra(p, l);
	go.setX(go.getX() * 0.25 / go.Dimention());
	go.setY(go.getY() * 0.25 / go.Dimention());
	go.setZ(go.getZ() * 0.25 / go.Dimention());
	
	CameraMove(go);
}

void MyModelGL::TargetMoveLeft(){
	float x = targetPoint.getX() - cameraPoint.getX();
	float y = targetPoint.getY() - cameraPoint.getY();
	float z = targetPoint.getZ() - cameraPoint.getZ();
	
	float xnew = x*cos(3.14/45) + z * sin(3.14/45);
	float ynew = y;
	float znew = -x*sin(3.14/45) + z * cos(3.14/45);
	
	targetPoint.setX(xnew + cameraPoint.getX());
	targetPoint.setY(ynew + cameraPoint.getY());
	targetPoint.setZ(znew + cameraPoint.getZ());
}

void MyModelGL::TargetMoveRight(){
	float x = targetPoint.getX() - cameraPoint.getX();
	float y = targetPoint.getY() - cameraPoint.getY();
	float z = targetPoint.getZ() - cameraPoint.getZ();
	
	float xnew = x*cos(-3.14/45) + z * sin(-3.14/45);
	float ynew = y;
	float znew = -x*sin(-3.14/45) + z * cos(-3.14/45);
	
	targetPoint.setX(xnew + cameraPoint.getX());
	targetPoint.setY(ynew + cameraPoint.getY());
	targetPoint.setZ(znew + cameraPoint.getZ());
}

void MyModelGL::TargetMoveUp(){
	targetPoint.setY(targetPoint.getY() + v);
}

void MyModelGL::TargetMoveDown(){
	targetPoint.setY(targetPoint.getY() - v);
}

void MyModelGL::printfModelMatrix(){
	cout << "\n\nMa tran bien doi la:\n";
	this->model.printfMatrix();
	cout << endl;
}
