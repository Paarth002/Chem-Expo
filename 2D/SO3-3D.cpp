#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;

double FinalX = 0.0;
double FinalY = 0.0;
GLdouble sphereRadius = 100;
GLdouble cylinderRadius = 100;
GLint resolution = 100;
GLint slices = resolution, stacks = resolution;

struct color
{
    double r, g, b;
};

color red = {1, 0, 0};
color green = {0, 1, 0};
color blue = {0, 0, 1};
color yellow = {1, 1, 0};
color cyan = {0, 1, 1};
color magenta = {1, 0, 1};
color white = {1, 1, 1};
color black = {0, 0, 0};

// double SO3_centers[4][2] = {
//     {0, 0},
//     {150, 0},
//     {75, 129.9},
//     {75, 43.3}};
double SO3_centers[4][3] = {
    {0, 0, 0},
    {300, 0, 0},
    {150, 259.8, 0},
    {150, 86.603, 0}};
// 1st 3 points are the vertices of the equilateral triangle and the 4th point is the centroid
// Change vertices only such that the triangle is equilateral and 4th one is centroid

color SO3_colors[4] = {red, red, red, yellow};
double SO3_radii[4] = {25, 25, 25, 50};

void draw_circle(double x, double y, double r, color c)
{
    glColor3f(c.r, c.g, c.b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++)
    {
        double angle = 2 * 3.1416 * i / 360;
        double x1 = x + r * cos(angle);
        double y1 = y + r * sin(angle);
        glVertex2f(x1, y1);
    }
    glEnd();
}

// Sphere

GLfloat c[3] = {1, 0, 0};

void draw_sphere(GLfloat color[3])
{
    // sans lumière:
    glColor3fv(color);

    // Light Options
    // GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    // GLfloat shine[] = {100.0};
    // glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    // glLightfv(GL_LIGHT0, GL_SPECULAR, light_color);
    // glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
    // glMaterialfv(GL_FRONT, GL_SHININESS, shine);

    GLUquadric *myQuad;
    myQuad = gluNewQuadric();

    // Création de la sphere
    gluSphere(myQuad, sphereRadius, slices, stacks);
}

void draw_SO3(double centers[4][3], double radii[4], color colors[4])
{
    for (int i = 0; i < 3; i++)
    {
        glBegin(GL_LINES);
        glColor3f(1, 1, 1);
        glVertex2f(centers[3][0], centers[3][1]);
        glVertex2f(centers[i][0], centers[i][1]);
        glEnd();
    }

    for (int i = 0; i < 4; i++)
    {
        draw_circle(centers[i][0], centers[i][1], radii[i], colors[i]);
    }
}

void translate_SO3(char key)
{
    int n = 4;
    glClear(GL_COLOR_BUFFER_BIT);
    double delta = 10;

    if (key == 'w')
    {
        for (int i = 0; i < n; i++)
        {
            SO3_centers[i][1] += delta;
        }
    }
    else if (key == 'a')
    {
        for (int i = 0; i < n; i++)
        {
            SO3_centers[i][0] -= delta;
        }
    }
    else if (key == 's')
    {
        for (int i = 0; i < n; i++)
        {
            SO3_centers[i][1] -= delta;
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            SO3_centers[i][0] += delta;
        }
    }
    draw_SO3(SO3_centers, SO3_radii, SO3_colors);

    glFlush();
}

// Scale Polygon along its center
void scale(char zoom)
{
    double scale;
    glClear(GL_COLOR_BUFFER_BIT);

    if (zoom == 'i')
    {
        scale = 1.05;
    }
    else
        scale = 0.95;

    double d_old = sqrt(pow(SO3_centers[0][0] - SO3_centers[3][0], 2) + pow(SO3_centers[0][1] - SO3_centers[3][1], 2));
    double d_new = scale * d_old;

    int flags[6] = {1, 1, 1, 1, 1, 1};
    if (SO3_centers[0][0] < SO3_centers[3][0])
        flags[0] = -1;
    if (SO3_centers[0][1] < SO3_centers[3][1])
        flags[1] = -1;
    if (SO3_centers[1][0] < SO3_centers[3][0])
        flags[2] = -1;
    if (SO3_centers[1][1] < SO3_centers[3][1])
        flags[3] = -1;
    if (SO3_centers[2][0] < SO3_centers[3][0])
        flags[4] = -1;
    if (SO3_centers[2][1] < SO3_centers[3][1])
        flags[5] = -1;

    if (SO3_centers[0][0] == SO3_centers[3][0])
    {
        SO3_centers[0][0] = SO3_centers[3][0];
        SO3_centers[0][1] = SO3_centers[3][1] + flags[1] * d_new;
    }
    else
    {
        double m1 = abs((SO3_centers[0][1] - SO3_centers[3][1]) / (SO3_centers[0][0] - SO3_centers[3][0]));
        SO3_centers[0][0] = SO3_centers[3][0] + flags[0] * d_new / (sqrt(1 + m1 * m1));
        SO3_centers[0][1] = SO3_centers[3][1] + flags[1] * m1 * d_new / (sqrt(1 + m1 * m1));
    }

    if (SO3_centers[1][0] == SO3_centers[3][0])
    {
        SO3_centers[1][0] = SO3_centers[3][0];
        SO3_centers[1][1] = SO3_centers[3][1] + flags[3] * d_new;
    }
    else
    {
        double m2 = abs((SO3_centers[1][1] - SO3_centers[3][1]) / (SO3_centers[1][0] - SO3_centers[3][0]));
        SO3_centers[1][0] = SO3_centers[3][0] + flags[2] * d_new / (sqrt(1 + m2 * m2));
        SO3_centers[1][1] = SO3_centers[3][1] + flags[3] * m2 * d_new / (sqrt(1 + m2 * m2));
    }

    if (SO3_centers[2][0] == SO3_centers[3][0])
    {
        SO3_centers[2][0] = SO3_centers[3][0];
        SO3_centers[2][1] = SO3_centers[3][1] + flags[5] * d_new;
    }
    else
    {
        double m3 = abs((SO3_centers[2][1] - SO3_centers[3][1]) / (SO3_centers[2][0] - SO3_centers[3][0]));
        SO3_centers[2][0] = SO3_centers[3][0] + flags[4] * d_new / (sqrt(1 + m3 * m3));
        SO3_centers[2][1] = SO3_centers[3][1] + flags[5] * m3 * d_new / (sqrt(1 + m3 * m3));
    }
    for (int i = 0; i < 4; i++)
    {
        SO3_radii[i] *= scale;
    }
    draw_SO3(SO3_centers, SO3_radii, SO3_colors);
    glFlush();
}

void displayMe(void)
{

    glClear(GL_COLOR_BUFFER_BIT);
    // glClearColor(1.0, 1.0, 1.0, 0.0);

    // draw_SO3(SO3_centers, SO3_radii, SO3_colors);

    draw_sphere(c);

    glFlush();
}

void rotate_SO3(double angle)
{
    glClear(GL_COLOR_BUFFER_BIT);

    double xc = SO3_centers[3][0];
    double yc = SO3_centers[3][1];

    for (int i = 0; i < 3; i++)
    {
        SO3_centers[i][0] -= xc;
        SO3_centers[i][1] -= yc;
    }

    for (int i = 0; i < 3; i++)
    {
        double x = SO3_centers[i][0];
        double y = SO3_centers[i][1];

        SO3_centers[i][0] = x * cos(angle) - y * sin(angle);
        SO3_centers[i][1] = x * sin(angle) + y * cos(angle);
    }

    for (int i = 0; i < 3; i++)
    {
        SO3_centers[i][0] += xc;
        SO3_centers[i][1] += yc;
    }

    draw_SO3(SO3_centers, SO3_radii, SO3_colors);
    glFlush();
}

// Get Co-Ordinates after Mouse Click
void mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN)
    {
        FinalX = x;
        FinalY = y;
    }
}

// Mouse Rotation function
void mouse_move(int x, int y)
{
    // Calculate mouse position change
    int delta_x = x - FinalX;

    // Rotate the figure
    double angle = delta_x * 0.05f;
    rotate_SO3(angle);

    // Change Final Mouse Position
    FinalX = x;
    FinalY = y;
}

void keyUser(unsigned char key, int x, int y)
{
    if (key == 'a' || key == 'A')
    {
        cout << "Key pressed: A\n";
        translate_SO3('a');
    }
    if (key == 'w' || key == 'W')
    {
        cout << "Key pressed: W\n";
        translate_SO3('w');
    }
    if (key == 's' || key == 'S')
    {
        cout << "Key pressed: S\n";
        translate_SO3('s');
    }
    if (key == 'd' || key == 'D')
    {
        cout << "Key pressed: D\n";
        translate_SO3('d');
    }
    if (key == 'i' || key == 'I')
    {
        cout << "Key pressed: I\n";
        scale('i');
    }
    if (key == 'o' || key == 'O')
    {
        cout << "Key pressed: O\n";
        scale('o');
    }
}

signed main(int argc, char **argv)
{
    cout << "Menu: \n";
    cout << "Key     Action \n";
    cout << "D:      Right Translation\n";
    cout << "A:      Left Translation\n";
    cout << "W:      Up Translation\n";
    cout << "S:      Down Translation\n";
    cout << "I:      Zoom In\n";
    cout << "O:      Zoom Out\n\n";

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Window");
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500, 500, -500, 500);
    glutDisplayFunc(displayMe);
    glutKeyboardFunc(keyUser);
    glutMotionFunc(mouse_move);
    glutMouseFunc(mouse);
    glutMainLoop();
}