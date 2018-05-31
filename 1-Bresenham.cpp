#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

int xx, yy, xend, yend;

void myinit() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	glMatrixMode(GL_MODELVIEW);
}

void setPixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
	glFlush();
}

void Bresenhamline() {
	int dx = abs(xend - xx), dy = abs(yend - yy);
	int p, x, y;
	int twody = 2 * dy, twodyMinustwodx = 2 * (dy - dx);
	int twodx = 2 * dx, twodxMinustwody = 2 * (dx - dy);

	x = xx;
	y = yy;
	
	glColor3f(1, 0, 0);
	glPointSize(3);
	if (dx > dy) {
		p = 2 * dy - dx;
		setPixel(x, y);
		while (x < xend) {
			x = x + 1;
			if (p < 0)
				p = p + twody;
			else {
				y = y + 1;
				p = p + twodyMinustwodx;
			}
			setPixel(x, y);
		}
	}
	else {
		p = 2 * dx - dy;
		setPixel(x, y);
		while (y < yend) {
			y = y + 1;
			if (p < 0)
				p = p + twodx;
			else {
				x = x + 1;
				p = p + twodxMinustwody;
			}
			setPixel(x, y);
		}
	}
}

void display() {
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	Bresenhamline();
	glFlush();
}

int main() {
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Bresenham's Line Drawing Algorthm");
	myinit();
	printf("Enter co-ordinates of first point: ");
	scanf_s("%d %d", &xx, &yy);

	printf("Enter co-ordinates of second point: ");
	scanf_s("%d %d", &xend, &yend);

	glutDisplayFunc(display);
glutMainLoop();
}
