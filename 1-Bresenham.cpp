/*Implement Bresenham�s line drawing algorithm for all types of slope.*/

#include <stdio.h>
#include <GLUT/glut.h>
#include <math.h>
int xx, yy, xend, yend;
void myinit()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);
	glMatrixMode(GL_MODELVIEW);
}
void setPixel(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
	glFlush();
}
void Bresenhamline()
{
	int dx = xend - xx, dy = yend - yy;
	int p, x, y;
	int twody = 2 * dy, twodyMinustwodx = 2 * (dy - dx);
	int twodx = 2 * dx, twodxMinustwody = 2 * (dx - dy);

	x = xx;
	y = yy;
	glColor3f(1, 0, 0); // Set color to red.
	glPointSize(3);		//Set point size to 3
	if (dx > dy)
	{
		//For slope m<1
		p = 2 * dy - dx;
		setPixel(x, y);
		while (x < xend)
		{
			x = x + 1;
			if (p < 0)
				p = p + twody;
			else
			{
				y = y + 1;
				p = p + twodyMinustwodx;
			}
			setPixel(x, y);
		}
	}
	else
	{
		//For slope m>1
		p = 2 * dx - dy;
		setPixel(x, y);
		while (y < yend)
		{
			y = y + 1;
			if (p < 0)
				p = p + twodx;
			else
			{
				x = x + 1;
				p = p + twodxMinustwody;
			}
			setPixel(x, y);
		}
	}
}

void display()
{
	glClearColor(1, 1, 1, 1);	 //Specifies a background RGB color for a display window.
	glClear(GL_COLOR_BUFFER_BIT); // Clear display window.
	Bresenhamline();
	glFlush(); // Process all OpenGL routines as quickly as possible.
}
int main()
{
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);		   // Set display mode.
	glutInitWindowPosition(100, 100);					   // Set top-left display-window position.
	glutInitWindowSize(500, 500);						   // Set display-window width and height.
	glutCreateWindow("Bresenham's Line Drawing Algorthm"); // Create display window.
	myinit();											   // Execute initialization procedure.

	printf("Enter co-ordinates of first point: ");
	scanf("%d %d", &xx, &yy);

	printf("Enter co-ordinates of second point: ");
	scanf("%d %d", &xend, &yend);

	glutDisplayFunc(display); //Invokes a function to create a picture within the current display window.
	glutMainLoop();
	return 0; //Executes the computer-graphics program.
}
