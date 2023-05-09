#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <conio.h>
#include "MyPoint.h"
#include "MyCube.h"
#include "MyModelGL.h"

using namespace std;

MyPoint m;
MyCube cube;
MyModelGL model;

void myInit(){
	m = MyPoint(0,0,0);
	cube = MyCube(m, 3);
}

void keyboard(unsigned char key, int x,int y){
	if (key == ' '){
		model.CameraMoveUp();
		glutPostRedisplay();
	}
	
	if (key == 'c'){
		model.CameraMoveDown();
		glutPostRedisplay();
	}
	
	if (key == 'w'){
		model.CameraMoveForward();
		glutPostRedisplay();
	}
	
	if (key == 's'){
		model.CameraMoveBackward();
		glutPostRedisplay();
	}
	
	if (key == 'a'){
		model.CameraMoveLeft();
		glutPostRedisplay();
	}
	
	if (key == 'd'){
		model.CameraMoveRight();
		glutPostRedisplay();
	}
	
	if (key == 'i'){
		cube.ZoomIn();
		glutPostRedisplay();
	}
	
	if (key == 'o'){
		cube.ZoomOut();
		glutPostRedisplay();
	}
}

void SpecialKey(int key, int x, int y){
	if (key == GLUT_KEY_LEFT){
		model.TargetMoveLeft();
		glutPostRedisplay();
	}
	if (key == GLUT_KEY_RIGHT){
		model.TargetMoveRight();
		glutPostRedisplay();
	}
	
	if (key == GLUT_KEY_UP){
		model.TargetMoveUp();
		glutPostRedisplay();
	}
	
	if (key == GLUT_KEY_DOWN){
		model.TargetMoveDown();
		glutPostRedisplay();
	}
}

void printfInfor(){
	model.printfModelMatrix();
	cube.getCube();
	cout << endl;
	cout << "--------------------";
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	model.LoadModelGL();
	cube.drawCube();
	
	printfInfor();
	
	glFlush();
}

int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(300,100);
	glutCreateWindow("Camera Transformation");
	myInit();
	
	glViewport(0, 0, 640, 480);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(SpecialKey);
	
	glutMainLoop();
	return 0;
}
