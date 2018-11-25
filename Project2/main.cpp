#include<iostream>
#include<cstdio>
#include<Windows.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include <GL/glut.h>
#include<stdlib.h>
#include<math.h>
#define SIZE  600

using namespace std;

int a, b, c, d;
int icount = 0;

void changecolor(int , int );

inline int iround(const float a) {
	return int(a + 0.5);
}

void lineDDA(int x0, int y0, int xEnd, int yEnd)
{
	int dx = xEnd - x0, dy = yEnd - y0, k;
	float steps;
	float xIncrement, yIncrement, x = x0, y = y0;
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx) / 20;
	else
		steps = fabs(dy) / 20;
	xIncrement = float(dx) / float(steps);
	yIncrement = float(dy) / float(steps);

	//setPixel(round(x), round(y));
	for (k = 0; k < steps; k++) {
		x += xIncrement;
		y += yIncrement;
		int m, n;
		for (m = 0; m < x; m += 20) {
			for (n = 0; n < y; n += 20)
			{
				//修改中
			}
		}
		changecolor(m, n);
	}
}

void InitEnvironment()
{
	glClearColor(0.6, 0.6, 0.6, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(6);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0, 400, 0, 400);
}

void OnMouse(int button, int state, int x, int y)
{
	glPointSize(6);
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		glColor3f(1, 0, 0);
		glBegin(GL_POINTS);
		glVertex2f(x, SIZE - y);
		//spt(0, 0);
		glEnd();
		glFlush();
	}
	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		glColor3f(0, 1, 0);
		glBegin(GL_POINTS);
		glVertex2f(x, SIZE - y);
		glEnd();
		glFlush();
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		glColor3f(0, 0, 1);
		glBegin(GL_POINTS);
		glVertex2f(x, SIZE - y);
		glEnd();
		glFlush();

	}



}

void mouseMove(int x, int y)
{
	glPointSize(6);
	glColor3f(1, 0, 0);
	glBegin(GL_POINTS);
	glVertex2f(x, SIZE - y);
	glEnd();
	glFlush();
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}


void mouseClick(int btn, int state, int x, int y)
{
	printf("点击了鼠标，btn:%d,state:%d,x:%d,y:%d\n", btn, state, x, y);
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		printf("按下了左边按钮\n");
		a = x;
		b = y;
		++icount;
		
	}
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		printf("松开了左边按钮\n");
	}
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		printf("按下了右边按钮\n");
		c = x;
		d = y;
		++icount;

	}
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
		printf("松开了右边按钮\n");

	}


	if (icount > 0 && (icount % 2 == 0)) {
		lineDDA(a, b, c, d);
	}

	int m, n;
	for ( m = 0; m < x; m += 20) {
		for ( n = 0; n < y; n += 20)
		{
			//修改中
		}
	}
	printf("%d %d\n", m,n);
	changecolor(m, n);

}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, SIZE, 0.0, SIZE);
}

void changecolor(int x, int  y) {
	glColor3f(0.8, 0.9, 0.2);
	//glClearColor(0.6, 0.6, 0.6, 0);
	glBegin(GL_QUADS);
	glVertex2i(x - 20, SIZE - y + 19);
	glVertex2i(x - 1, SIZE - (y - 19)) ;
	glVertex2i(x - 1, SIZE - y);
	glVertex2i(x - 20, SIZE - y);
	glEnd();
	glFlush();
}

void draw()
{
	glClearColor(1.0, 1.0, 0.2, 0.4);//修改底色
	glClear(GL_COLOR_BUFFER_BIT);//貌似可有可无
	glBegin(GL_QUADS);
	int m, n;//i=1,j=1,a[SIZE/10][SIZE/10];
	for (m = 0; m < SIZE ; m += 20)
		for (n = 0; n < SIZE ; n +=20)
		{
			glColor3f(1.0, 0.6, 1.0);
			glVertex2i(m, n);
			glVertex2i(m + 19, n);
			glVertex2i(m + 19, n + 19);
			glVertex2i(m, n + 19);

		}
	glEnd();
	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(SIZE , SIZE);
	glutCreateWindow("好漂亮好漂亮");
	init();
	glutDisplayFunc(draw);
	
	//InitEnvironment();   //初始化
	glutMouseFunc(&OnMouse);  //注册鼠标事件
	//glutMotionFunc(mouseMove);
	glutDisplayFunc(&myDisplay);   //回调函数 
	/*鼠标点击事件，鼠标点击或者松开时调用 */
	glutMouseFunc(mouseClick);
	glutDisplayFunc(draw);
	glutMainLoop();
}