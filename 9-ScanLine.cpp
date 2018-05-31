#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

void edgedetect(int x1, int y1, int x2, int y2, int *le, int *re) {
	int mx, x, temp;
	if (y2 - y1 < 0) {
		temp = y1; y1 = y2; y2 = temp;
		temp = x1; x1 = x2; x2 = temp;
	}
	if (y2 - y1 != 0)
		mx = (x2 - x1) / (y2 - y1);
	else 
		mx = x2 - x1;
	x = x1;
	for (int i = y1; i <= y2; i++) {
		if (x < le[i])
			le[i] = x;
		if (x > re[i])
			re[i] = x;
		x += mx;
	}
}

void drawpixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void scanfill(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
	glBegin(GL_LINE_LOOP);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		glVertex2f(x3, y3);
		glVertex2f(x4, y4);
	glEnd();
	int le[500], re[500];
	for (int i = 0; i < 500; i++) {
		le[i] = 500;
		re[i] = 0;
	}
	edgedetect(x1, y1, x2, y2, le, re);
	edgedetect(x2, y2, x3, y3, le, re);
	edgedetect(x3, y3, x4, y4, le, re);
	edgedetect(x4, y4, x1, y1, le, re);
	for (int y = 0; y < 500; y++)
		if (le[y] <= re[y])
			for (int x = le[y]; x < re[y]; x++)
				drawpixel(x, y);
}

void display() {
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void myinit() {
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);
	glMatrixMode(GL_MODELVIEW);
}

void menu(int op) {
	if (op == 1) glColor3f(1, 0, 0);
	else if (op == 2) glColor3f(0, 1, 0);
	else if (op == 3) glColor3f(0, 0, 1);
	else exit(0);
	scanfill(200, 200, 100, 300, 200, 400, 300, 300);
}

int main() {
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Scan-Line Filling Algorithm");
	myinit();
	glutDisplayFunc(display);
	glutCreateMenu(menu);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Exit", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}