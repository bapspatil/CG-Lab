#include<stdio.h>
#include<GL/glut.h>
float x1,y1,x2,y2,x3,y3,x4,y4;
void init(){

//	glColor3f(1,0,0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,500.0,0,500.0);
	glMatrixMode(GL_MODELVIEW);
}

void drawpixel(float x,float y){
	printf("\nx=%f\ty=%f",x,y);
	glColor3f(1,0,1);
	glPointSize(1);
	glBegin(GL_POINTS);
	glVertex2f(x,y);
	glEnd();
	glFlush();
}

void edgedetect(float x1, float y1, float x2, float y2, int *le, int *re){
	int mx,y;
	float temp,x;
	if((y2-y1)<0){
		temp=y1;y1=y2;y2=temp;
		temp=x1;x1=x2;x2=temp;
	}
	if((y2-y1)!=0)
		mx=(x2-x1)/(y2-y1);
	else
		mx=x2-x1;
	x=x1;
	for(y=y1;y<=y2;y++){
		if(x<(float)le[y])
			le[y]=(int)x;
		if(x>(float)re[y])
			re[y]=(int)x;
		x+=mx;
	}
}

void scanfill(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4){
	int le[500],re[500];
	int i,y;
	for(i=0;i<500;i++){
		le[i]=500;
		re[i]=0;
	}
	edgedetect(x1,y1,x2,y2,le,re);
	edgedetect(x2,y2,x3,y3,le,re);
	edgedetect(x3,y3,x4,y4,le,re);
	edgedetect(x4,y4,x1,y1,le,re);
	for(y=0;y<500;y++){
		if(le[y]<re[y]){
			for(i=le[y];i<=re[y];i++){
				drawpixel(i,y);
			}
		}
	}
}

void display(){
	x1=200.0,y1=200.0,x2=100.0,y2=300.0,x3=200.0,y3=400.0,x4=300.0,y4=300.0;
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,1);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x1,y1);
	glVertex2f(x2,y2);
	glVertex2f(x3,y3);
	glVertex2f(x4,y4);
	glEnd();
	scanfill(x1,y1,x2,y2,x3,y3,x4,y4);
	glFlush();
}

int main(){
	//glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(10,10);
	glutInitWindowSize(500,500);
	glutCreateWindow("Scan Line");
		init();
	glutDisplayFunc(display);
	//init();
	glutMainLoop();
	return 0;
}
