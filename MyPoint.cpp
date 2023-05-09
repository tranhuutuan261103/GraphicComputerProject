#include "MyPoint.h"
#include <math.h>

MyPoint::MyPoint(){
	x = y = z = 0;
}

MyPoint::MyPoint(float x, float y, float z){
	this->x = x;
	this->y = y;
	this->z = z;
}

const MyPoint MyPoint::Normalize(){
	MyPoint t = MyPoint();
	float d = this->Dimention();
	t.x = this->x / d;
	t.y = this->y / d;
	t.z = this->z / d;
	return t;
}

const MyPoint MyPoint::operator-(const MyPoint &x){
	MyPoint t = MyPoint();
	t.x = this->x - x.x;
	t.y = this->y - x.y;
	t.z = this->z - x.z;
	return t;
}

const MyPoint MyPoint::operator*(const MyPoint &x){
	MyPoint t = MyPoint();
	t.x = this->y * x.z - this->z * x.y;
	t.y = -this->x * x.z + this->z * x.x;
	t.z = this->x * x.y - this->y * x.x;
	return t;
}

MyPoint MyPoint::operator=(const MyPoint &x){
	if (this != &x)
	{
		this->x = x.x;
		this->y = x.y;
		this->z = x.z;
	}
	return *this;
}

float &MyPoint::operator()(int i)
{
	if (i == 0){
		return x;
	}
	
	if (i == 1){
		return y;
	}
	
	if (i == 2){
		return z;
	}
}

float MyPoint::Dimention(){
	return sqrt(pow(x,2) + pow(y,2) + pow(z,2));
}

MyPoint &MyPoint::Symmetry(){
	this->x = -x;
	this->y = -y;
	this->z = -z;
	return *this;
}

float MyPoint::Mul2Vector(MyPoint a, MyPoint b){
	return a.x * b.x + a.y * b.y + a.z + b.z;
}

MyPoint MyPoint::LinearAlgebra(MyPoint v1, MyPoint v2){
	this->x = v1.y * v2.z - v1.z * v2.y;
	this->y = -(v1.x * v2.z - v1.z * v2.x);
	this->z = v1.x * v2.y - v1.y * v2.x;
	return *this;
}
