#include <GL/glut.h>
#include <stdio.h>
int theta[3] = { 0, 0, 0 };
int flag = 2;
float q[8][3] = { { 0, 0, 1 }, { 0, 1, 1 }, { 1, 1, 1 }, { 1, 0, 1 }, { 0, 0, 0 }, { 0, 1, 0 }, { 1, 1, 0 }, { 1, 0, 0 } };
float p[8][3] = { { -1, -1, 1 }, { -1, 1, 1 }, { 1, 1, 1 }, { 1, -1, 1 }, { -1, -1, -1 }, { -1, 1, -1 }, { 1, 1, -1 }, { 1, -1, -1 } };

void myinit() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2, 2, -2, 2, -2, 2);
	glMatrixMode(GL_MODELVIEW);
}

void polygon(int a, int b, int c, int d) {
	glBegin(GL_POLYGON);
		glColor3fv(q[a]);
		glVertex3fv(p[a]);
		glColor3fv(q[b]);
		glVertex3fv(p[b]);
		glColor3fv(q[c]);
		glVertex3fv(p[c]);
		glColor3fv(q[d]);
		glVertex3fv(p[d]);
	glEnd();
	glFlush();
}

void spincube() {
	for (unsigned int i = 0; i < 65000000; i++);
	theta[flag] += 5;
	if (theta[flag] >= 360)
		theta[flag] = 0;
	glutPostRedisplay();
}

void mouse(int b, int s, int x, int y) {
	if (b == GLUT_LEFT_BUTTON && s == GLUT_DOWN)
		flag = 0;
	else if (b == GLUT_RIGHT_BUTTON && s == GLUT_DOWN)
		flag = 2;
	else
		flag = 1;
}

void colorcube() {
	polygon(0, 1, 2, 3);
	polygon(4, 5, 6, 7);
	polygon(4, 5, 1, 0);
	polygon(1, 5, 6, 2);
	polygon(7, 6, 2, 3);
	polygon(0, 4, 7, 3);
}

void display() {
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	glRotatef(theta[0], 1, 0, 0);
	glRotatef(theta[1], 0, 1, 0);
	glRotatef(theta[2], 0, 0, 1);
	colorcube();
	glutSwapBuffers();
	glFlush();
}

int main() {
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Spin Cube");
	myinit();
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutIdleFunc(spincube);
	glutMainLoop();
}
