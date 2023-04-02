#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;

float xRotated = 90.0, yRotated = 0.0, zRotated = 0.0;

//------------------------------  reshapeFunc  ---------------------------------

void reshapeFunc(int x, int y)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, x, y);
}

//------------------------------  Draw_Spheres   -------------------------------

void Draw_Spheres(void)
{
    // glMatrixMode(GL_MODELVIEW);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glLoadIdentity();
    glColor3f(1, 0, 0);
    GLUquadric *quad;
    quad = gluNewQuadric();
    // glTranslatef(2, 2, 2);
    gluSphere(quad, 1, 100, 20);

    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(800, 700);
    glutInitWindowPosition(700, 200);
    glutCreateWindow("Sphere Rotating Animation");
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glClearColor(0.0, 0.0, 0.0, 0.0);

    glutDisplayFunc(Draw_Spheres);
    glutReshapeFunc(reshapeFunc);
    // glutIdleFunc(idleFunc);

    glutMainLoop();
}
