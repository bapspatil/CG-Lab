//Scan Line Algorithm
#include <GLUT/glut.h>
#include <stdio.h>

//Global Edge table
// et contains information as ymin , xmin, ymax,1/m 
float et[4][4]={{100,250,200,-1}, //ab
{100,250,200,1},// ad
{200,150,300,1},//bc
{200,350,300,-1}};// dc


int np=4;// number of points


float ae[4][3];
//js is scan line
// find minimum value of scan

float js=et[0][0];
int iaet=0;
int ymax=0;//max val of scan

//add to a e t
void addaet()
{
    int i;
    for(i=0; i<np;i++)
    {
        printf("scan line =%f  & iate=%d\n",js,iaet);
        if(js==et[i][0]) 
        {
            ae[iaet][0]=et[i][1];//x min
            ae[iaet][1]=et[i][2];//ymax
            ae[iaet][2]=et[i][3];//1/m
            if(ae[iaet][1]>ymax) ymax=ae[iaet][1];//update ymax value
            iaet++;
        }

    }

}
// update  aet
void upaet()
{
    int i;
    for(i=0;i<np;i++)
        ae[i][0]=ae[i][0]+ae[i][2];//x=x+1/m
}

void draw_pixel(float x1,float x2)
{
    float n;
    for(n=x1;n<x2;n++)// fill from x1 to x2
    {
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_POINTS);
    glVertex2f(n,js);
    glEnd();
    glFlush();
    }
    printf(" x1=%f  x2= %f\n",x1,x2); 
}

void fill_tri()
{
    float x[3]={0,0,0};
    int i=0;
    bool done=false;
do
{
    i=0;
    addaet();
        printf("  1=%f   2= %f  %f\n",ae[0][1],ae[1][1],js);

    if(ae[0][1]>js){x[i]=ae[0][0]; i++; printf(" 1=%f ae=%f \n ",ae[0][0],x[0]);}
    if(ae[1][1]>js){x[i]=ae[1][0]; i++;printf(" 1=%f ae=%f \n",ae[0][0],x[0]);}
    if(ae[2][1]>js){x[i]=ae[2][0]; i++;}
    if(ae[3][1]>js){x[i]=ae[3][0]; i++;}
    draw_pixel(x[0],x[1]);
    upaet();
    js++;
}
while(js<=ymax);
}

void display()
{

glClear(GL_COLOR_BUFFER_BIT);    
glClearColor(1.0,1.0,1.0,1.0);
fill_tri();
glFlush();
}
void myinit()
{
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,499.0,0.0,499.0);
    glMatrixMode(GL_MODELVIEW);

}
int main(int argc, char** argv)
{
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(400,300);
    glutCreateWindow("polygon filling algorithm");
    myinit();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
