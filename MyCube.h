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
			centerPoint.getPoint();
			cout << endl;
			cout << sideLength;
		}
		void drawCube();
		void ZoomIn();
		void ZoomOut();
};

#endif
