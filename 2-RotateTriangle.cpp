#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

float th;
int xp, yp;
int p[3][2];

void myinit() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);
	glMatrixMode(GL_MODELVIEW);
}

void drawTriangle() {
	glBegin(GL_POLYGON);
		glVertex2iv(p[0]);
		glVertex2iv(p[1]);
		glVertex2iv(p[2]);
	glEnd();
	glFlush();
}

void rotate() {
	float x, y, rth;
	rth = th * 3.142 / 180;
	for (int k = 0; k < 3; k++) {
		x = p[k][0];
		y = p[k][1];
		p[k][0] = x * cos(rth) - y * sin(rth) + xp * (1 - cos(rth)) + yp * sin(rth);
		p[k][1] = x * sin(rth) + y * cos(rth) - xp * sin(rth) + yp * (1 - cos(rth));
	}
	glColor3f(0, 1, 0);
	drawTriangle();
}

void display() {
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 1);
	drawTriangle();
	rotate();
	glFlush();
}

int main() {
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(30, 30);
	glutCreateWindow("Rotate triangle");
	myinit();
	printf("Enter coordinates of triangle:\n");
	for (int i = 0; i < 3; i++)
		scanf_s("%d%d", &p[i][0], &p[i][1]);
	printf("Enter pivot point: ");
	scanf_s("%d%d", &xp, &yp);
	printf("Enter rotation angle: ");
	scanf_s("%f", &th);
	glutDisplayFunc(display);
	glutMainLoop();
}