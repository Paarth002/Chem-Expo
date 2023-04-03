#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>
#include <cmath>
#include <iostream>
using namespace std;
#include <GL/glut.h>

int selectedObject = 3;
bool drawThatAxis = 0;
bool lightEffect = 1;
GLdouble sphereRadius = 0.4;
GLdouble cylinderRadius = 0.2;
GLint resolution = 100;
GLint slices = resolution, stacks = resolution;

// Viewer options (GluLookAt)
float fovy = 60.0, aspect = 1.0, zNear = 1.0, zFar = 100.0;

// Mouse modifiers
float depth = 8;
float phi = 0, theta = 0;
float downX, downY;
bool leftButton = false, middleButton = false;

// colors
GLfloat oxygen[3] = {1, 0.5, 0};        
GLfloat nitrogen[3] = {0.5, 0.3, 0.5};  
GLfloat phosphate[3] = {1.0, 0.5, 0.0}; 
GLfloat carbon[3] = {0.5, 0.5, 0.5};    
GLfloat sulphur[3] = {1, 0, 0};         
GLfloat hydrogen[3] = {0, 0, 1};  
GLfloat white[3] = {1.0, 1.0, 1.0};
GLfloat black[3] = {0.0, 0.0, 0.0};

/* Prototypes */
void bond(GLfloat color[3], GLfloat height);
void draw_sphere(GLfloat color[3]);
void setLightColor(GLfloat light_color[3]);
void renderCylinder(float x1, float y1, float z1, float x2, float y2, float z2, float radius, GLUquadricObj *quadrilc);
void drawAxis();
void reshape(int w, int h);
void mouseCallback(int button, int state, int x, int y);
void motionCallback(int x, int y);
void keyboardCallback(unsigned char ch, int x, int y);
void displayCallback(void);
void buildDisplayList();
void options_menu(int input);
void initMenu();

GLdouble width, height; /* window width and height */
int wd;                 /* GLUT window handle */

void init(void)
{
    width = 1280.0; /* initial window width and height, */
    height = 800.0; /* within which we draw. */
}

void reshape(int w, int h)
{
    width = (GLdouble)w;
    height = (GLdouble)h;

    glViewport(0, 0, (GLsizei)width, (GLsizei)height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, width, 0.0, height);

    aspect = width / height;
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    init();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH);
    glutInitWindowSize((int)width, (int)height);
    wd = glutCreateWindow("H2O + SO3 -> H2SO4" /* title */);
    glutReshapeFunc(reshape);
    setLightColor(white);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glClearColor(0.0, 0.0, 0.0, 0.0);

    buildDisplayList();

    glutDisplayFunc(displayCallback);

    glutMouseFunc(mouseCallback);
    glutMotionFunc(motionCallback);

    // exit with [esc] keyboard button
    glutKeyboardFunc(keyboardCallback);

    initMenu();

    glutMainLoop();

    return 0;
}

void bond(GLfloat color[3], GLfloat height)
{
    glColor3fv(color);
    setLightColor(color);

    GLUquadric *myQuad;
    myQuad = gluNewQuadric();

    gluCylinder(myQuad, cylinderRadius, cylinderRadius, height, slices, stacks);
}

// Sphere
void draw_sphere(GLfloat color[3],GLdouble sphereRadius)
{
    glColor3fv(color);
    setLightColor(color);

    GLUquadric *myQuad;
    myQuad = gluNewQuadric();

    gluSphere(myQuad, sphereRadius, slices, stacks);
}

void setLightColor(GLfloat light_color[3])
{
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat shine[] = {100.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_color);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
    glMaterialfv(GL_FRONT, GL_SHININESS, shine);
}

void renderCylinder(float x1, float y1, float z1, float x2, float y2, float z2, float radius, GLUquadricObj *quadric)
{
    float vx = x2 - x1;
    float vy = y2 - y1;
    float vz = z2 - z1;
    float ax, rx, ry, rz;
    float len = sqrt(vx * vx + vy * vy + vz * vz);

    glPushMatrix();
    glTranslatef(x1, y1, z1);
    if (fabs(vz) < 0.0001)
    {
        glRotatef(90, 0, 1, 0);
        ax = 57.2957795 * -atan(vy / vx);
        if (vx < 0)
        {
        }
        rx = 1;
        ry = 0;
        rz = 0;
    }
    else
    {
        ax = 57.2957795 * acos(vz / len);
        if (vz < 0.0)
            ax = -ax;
        rx = -vy * vz;
        ry = vx * vz;
        rz = 0;
    }
    glRotatef(ax, rx, ry, rz);
    gluQuadricOrientation(quadric, GLU_OUTSIDE);
    gluCylinder(quadric, radius, radius, len, slices, stacks);
    glPopMatrix();
}

void drawAxis()
{
    float originAxis[3] = {3, 3, 3}; 
    float xAxis[3] = {4, 0, 0};      
    float yAxis[3] = {0, 4, 0};      
    float zAxis[3] = {0, 0, 4};      

    glDisable(GL_LIGHTING);
    glPushMatrix();
    glLineWidth(10.0);

    glBegin(GL_LINES);
    glColor3f(4.0, 0.0, 0.0);
    glVertex3fv(originAxis);
    glVertex3fv(xAxis);
    glColor3f(0.0, 4.0, 0.0);
    glVertex3fv(originAxis);
    glVertex3fv(yAxis);
    glColor3f(0.0, 0.0, 4.0);
    glVertex3fv(originAxis);
    glVertex3fv(zAxis);
    glEnd();

    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void mouseCallback(int button, int state, int x, int y)
{
    downX = x;
    downY = y;
    leftButton = ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN));
    middleButton = ((button == GLUT_MIDDLE_BUTTON) && (state == GLUT_DOWN));
}

void motionCallback(int x, int y)
{
    if (leftButton) // Rotate
    {
        phi += (x - downX) / 4.0;
        theta += (downY - y) / 4.0;
    }
    if (middleButton) // Scale
    {
        if (depth + (downY - y) / 10.0 < zFar - 10 && depth + (downY - y) / 10.0 > zNear + 3)
            depth += (downY - y) / 10.0;
    }
    downX = x;
    downY = y;

    glutPostRedisplay();
}

void keyboardCallback(unsigned char ch, int x, int y)
{
    switch (ch)
    {
    case 27:
        exit(0);
        break;
    }
    glutPostRedisplay();
}

void displayCallback(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy, aspect, zNear, zFar);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // gluLookAt(eyex, eyey, eyez, atx, aty, atz, upx, upy, upz);
    gluLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);

    // Motion Options
    glTranslatef(0.0, 0.0, -depth);
    glRotatef(-theta, 1.0, 0.0, 0.0);
    glRotatef(phi, 0.0, 1.0, 0.0);

    // Axis x, y and z Toggle
    if (drawThatAxis)
    {
        drawAxis();
    }

    // Light Effect Toggle :)
    if (lightEffect)
    {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
    }
    else
    {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
    }

    switch (selectedObject)
    {
    // Molecule 1
    case (1):
        glCallList(1);
        break;
    // Molecule 2
    case (2):
        glCallList(2);
        break;
    // Molecule 3
    case (3):
        glCallList(3);
        break;
    case (4):
        glCallList(4);
        break;
    default:
        break;
    }

    glFlush();
}

/* Our display items to prepare */
void buildDisplayList()
{
    GLuint id;

    // 3 elements
    id = glGenLists(4);

    // 1st molecule (H2SO4)
    glNewList(id, GL_COMPILE);
    glPushMatrix();
    GLUquadric *myQuad;
    myQuad = gluNewQuadric();

    // Begin drawing

    // molecules
    glPushMatrix();
    glTranslatef(0, 0, 0);
    draw_sphere(sulphur,0.8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -2, 3);
    draw_sphere(oxygen,0.8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2, -2, -2);
    draw_sphere(oxygen,0.8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.6, -2, -0.6);
    draw_sphere(oxygen,0.8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 3, 0);
    draw_sphere(oxygen,0.8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.5, -1.7, -0.2);
    draw_sphere(hydrogen,0.8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.7, 4.8, 0);
    draw_sphere(hydrogen,0.8);
    glPopMatrix();

    // links
    setLightColor(white);
    renderCylinder(0, 0, 0, 0, -2, 3, 0.35, myQuad);
    renderCylinder(0, 0, 0, -2, -2, -2, 0.35, myQuad);
    renderCylinder(0, 0, 0, 2.6, -2, -0.6, 0.35, myQuad);
    renderCylinder(0, 0, 0, 0, 3, 0, 0.35, myQuad);
    renderCylinder(2.6, -2, -0.6, 4.5, -1.7, -0.2, 0.35, myQuad);
    renderCylinder(0, 3, 0, 0.7, 4.8, 0, 0.35, myQuad);

    // End drawing

    glPopMatrix();
    glEndList();

    // 2nd molecule (SO3 tethra)
    id++;
    glNewList(id, GL_COMPILE);
    
    glPushMatrix();
    glTranslatef(0, 0, 0);
    draw_sphere(sulphur,0.8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 3, 0);
    draw_sphere(oxygen,0.8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.59807621, -1.5, 0);
    draw_sphere(oxygen,0.8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.59807621, -1.5, 0);
    draw_sphere(oxygen,0.8);
    glPopMatrix();

    //Links
    setLightColor(white);
    renderCylinder(0, 0, 0, -2.59807621, 1.5, 0, 0.35, myQuad);
    renderCylinder(-2.59807621, -1.5,0, 0, 0, 0, 0.35, myQuad);
    renderCylinder(0, 0, 0, 0, 3, 0, 0.35, myQuad);

    // End drawing

    glPopMatrix();
    glEndList();

    // 3rd molecule (Combined reaction)
    id++;
    glNewList(id, GL_COMPILE);
    
    glPushMatrix();
    glTranslatef(0, 0, 0);
    draw_sphere(oxygen,0.8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.37208721, -1.83665184, 0);
    draw_sphere(hydrogen,0.8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.37208721, -1.83665184, 0);
    draw_sphere(hydrogen,0.8);
    glPopMatrix();

    //Links
    setLightColor(white);
    renderCylinder(0, 0, 0, 2.37208721, -1.83665184, 0, 0.35, myQuad);
    renderCylinder(-2.37208721, -1.83665184, 0, 0, 0, 0, 0.35, myQuad);

    // End drawing

    glPopMatrix();
    glEndList();

     // 4th molecule (H2O tethra)

    id++;
    glNewList(id, GL_COMPILE);
    
    glPushMatrix();
    glTranslatef(0, 0, 0);
    draw_sphere(sulphur,0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 1.5, 0);
    draw_sphere(oxygen,0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.299038106, -0.75, 0);
    draw_sphere(oxygen,0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.299038106, -0.75, 0);
    draw_sphere(oxygen,0.4);
    glPopMatrix();

    //Links
    setLightColor(white);
    renderCylinder(-1.299038106, -0.75, 0, 0, 0, 0, cylinderRadius, myQuad);
    renderCylinder(0, 0, 0, 1.299038106, -0.75,0, cylinderRadius, myQuad);
    renderCylinder(0, 1.5, 0, 0, 0, 0, cylinderRadius, myQuad);

    // plus
    setLightColor(nitrogen);
    renderCylinder(-3, 0, 0, -2, 0, 0, 0.1, myQuad);
    renderCylinder(-2.5, -0.5, 0, -2.5, 0.5, 0, 0.1, myQuad);

    // arrow
    setLightColor(nitrogen);
    renderCylinder(2.5, 0, 0, 3.5, 0, 0, 0.1, myQuad);
    renderCylinder(3.146446609, 0.353553391, 0, 3.5, 0, 0, 0.1, myQuad);
    renderCylinder(3.146446609, -0.353553391, 0, 3.5, 0, 0, 0.1, myQuad);

    // H2O
    glPushMatrix();
    glTranslatef(-5, 0, 0);
    draw_sphere(oxygen,0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6.18603436, -0.91832592, 0);
    draw_sphere(hydrogen,0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.81396564, -0.91832592, 0);
    draw_sphere(hydrogen,0.4);
    glPopMatrix();

    //Links
    setLightColor(white);
    renderCylinder(-6.18603436, -0.91832592, 0, -5, 0, 0, cylinderRadius, myQuad);
    renderCylinder(-5, 0, 0, -3.81396564, -0.91832592, 0, cylinderRadius, myQuad);

    // H2SO4
    glPushMatrix();
    glTranslatef(5.2,0,0);
    draw_sphere(sulphur,0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6.2,1,1);
    draw_sphere(oxygen,0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6.2,-1,-1);
    draw_sphere(oxygen,0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.2,-1,1);
    draw_sphere(oxygen,0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.2,1,-1);
    draw_sphere(oxygen,0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7.2,1,1);
    draw_sphere(hydrogen,0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7.2,-1,-1);
    draw_sphere(hydrogen,0.4);
    glPopMatrix();

    // // links
    setLightColor(white);
    renderCylinder(5.2, 0, 0, 6.2, 1, 1, cylinderRadius, myQuad);
    renderCylinder(5.2, 0, 0, 6.2, -1, -1, cylinderRadius, myQuad);
    renderCylinder(4.2, -1, 1, 5.2, 0, 0, cylinderRadius, myQuad);
    renderCylinder(4.2, 1, -1, 5.2, 0, 0, cylinderRadius, myQuad);
    renderCylinder(6.2, 1, 1, 7.2, 1, 1, cylinderRadius, myQuad);
    renderCylinder(6.2, -1, -1, 7.2, -1, -1, cylinderRadius, myQuad);

    // End drawing
    glPopMatrix();
    glEndList();
    glutSwapBuffers();
}

void options_menu(int input)
{
    if (input == 1 || input == 2 || input == 3 || input==4)
    {
        selectedObject = input;
    }
    else if (input == 5)
    {
        if (lightEffect == 1)
        {
            lightEffect = 0;
        }
        else
        {
            lightEffect = 1;
        }
    }
    else if (input == 6)
    {
        if (drawThatAxis == 1)
        {
            drawThatAxis = 0;
        }
        else
        {
            drawThatAxis = 1;
        }
    }
    glutPostRedisplay();
}

void initMenu()
{
    glutCreateMenu(options_menu);
    glutAddMenuEntry("Molecule H2SO4", 1);
    glutAddMenuEntry("Molecule SO3", 2);
    glutAddMenuEntry("Molecule H2O", 3);
    glutAddMenuEntry("combined reaction", 4);
    // glutAddMenuEntry("Toggle LightEffect", 5);
    // glutAddMenuEntry("Toggle Axis", 6);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}