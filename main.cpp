#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <conio.h>


using namespace std;

// Toa do camera ban dau
double t[3] = {8, 9, 8}; // 8 9 8
// Toa do muc tieu (tam cua hinh lap phuong)
double c[3] = {0, 0, 0}; // 0 0 0
double P[4]={0,0,0,1};

double a;

class MyPoint{
	private:
		double x;
		double y;
		double z;
	public:
		MyPoint(double x,double y,double z){
			this->x = x;
			this->y = y;
			this->z = z;
		}
		
		double getX(){
			return x;
		}
		
		double getY(){
			return y;
		}
		
		double getZ(){
			return z;
		}
		
		MyPoint Rotate0y(double alpha)
		{
			alpha = (M_PI * alpha) / 180;
			double x0 = x;
			double y0 = y;
			double z0 = z;
			x = x0 * cos(alpha) + z0 * sin(alpha);
			z = x0 * (-sin(alpha)) + z0 * cos(alpha);
			return *this;
		}
		
		// Tich co huong cua 2 vevtor
		MyPoint LinearAlgebra(MyPoint v1, MyPoint v2){
			this->x = v1.y * v2.z - v1.z * v2.y;
			this->y = -(v1.x * v2.z - v1.z * v2.x);
			this->z = v1.x * v2.y - v1.y * v2.x;
			return *this;
		}
		
		double DimensionWithO(){
			return sqrt(pow(x,2) + pow(y,2) + pow(z,2));
		}
		
		MyPoint Zoom(double d){
			double D = this->DimensionWithO();
			x = x - x * (d/D);
			y = y - y * (d/D);
			z = z - z * (d/D);
			return *this;
		}
};

void subMatrix(double C[],double A[],double B[])
{
	for (int i=0;i<3;i++)
	{
		C[i] = A[i] - B[i];
	}
}

void normalizeMatrix(double A[])
{
	double sum=0, d;
	for (int i=0;i<3;i++)
	{
		sum += A[i] * A[i];
	}
	d = sqrt(sum);
	if (d>0)
	{
		for (int i=0;i<3;i++)
			A[i]/=d;
	}
	else
	{
		cout << "NULL matrix";
	}
}

void direction_vector(double C[],double A[],double B[])
{
	int j,k;
	for (int i=0;i<3;i++)
	{
		j=(i+1)%3;
		k=(j+1)%3;
		C[i] = A[j]*B[k] - A[k]*B[j];
	}
}

// ma tran chuyen vi
void transpose(double A[][4],double B[][4])
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
			A[i][j] = B[j][i];
	}
}

void printfMatrix(double matrix[][4])
{
	for(int i =0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			cout << fixed << setprecision(4) << setw(9) << matrix[j][i] << " ";
		}
		cout << endl;
	}
}

void changedPoint(double finishP[],double A[][4],double P[])
{
	for(int i=0;i<4;i++)
	{
		double s=0;
		for(int k=0;k<4;k++)
			 s += A[i][k] * P[k];
		finishP[i] = s;
	}
}

void printfPoint(double A[])
{
	for(int i=0;i<4;i++)
	{
		cout << fixed << setprecision(5) << setw(8) << A[i] << " ";
	}
}

void myInit()
{
	cout << "Nhap do dai canh a = ";
	cin >> a;
}

void setDisplay()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.5,1.5,-1.5,1.5,1.5,30);
	
	glMatrixMode(GL_MODELVIEW);
	glOrtho(-200, 200, -200, 200, -200, 200);
}

void keyboard(unsigned char key, int x,int y){
	MyPoint m = MyPoint(t[0],t[1],t[2]);
	if(key=='d')
	{
		m.Rotate0y(3);
		t[0] = m.getX();
		t[2] = m.getZ();
		glutPostRedisplay();
	}
	if (key=='a'){
		m.Rotate0y(-3);
		t[0] = m.getX();
		t[2] = m.getZ();
		glutPostRedisplay();
	}
	
	if(key=='w')
	{
		t[1] ++ ;
		glutPostRedisplay();
	}
	if (key=='s'){
		t[1] -- ;
		glutPostRedisplay();
	}
	
	if (key == 'i'){
		if (m.DimensionWithO() < 1){
			return;
		}
		m.Zoom(0.25);
		t[0] = m.getX();
		t[1] = m.getY();
		t[2] = m.getZ();
		glutPostRedisplay();
	}
	
	if (key == 'o'){
		m.Zoom(-0.25);
		t[0] = m.getX();
		t[1] = m.getY();
		t[2] = m.getZ();
		glutPostRedisplay();
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	setDisplay();
	
	double up[3] = {0,1,0};
	double target[3] = {c[0],c[1],c[2]};
	double eye[3] = {t[0],t[1],t[2]};
	double u[3],f[3],r[3];
	double Rt[4][4], R[4][4],p1[4][4],p2[4][4];
	double Pc[4];
	
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(eye[0],eye[1],eye[2],target[0],target[1],target[2],up[0],up[1],up[2]);
	glGetDoublev(GL_MODELVIEW_MATRIX,&p1[0][0]);
	cout << "\nMa tran bien doi bang gluLookAt:\n";
	printfMatrix(p1);
	
	glLoadIdentity();
	
	subMatrix(f,eye,target);
	normalizeMatrix(f);
	direction_vector(r,up,f);
	normalizeMatrix(r);
	direction_vector(u,f,r);
	normalizeMatrix(u);
	
	for (int i=0;i<3;i++)
	{
		R[0][i] = r[i];
		R[1][i] = u[i];
		R[2][i] = f[i];
		R[3][i] = 0;
		R[i][3] = 0;
	}
	R[3][3]=1;
	
	transpose(Rt,R);	
	glMultMatrixd(&Rt[0][0]);
	glTranslated(-eye[0],-eye[1],-eye[2]);
	glGetDoublev(GL_MODELVIEW_MATRIX,&p2[0][0]);
	
	cout << "\nMa tran bien doi bang Matrix model view:\n";
	printfMatrix(p2);
	
	double temp[4][4];
	transpose(temp,p2);
	changedPoint(Pc,temp,P);
	cout << "Toa do diem Pworld sau khi bien doi thanh Pcamera la:";
	printfPoint(Pc);
	
//	glutWireTeapot(3);

	glPointSize(2);
	glBegin(GL_POINTS);
	glColor3f(1,0,0);
	glVertex3f(P[0],P[1],P[2]);
	glEnd();
	
	glutWireCube(a);
	
	glFlush();
}




int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(300,100);
	glutCreateWindow("Lab03 Bai2");
	myInit();
	
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	
	glutMainLoop();
	return 0;
}
