#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;

double FinalX = 0.0;
double FinalY = 0.0;

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

// h20
double H2O_centers[3][2] = {{-950, -200}, {-800, 0}, {-650, -200}};
color H2O_colors[] = {blue, red, blue};
double H2O_radii[3] = {25, 50, 25};

// so3
// double SO3_centers[4][2] = {{-450, -200}, {-150, -200}, {-300, 59.8}, {-300, -113.4}};
double SO3_centers[4][2] = {{300, 0}, {0, 0}, {150, 259.8}, {150, 86.3}};
color SO3_colors[4] = {red, red, red, yellow};
double SO3_radii[4] = {50, 50, 50, 100};

// h2so4
double H2SO4_centers[7][2] = {{100, 0}, {300, 0}, {500, 0}, {193.94, 106.06}, {406.06, 106.06}, {406.06, -106.06}, {193.94, -106.06}};
color H2SO4_colors[7] = {blue, yellow, blue, red, red, red, red};
double H2SO4_radii[7] = {25, 50, 25, 25, 25, 25, 25};

// plus symbol
double plus_center[1][2] = {{-550, 0}};
color plus_colors[2] = {white, magenta};

// reaction equal symbol
double equal_center[1][2] = {{-100, 0}};
color equal_colors[2] = {white, magenta};

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

void draw_plus(double centers[1][2], color colors[2])
{
    glBegin(GL_LINES);
    glColor3f(colors[0].r, colors[0].g, colors[0].b);
    glVertex2f(centers[0][0] - 50, centers[0][1]);
    glVertex2f(centers[0][0] + 50, centers[0][1]);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(colors[1].r, colors[1].g, colors[1].b);
    glVertex2f(centers[0][0], centers[0][1] - 50);
    glVertex2f(centers[0][0], centers[0][1] + 50);
    glEnd();
}

void draw_equal(double centers[1][2], color colors[2])
{
    glBegin(GL_LINES);
    glColor3f(colors[0].r, colors[0].g, colors[0].b);
    glVertex2f(centers[0][0] - 50, centers[0][1]);
    glVertex2f(centers[0][0] + 50, centers[0][1]);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(colors[1].r, colors[1].g, colors[1].b);
    glVertex2f(centers[0][0], centers[0][1] + 50);
    glVertex2f(centers[0][0] + 50, centers[0][1]);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(colors[1].r, colors[1].g, colors[1].b);
    glVertex2f(centers[0][0], centers[0][1] - 50);
    glVertex2f(centers[0][0] + 50, centers[0][1]);
    glEnd();
}

void draw_H2O(double centers[3][2], double radii[3], color colors[3])
{
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(centers[0][0], centers[0][1]);
    glVertex2f(centers[1][0], centers[1][1]);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(centers[1][0], centers[1][1]);
    glVertex2f(centers[2][0], centers[2][1]);
    glEnd();

    for (int i = 0; i < 3; i++)
    {
        draw_circle(centers[i][0], centers[i][1], radii[i], colors[i]);
    }
    draw_plus(plus_center, plus_colors);
    draw_equal(equal_center, equal_colors);
}

void draw_SO3(double centers[4][2], double radii[4], color colors[4])
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
    draw_plus(plus_center, plus_colors);
    draw_equal(equal_center, equal_colors);
}

void draw_H2SO4(double centers[7][2], double radii[7], color colors[7])
{
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);

    for (int k = 0; k < 7; k++)
    {
        glVertex2f(centers[1][0], centers[1][1]);
        glVertex2f(centers[k][0], centers[k][1]);
    }

    glEnd();

    for (int k = 0; k < 7; k++)
    {
        draw_circle(centers[k][0], centers[k][1], radii[k], colors[k]);
    }
    draw_plus(plus_center, plus_colors);
    draw_equal(equal_center, equal_colors);
}

void translate_H2O(char key)
{
    int n = 3;
    glClear(GL_COLOR_BUFFER_BIT);
    double delta = 10;

    if (key == 'w' || key == 'W')
    {
        for (int i = 0; i < n; i++)
        {
            H2O_centers[i][1] += delta;
        }
    }
    else if (key == 'a' || key == 'A')
    {
        for (int i = 0; i < n; i++)
        {
            H2O_centers[i][0] -= delta;
        }
    }
    else if (key == 's' || key == 'S')
    {
        for (int i = 0; i < n; i++)
        {
            H2O_centers[i][1] -= delta;
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            H2O_centers[i][0] += delta;
        }
    }
    draw_H2O(H2O_centers, H2O_radii, H2O_colors);
}

void translate_SO3(char key)
{
    int n = 4;
    glClear(GL_COLOR_BUFFER_BIT);
    double delta = 10;

    if (key == 'Y' || key == 'y')
    {
        for (int i = 0; i < n; i++)
        {
            SO3_centers[i][1] += delta;
        }
    }
    else if (key == 'G' || key == 'g')
    {
        for (int i = 0; i < n; i++)
        {
            SO3_centers[i][0] -= delta;
        }
    }
    else if (key == 'h' || key == 'H')
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
}

void translate_H2SO4(char key)
{
    int n = 7;
    glClear(GL_COLOR_BUFFER_BIT);
    double delta = 10;

    if (key == '8')
    {
        for (int i = 0; i < n; i++)
        {
            H2SO4_centers[i][1] += delta;
        }
    }
    else if (key == '4')
    {
        for (int i = 0; i < n; i++)
        {
            H2SO4_centers[i][0] -= delta;
        }
    }
    else if (key == '5')
    {
        for (int i = 0; i < n; i++)
        {
            H2SO4_centers[i][1] -= delta;
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            H2SO4_centers[i][0] += delta;
        }
    }
    draw_H2SO4(H2SO4_centers, H2SO4_radii, H2SO4_colors);
}

// scale_H20 Polygon along its center
void scale_H2O(char zoom)
{
    double scale_H20;
    glClear(GL_COLOR_BUFFER_BIT);

    if (zoom == 'q' || zoom == 'Q')
    {
        scale_H20 = 1.05;
    }
    else
        scale_H20 = 0.95;

    double d_old_1 = sqrt(pow(H2O_centers[0][0] - H2O_centers[1][0], 2) + pow(H2O_centers[0][1] - H2O_centers[1][1], 2));
    double d_old_2 = sqrt(pow(H2O_centers[1][0] - H2O_centers[2][0], 2) + pow(H2O_centers[1][1] - H2O_centers[2][1], 2));
    double d_new_1 = scale_H20 * d_old_1;
    double d_new_2 = scale_H20 * d_old_2;

    int flags[4] = {1, 1, 1, 1};
    if (H2O_centers[0][0] < H2O_centers[1][0])
        flags[0] = -1;
    if (H2O_centers[0][1] < H2O_centers[1][1])
        flags[1] = -1;
    if (H2O_centers[2][0] < H2O_centers[1][0])
        flags[2] = -1;
    if (H2O_centers[2][1] < H2O_centers[1][1])
        flags[3] = -1;

    if (H2O_centers[0][0] == H2O_centers[1][0])
    {
        H2O_centers[0][0] = H2O_centers[1][0];
        H2O_centers[0][1] = H2O_centers[1][1] + flags[1] * d_new_1;
    }
    else
    {
        double m1 = abs((H2O_centers[0][1] - H2O_centers[1][1]) / (H2O_centers[0][0] - H2O_centers[1][0]));
        H2O_centers[0][0] = H2O_centers[1][0] + flags[0] * d_new_1 / (sqrt(1 + m1 * m1));
        H2O_centers[0][1] = H2O_centers[1][1] + flags[1] * m1 * d_new_1 / (sqrt(1 + m1 * m1));
    }

    if (H2O_centers[2][0] == H2O_centers[1][0])
    {
        H2O_centers[2][0] = H2O_centers[1][0];
        H2O_centers[2][1] = H2O_centers[1][1] + flags[3] * d_new_2;
    }
    else
    {
        double m2 = abs((H2O_centers[2][1] - H2O_centers[1][1]) / (H2O_centers[2][0] - H2O_centers[1][0]));
        H2O_centers[2][0] = H2O_centers[1][0] + flags[2] * d_new_2 / (sqrt(1 + m2 * m2));
        H2O_centers[2][1] = H2O_centers[1][1] + flags[3] * m2 * d_new_2 / (sqrt(1 + m2 * m2));
    }

    for (int i = 0; i < 3; i++)
    {
        H2O_radii[i] *= scale_H20;
    }
    draw_H2O(H2O_centers, H2O_radii, H2O_colors);
}

void scale_SO3(char zoom)
{
    double scale_SO3;
    glClear(GL_COLOR_BUFFER_BIT);

    if (zoom == 't' || zoom == 'T')
    {
        scale_SO3 = 1.05;
    }
    else
        scale_SO3 = 0.95;

    double d_old = sqrt(pow(SO3_centers[0][0] - SO3_centers[3][0], 2) + pow(SO3_centers[0][1] - SO3_centers[3][1], 2));
    double d_new = scale_SO3 * d_old;

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
        SO3_radii[i] *= scale_SO3;
    }
    draw_SO3(SO3_centers, SO3_radii, SO3_colors);
}

void scale_h2so4(char zoom)
{
    double scale_h2so4;
    glClear(GL_COLOR_BUFFER_BIT);

    if (zoom == '7')
    {
        scale_h2so4 = 1.05;
    }
    else
        scale_h2so4 = 0.95;

    double d_old_1 = sqrt(pow(H2SO4_centers[0][0] - H2SO4_centers[1][0], 2) + pow(H2SO4_centers[0][1] - H2SO4_centers[1][1], 2));
    double d_old_2 = sqrt(pow(H2SO4_centers[1][0] - H2SO4_centers[3][0], 2) + pow(H2SO4_centers[1][1] - H2SO4_centers[3][1], 2));
    double d_new_1 = scale_h2so4 * d_old_1;
    double d_new_2 = scale_h2so4 * d_old_2;

    int flags[12];
    for (int k = 0; k < 12; k++)
    {
        flags[k] = 1;
    }
    if (H2SO4_centers[0][0] < H2SO4_centers[1][0])
        flags[0] = -1;
    if (H2SO4_centers[0][1] < H2SO4_centers[1][1])
        flags[1] = -1;
    if (H2SO4_centers[2][0] < H2SO4_centers[1][0])
        flags[2] = -1;
    if (H2SO4_centers[2][1] < H2SO4_centers[1][1])
        flags[3] = -1;
    if (H2SO4_centers[3][0] < H2SO4_centers[1][0])
        flags[4] = -1;
    if (H2SO4_centers[3][1] < H2SO4_centers[1][1])
        flags[5] = -1;
    if (H2SO4_centers[4][0] < H2SO4_centers[1][0])
        flags[6] = -1;
    if (H2SO4_centers[4][1] < H2SO4_centers[1][1])
        flags[7] = -1;
    if (H2SO4_centers[5][0] < H2SO4_centers[1][0])
        flags[8] = -1;
    if (H2SO4_centers[5][1] < H2SO4_centers[1][1])
        flags[9] = -1;
    if (H2SO4_centers[6][0] < H2SO4_centers[1][0])
        flags[10] = -1;
    if (H2SO4_centers[6][1] < H2SO4_centers[1][1])
        flags[11] = -1;

    if (H2SO4_centers[0][0] == H2SO4_centers[1][0])
    {
        H2SO4_centers[0][0] = H2SO4_centers[1][0];
        H2SO4_centers[0][1] = H2SO4_centers[1][1] + flags[1] * d_new_1;
    }
    else
    {
        double m1 = abs((H2SO4_centers[0][1] - H2SO4_centers[1][1]) / (H2SO4_centers[0][0] - H2SO4_centers[1][0]));
        H2SO4_centers[0][0] = H2SO4_centers[1][0] + flags[0] * d_new_1 / (sqrt(1 + m1 * m1));
        H2SO4_centers[0][1] = H2SO4_centers[1][1] + flags[1] * m1 * d_new_1 / (sqrt(1 + m1 * m1));
    }

    if (H2SO4_centers[2][0] == H2SO4_centers[1][0])
    {
        H2SO4_centers[2][0] = H2SO4_centers[1][0];
        H2SO4_centers[2][1] = H2SO4_centers[1][1] + flags[3] * d_new_1;
    }
    else
    {
        double m2 = abs((H2SO4_centers[2][1] - H2SO4_centers[1][1]) / (H2SO4_centers[2][0] - H2SO4_centers[1][0]));
        H2SO4_centers[2][0] = H2SO4_centers[1][0] + flags[2] * d_new_1 / (sqrt(1 + m2 * m2));
        H2SO4_centers[2][1] = H2SO4_centers[1][1] + flags[3] * m2 * d_new_1 / (sqrt(1 + m2 * m2));
    }

    if (H2SO4_centers[3][0] == H2SO4_centers[1][0])
    {
        H2SO4_centers[3][0] = H2SO4_centers[1][0];
        H2SO4_centers[3][1] = H2SO4_centers[1][1] + flags[5] * d_new_2;
    }
    else
    {
        double m3 = abs((H2SO4_centers[3][1] - H2SO4_centers[1][1]) / (H2SO4_centers[3][0] - H2SO4_centers[1][0]));
        H2SO4_centers[3][0] = H2SO4_centers[1][0] + flags[4] * d_new_2 / (sqrt(1 + m3 * m3));
        H2SO4_centers[3][1] = H2SO4_centers[1][1] + flags[5] * m3 * d_new_2 / (sqrt(1 + m3 * m3));
    }

    if (H2SO4_centers[4][0] == H2SO4_centers[1][0])
    {
        H2SO4_centers[4][0] = H2SO4_centers[1][0];
        H2SO4_centers[4][1] = H2SO4_centers[1][1] + flags[7] * d_new_2;
    }
    else
    {
        double m4 = abs((H2SO4_centers[4][1] - H2SO4_centers[1][1]) / (H2SO4_centers[4][0] - H2SO4_centers[1][0]));
        H2SO4_centers[4][0] = H2SO4_centers[1][0] + flags[6] * d_new_2 / (sqrt(1 + m4 * m4));
        H2SO4_centers[4][1] = H2SO4_centers[1][1] + flags[7] * m4 * d_new_2 / (sqrt(1 + m4 * m4));
    }

    if (H2SO4_centers[5][0] == H2SO4_centers[1][0])
    {
        H2SO4_centers[5][0] = H2SO4_centers[1][0];
        H2SO4_centers[5][1] = H2SO4_centers[1][1] + flags[9] * d_new_2;
    }
    else
    {
        double m5 = abs((H2SO4_centers[5][1] - H2SO4_centers[1][1]) / (H2SO4_centers[5][0] - H2SO4_centers[1][0]));
        H2SO4_centers[5][0] = H2SO4_centers[1][0] + flags[8] * d_new_2 / (sqrt(1 + m5 * m5));
        H2SO4_centers[5][1] = H2SO4_centers[1][1] + flags[9] * m5 * d_new_2 / (sqrt(1 + m5 * m5));
    }

    if (H2SO4_centers[6][0] == H2SO4_centers[1][0])
    {
        H2SO4_centers[6][0] = H2SO4_centers[1][0];
        H2SO4_centers[6][1] = H2SO4_centers[1][1] + flags[11] * d_new_2;
    }
    else
    {
        double m6 = abs((H2SO4_centers[6][1] - H2SO4_centers[1][1]) / (H2SO4_centers[6][0] - H2SO4_centers[1][0]));
        H2SO4_centers[6][0] = H2SO4_centers[1][0] + flags[10] * d_new_2 / (sqrt(1 + m6 * m6));
        H2SO4_centers[6][1] = H2SO4_centers[1][1] + flags[11] * m6 * d_new_2 / (sqrt(1 + m6 * m6));
    }

    for (int i = 0; i < 7; i++)
    {
        H2SO4_radii[i] *= scale_h2so4;
    }
    draw_H2SO4(H2SO4_centers, H2SO4_radii, H2SO4_colors);
}

void rotate_H2O(double angle)
{
    glClear(GL_COLOR_BUFFER_BIT);

    double xc = H2O_centers[1][0];
    double yc = H2O_centers[1][1];

    for (int i = 0; i < 3; i++)
    {
        H2O_centers[i][0] -= xc;
        H2O_centers[i][1] -= yc;
    }

    for (int i = 0; i < 3; i++)
    {
        double x = H2O_centers[i][0];
        double y = H2O_centers[i][1];

        H2O_centers[i][0] = x * cos(angle) - y * sin(angle);
        H2O_centers[i][1] = x * sin(angle) + y * cos(angle);
    }

    for (int i = 0; i < 3; i++)
    {
        H2O_centers[i][0] += xc;
        H2O_centers[i][1] += yc;
    }

    draw_H2O(H2O_centers, H2O_radii, H2O_colors);
}

void rotate_SO3(double angle)
{
    // glClear(GL_COLOR_BUFFER_BIT);

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
}

void rotate_H2SO4(double angle)
{
    // glClear(GL_COLOR_BUFFER_BIT);

    double xc = H2SO4_centers[1][0];
    double yc = H2SO4_centers[1][1];

    for (int i = 0; i < 7; i++)
    {
        H2SO4_centers[i][0] -= xc;
        H2SO4_centers[i][1] -= yc;
    }

    for (int i = 0; i < 7; i++)
    {
        double x = H2SO4_centers[i][0];
        double y = H2SO4_centers[i][1];

        H2SO4_centers[i][0] = x * cos(angle) - y * sin(angle);
        H2SO4_centers[i][1] = x * sin(angle) + y * cos(angle);
    }

    for (int i = 0; i < 7; i++)
    {
        H2SO4_centers[i][0] += xc;
        H2SO4_centers[i][1] += yc;
    }

    draw_H2SO4(H2SO4_centers, H2SO4_radii, H2SO4_colors);
}

void displayMe(void)
{

    glClear(GL_COLOR_BUFFER_BIT);
    // glClearColor(1.0, 1.0, 1.0, 0.0);

    draw_H2O(H2O_centers, H2O_radii, H2O_colors);
    draw_plus(plus_center, plus_colors);
    draw_SO3(SO3_centers, SO3_radii, SO3_colors);
    draw_equal(equal_center, equal_colors);
    draw_H2SO4(H2SO4_centers, H2SO4_radii, H2SO4_colors);

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
    rotate_H2O(angle);
    rotate_SO3(angle);
    rotate_H2SO4(angle);
    glFlush();

    // Change Final Mouse Position
    FinalX = x;
    FinalY = y;
}

void keyUser(unsigned char key, int x, int y)
{
    if (key == 'w' || key == 'W' || key == 'A' || key == 'a' || key == 's' || key == 'S' || key == 'd' || key == 'D')
    {
        cout << "Key pressed: W\n";
        translate_H2O(key);
        draw_SO3(SO3_centers, SO3_radii, SO3_colors);
        draw_H2SO4(H2SO4_centers, H2SO4_radii, H2SO4_colors);
        glFlush();
    }
    if (key == 'y' || key == 'Y' || key == 'j' || key == 'J' || key == 'h' || key == 'H' || key == 'G' || key == 'g')
    {
        cout << "Key pressed: I\n";
        translate_SO3(key);
        draw_H2O(H2O_centers, H2O_radii, H2O_colors);
        draw_H2SO4(H2SO4_centers, H2SO4_radii, H2SO4_colors);
        glFlush();
    }
    if (key == '8' || key == '4' || key == '5' || key == '6')
    {
        cout << "Key pressed: 8\n";
        translate_H2SO4(key);
        draw_H2O(H2O_centers, H2O_radii, H2O_colors);
        draw_SO3(SO3_centers, SO3_radii, SO3_colors);
        glFlush();
    }

    if (key == 'q' || key == 'Q' || key == 'e' || key == 'E')
    {
        cout << "Key pressed: Q\n";
        scale_H2O(key);
        draw_SO3(SO3_centers, SO3_radii, SO3_colors);
        draw_H2SO4(H2SO4_centers, H2SO4_radii, H2SO4_colors);
        glFlush();
    }
    if (key == 't' || key == 'T' || key == 'u' || key == 'U')
    {
        cout << "Key pressed: I\n";
        scale_SO3(key);
        draw_H2O(H2O_centers, H2O_radii, H2O_colors);
        draw_H2SO4(H2SO4_centers, H2SO4_radii, H2SO4_colors);
        glFlush();
    }
    if (key == '7' || key == '9')
    {
        cout << "Key pressed: O\n";
        scale_h2so4(key);
        draw_H2O(H2O_centers, H2O_radii, H2O_colors);
        draw_SO3(SO3_centers, SO3_radii, SO3_colors);
        glFlush();
    }
}

signed main(int argc, char **argv)
{
    cout << "Menu: \n";
    cout << "Key     Action \n";
    cout << "W-A-S-D:      Translation of H2O\n";
    cout << "Y-G-H-L:      Translation of SO3\n";
    cout << "8-4-5-6:      Translation of H2SO4\n";
    cout << "Q-E:          Scaling of H2O\n";
    cout << "T-U:          Scaling of SO3\n";
    cout << "7-9:          Scaling of H2SO4\n";
    cout << "Mouse:        Rotation\n\n";

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(1500, 1500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Window");
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1200, 800, -1000, 1000);
    glutDisplayFunc(displayMe);
    glutKeyboardFunc(keyUser);
    glutMotionFunc(mouse_move);
    glutMouseFunc(mouse);
    glutMainLoop();
}