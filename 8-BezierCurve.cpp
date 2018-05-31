#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define pi 3.142

typedef struct wcPt3D
{
    float x, y, z;
};

void myinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 130, 0, 130);
    glMatrixMode(GL_MODELVIEW);
}

void binomialCoefficient(int n, int *C)
{
    for (int k = 0; k <= n; k++)
    {
        C[k] = 1;
        for (int j = n; j >= k + 1; j--)
            C[k] *= j;
        for (int j = n - k; j >= 2; j--)
            C[k] /= j;
    }
}

void computeBezPt(float u, wcPt3D *bezPt, int nCtrlPts, wcPt3D *ctrlPts, int *C)
{
    int n = nCtrlPts - 1;
    bezPt->x = bezPt->y = bezPt->z = 0;
    for (int k = 0; k < nCtrlPts; k++)
    {
        float bezBlendFcn = C[k] * pow(u, k) * pow(1 - u, n - k);
        bezPt->x += ctrlPts[k].x * bezBlendFcn;
        bezPt->y += ctrlPts[k].y * bezBlendFcn;
        bezPt->z += ctrlPts[k].z * bezBlendFcn;
    }
}

void bezier(wcPt3D *ctrlPts, int nCtrlPts, int nBezCurvePts)
{
    wcPt3D bezCurvePt;
    int *C = new int[nCtrlPts];
    binomialCoefficient(nCtrlPts - 1, C);
    glBegin(GL_LINE_STRIP);
    for (int k = 0; k <= nBezCurvePts; k++)
    {
        float u = (float)k / nBezCurvePts;
        computeBezPt(u, &bezCurvePt, nCtrlPts, ctrlPts, C);
        glVertex2f(bezCurvePt.x, bezCurvePt.y);
    }
    glEnd();
    delete[] C;
}

void display()
{
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    wcPt3D ctrlPts[4] = {
        {20, 100, 0},
        {30, 110, 0},
        {50, 90, 0},
        {60, 100, 0}};
    int nCtrlPts = 4, nBezCurvePts = 20;
    static float theta = 0;
    ctrlPts[1].x += 10 * sin(theta * pi / 180);
    ctrlPts[1].y += 5 * sin(theta * pi / 180);
    ctrlPts[2].x -= 10 * sin((theta + 30) * pi / 180);
    ctrlPts[2].y -= 10 * sin((theta + 30) * pi / 180);
    ctrlPts[3].x -= 4 * sin(theta * pi / 180);
    ctrlPts[3].y += sin((theta - 30) * pi / 180);
    theta += 0.1;
    glPushMatrix();
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 8; j++)
        {
            glTranslatef(0, -0.8, 0);
            bezier(ctrlPts, nCtrlPts, nBezCurvePts);
        }
    glPopMatrix();
    glLineWidth(5);
    glBegin(GL_LINES);
        glVertex2f(20, 100);
        glVertex2f(20, 40);
    glEnd();
    glFlush();
    glutPostRedisplay();
    glutSwapBuffers();
}

void menu(int op)
{
    if (op == 1) glColor3f(1, 0, 0);
    else if (op == 2) glColor3f(0, 1, 0);
    else if (op == 3) glColor3f(0, 0, 1);
    else exit(0);
    glutPostRedisplay();
}

int main()
{
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("BEZIER CURVE");
    myinit();
    glutDisplayFunc(display);
    glutCreateMenu(menu);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Green", 2);
    glutAddMenuEntry("Blue", 3);
    glutAddMenuEntry("Exit", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
}
