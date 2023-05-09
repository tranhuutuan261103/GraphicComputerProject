#ifndef MyModelGL_h
#define MyModelGL_h
#include "MyPoint.h"
#include "Matrix.h"

using namespace std;

class MyModelGL{
	private:
		MyPoint cameraPoint;
		MyPoint targetPoint;
		Matrix model;
		float v;
	public:
		MyModelGL();
		float Mul2Vector(MyPoint);
		void LoadModelGL();
		Matrix CameraLookAt();
		
		void CameraMove(MyPoint);
		
		void CameraMoveUp();
		void CameraMoveDown();
		void CameraMoveForward();
		void CameraMoveBackward();
		void CameraMoveLeft();
		void CameraMoveRight();
		
		void TargetMoveLeft();
		void TargetMoveRight();
		void TargetMoveUp();
		void TargetMoveDown();
		
		void printfModelMatrix();
};

#endif
