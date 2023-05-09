#ifndef MyRotation_h
#define MyRotation_h
#include "MyPoint.h"
#include "Matrix.h"

class MyRotaion{
	private:
	public:
		Matrix RotateOx(float);
		Matrix RotateOy(float);
		Matrix RotateOz(float);
		
		Matrix Translate(MyPoint p);
		
		Matrix Rotate(MyPoint, MyPoint, float);
};

#endif
