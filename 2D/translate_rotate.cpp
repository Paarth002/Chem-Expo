#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;
#define double double
vector<pair<double, double>> points;

double FinalX = 0.0;
double FinalY = 0.0;
int n;

// Translate polygon
void translate(vector<pair<double, double>> &points, char key)
{

    glClear(GL_COLOR_BUFFER_BIT);
    double x = 10;

    glBegin(GL_POLYGON);
    if (key == 'w')
    {
        for (int i = 0; i < n; i++)
        {
            points[i].second += x;
        }
    }
    else if (key == 'a')
    {
        for (int i = 0; i < n; i++)
        {
            points[i].first -= x;
        }
    }
    else if (key == 's')
    {
        for (int i = 0; i < n; i++)
        {
            points[i].second -= x;
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            points[i].first += x;
        }
    }
    for (int i = 0; i < n; i++)
    {
        glVertex2f(points[i].first, points[i].second);
    }
    glEnd();
    glFlush();
}

// Scale Polygon along its center
void scale(vector<pair<double, double>> &points, char zoom)
{
    double scale;
    glClear(GL_COLOR_BUFFER_BIT);

    if (zoom == 'i')
    {
        scale = 1.05;
    }
    else
        scale = 0.95;
    // glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);

    double xc = 0, yc = 0;

    for (int i = 0; i < n; i++)
    {
        xc += points[i].first;
        yc += points[i].second;
    }
    xc /= n;
    yc /= n;

    for (int i = 0; i < n; i++)
    {
        points[i].first -= xc;
        points[i].second -= yc;
        points[i].first *= scale;
        points[i].second *= scale;
        points[i].first += xc;
        points[i].second += yc;
        glVertex2f(points[i].first, points[i].second);
    }
    glEnd();
    glFlush();
}

// Rotate polygon around origin
void rotate(double angle, vector<pair<double, double>> &points)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++)
    {
        float x = points[i].first;
        float y = points[i].second;
        points[i].first = x * cos(angle) - y * sin(angle);
        points[i].second = x * sin(angle) + y * cos(angle);
        glVertex2f(points[i].first, points[i].second);
    }
    glEnd();
    glFlush();
}

void displayMe(void)
{

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);

    for (int i = 0; i < n; i++)
    {
        glVertex2f(points[i].first, points[i].second);
    }

    glEnd();

    glBegin(GL_POINTS);             // starts drawing of points
    glVertex3f(1.0f, 1.0f, 0.0f);   // upper-right corner
    glVertex3f(-1.0f, -1.0f, 0.0f); // lower-left corner
    // glVe
    glEnd();
    // /
    // info();
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
    rotate(angle, points);

    // Change Final Mouse Position
    FinalX = x;
    FinalY = y;
}

void keyUser(unsigned char key, int x, int y)
{
    if (key == 'a' || key == 'A')
    {
        cout << "Key pressed: A\n";
        translate(points, 'a');
    }
    if (key == 'w' || key == 'W')
    {
        cout << "Key pressed: W\n";
        translate(points, 'w');
    }
    if (key == 's' || key == 'S')
    {
        cout << "Key pressed: S\n";
        translate(points, 's');
    }
    if (key == 'd' || key == 'D')
    {
        cout << "Key pressed: D\n";
        translate(points, 'd');
    }
    if (key == 'i' || key == 'I')
    {
        cout << "Key pressed: I\n";
        scale(points, 'i');
    }
    if (key == 'o' || key == 'O')
    {
        cout << "Key pressed: O\n";
        scale(points, 'o');
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
    cout << "Enter number of vertices:";

    cin >> n;
    cout << "Enter vertices:\n";
    for (int i = 0; i < n; i++)
    {
        pair<double, double> xy;
        cin >> xy.first;
        cin >> xy.second;
        points.push_back(xy);
    }

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
    // glutMotionFunc(mouse_move);
    // glutMouseFunc(mouse);
    glutMainLoop();
}