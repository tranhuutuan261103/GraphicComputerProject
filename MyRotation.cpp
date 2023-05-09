#include "MyRotation.h"
#include "Matrix.h"
#include <math.h>


Matrix MyRotaion::RotateOx(float degree){
	degree = degree * 3.14/180;
	Matrix m = Matrix(4);
	m.IdentityMatrix();
	m(1,1) = cos(degree);
	m(1,2) = -sin(degree);
	m(2,1) = sin(degree);
	m(2,2) = cos(degree);
	return m;
}

Matrix MyRotaion::RotateOy(float degree){
	degree = degree * 3.14/180;
	Matrix m = Matrix(4);
	m.IdentityMatrix();
	m(0,0) = cos(degree);
	m(2,0) = -sin(degree);
	m(0,2) = sin(degree);
	m(2,2) = cos(degree);
	return m;
}

Matrix MyRotaion::RotateOz(float degree){
	degree = degree * 3.14/180;
	Matrix m = Matrix(4);
	m.IdentityMatrix();
	m(0,0) = cos(degree);
	m(0,1) = -sin(degree);
	m(1,0) = sin(degree);
	m(1,1) = cos(degree);
	return m;
}

Matrix MyRotaion::Translate(MyPoint p){
	Matrix m = Matrix(4);
	m.IdentityMatrix();
	m(0,3) = p.getX();
	m(1,3) = p.getY();
	m(2,3) = p.getZ();
	return m;
}

// error
Matrix MyRotaion::Rotate(MyPoint P, MyPoint vertorRotate, float degree){
	
	float ThetaX = atan(vertorRotate.getY() / vertorRotate.getZ()) * 180/3.14;
	float ThetaY = asin(-vertorRotate.getX()/vertorRotate.Dimention()) * 180/3.14;
	
	Matrix m = Matrix(4);
	m.IdentityMatrix();
	
	MyPoint P2 = MyPoint(P.getX(), P.getY(), P.getZ());
	
	m = Translate(P.Symmetry()) * m;
	m = RotateOx(ThetaX) * m;
	m = RotateOy(ThetaY) * m;
	m = RotateOz(degree) * m;
	m = RotateOy(-ThetaY) * m;
	m = RotateOx(-ThetaX) * m;
	m = Translate(P2) * m;
	
	return m; 
}
