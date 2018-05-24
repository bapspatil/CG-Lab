/* Design, develop and implement recursively subdivide a tetrahedron to form 3D
sierpinski gasket. The number of recursive steps is to be specified by the user.
*/
#include<stdlib.h>
#include<GLUT/glut.h>
#include<stdio.h>
#include<math.h>
int n;
float v[4][3]={{0,1,0},{.5,-.5,0},{-.5,-.5,0},{0,0,1}};
void myinit()
{
	glMatrixMode(GL_PROJECTION);	//Specifies current matrix for geometric-viewing transformations
	glLoadIdentity();		//Sets current matrix to identity.
	glOrtho(-2,2,-2,2,-2,2);	//Specifies parameters for a clipping window and the near and far clipping planes 
	glMatrixMode(GL_MODELVIEW);
}
void triangle(float *a,float *b,float *c)
{
	glBegin(GL_POLYGON);
		glVertex3fv(a);
		glVertex3fv(b);
		glVertex3fv(c);
	glEnd();
}
void divide_triangle(float *a,float *b,float *c,int n)
{
		float ab[3],bc[3],ac[3];
		int j;
		if(n>0)
		{
			for(j=0;j<3;j++)
			{
				ab[j]=(a[j]+b[j])/2;
				bc[j]=(b[j]+c[j])/2;
				ac[j]=(a[j]+c[j])/2;
			}
			divide_triangle(a,ab,ac,n-1);
			divide_triangle(ab,b,bc,n-1);
			divide_triangle(ac,bc,c,n-1);
		}
		else
			triangle(a,b,c);
}
void display1()
{
	
		glClearColor(1,1,1,1);		//Specifies a background RGB color for a display window.
		glClear(GL_COLOR_BUFFER_BIT);	// Clear display window.
		glColor3f(1,0,0);		//Set current color to red
		divide_triangle(v[0],v[1],v[2],n);
		glColor3f(0,1,0);
		divide_triangle(v[3],v[2],v[0],n);
		glColor3f(0,0,1);
		divide_triangle(v[3],v[0],v[1],n);
		glColor3f(1,0,1);
		divide_triangle(v[3],v[1],v[2],n);
		glFlush();			// Process all OpenGL routines as quickly as possible.
}
int main()
{
        glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);// sets buffering and color mode for a display window
        glutInitWindowPosition(100,100);        //Specifies coordinates for the top-left corner of a display window.
        glutInitWindowSize(500,500);            //Specifies width and height for a display window.
        glutCreateWindow("3D SIERPINSKI PATTERN");  //Creates a display window & specify a display-window title
        printf("Enter the value of n");
        scanf("%d",&n);
        myinit();                   // Execute initialization procedure.
        glutDisplayFunc(display1);           //Invokes a function to create a picture within the current display window.
        glutMainLoop();                   //Executes the computer-graphics program.
    return 0;
}
