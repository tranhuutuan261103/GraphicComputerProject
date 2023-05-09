#ifndef MyPoint_h
#define MyPoint_h
#include <iostream>
#include <string>

using namespace std;

class MyPoint{
	private:
		float x;
		float y;
		float z;
	public:
		MyPoint();
		MyPoint(float, float, float);
		float getX(){
			return x;
		}
		float getY(){
			return y;
		}
		float getZ(){
			return z;
		}
		void setX(float x){
			this->x = x;
		}
		void setY(float y){
			this->y = y;
		}
		void setZ(float z){
			this->z = z;
		}
		
		void addX(float x){
			this->x += x;
		}
		void addY(float y){
			this->y += y;
		}
		void addZ(float z){
			this->z += z;
		}
		void addXYZ(MyPoint point){
			this->x += point.x;
			this->y += point.y;
			this->z += point.z;
		}
		
		void getPoint(){
			cout << "[" << x << "," << y << "," << z << "]";
		}
		
		const MyPoint Normalize();
		const MyPoint operator-(const MyPoint &p);
		const MyPoint operator*(const MyPoint &p);
		MyPoint operator=(const MyPoint &x);
		float &operator()(int);
		
		float Dimention();
		MyPoint &Symmetry();
		float Mul2Vector(MyPoint, MyPoint);
		MyPoint LinearAlgebra(MyPoint, MyPoint);
};

#endif
