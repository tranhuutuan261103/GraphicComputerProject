#ifndef MyCube_h
#define MyCibe_h
#include "MyPoint.h"

using namespace std;

class MyCube{
	private:
		MyPoint centerPoint;
		float sideLength;
	public:
		MyCube();
		MyCube(MyPoint centerPoint, float sideLength){
			this->centerPoint = centerPoint;
			this->sideLength = sideLength;
		}
		void getCube(){
			cout << "Tam hinh lap phuong la: ";
			centerPoint.getPoint();
			cout << endl;
			cout << "Do dai canh:";
			cout << sideLength;
			cout << endl;
		}
		void drawCube();
		void ZoomIn();
		void ZoomOut();
};

#endif
