#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;
#define double double
vector<pair<double, double>> points;

#define X .525731112119133606
#define Z .850650808352039932

static GLfloat vdata[12][3] =
    {
        {-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z}, {0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X}, {Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0}};

static GLushort tindices[20][3] =
    {
        {0, 4, 1}, {0, 9, 4}, {9, 5, 4}, {4, 5, 8}, {4, 8, 1}, {8, 10, 1}, {8, 3, 10}, {5, 3, 8}, {5, 2, 3}, {2, 7, 3}, {7, 10, 3}, {7, 6, 10}, {7, 11, 6}, {11, 0, 6}, {0, 1, 6}, {6, 1, 10}, {9, 0, 11}, {9, 11, 2}, {9, 2, 5}, {7, 2, 11}};

void glVertex3ff(double x, double y, double z)
{
    glVertex3f(x * 10, y * 10, z * 10);
}
void displayMe(void)
{

    glClear(GL_COLOR_BUFFER_BIT);
    m_vertexBufferHandle = (GLuint *)malloc(sizeof(GLuint) * m_numberOfVertexBuffers);
    m_indexBufferHandle = (GLuint *)malloc(sizeof(GLuint) * m_numberOfVertexBuffers);
    m_numberOfIndicesForBuffers = (unsigned int *)malloc(sizeof(unsigned int) * m_numberOfVertexBuffers);

    unsigned int bufferIndex;
    for (bufferIndex = 0; bufferIndex < m_numberOfVertexBuffers; bufferIndex++)
    {
        glGenBuffers(1, &m_indexBufferHandle[bufferIndex]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferHandle[bufferIndex]);

        NSData *currentIndexBuffer = [m_indexArrays objectAtIndex:bufferIndex];
        GLushort *indexBuffer = (GLushort *)[currentIndexBuffer bytes];
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, [currentIndexBuffer length], indexBuffer, GL_STATIC_DRAW);
        m_numberOfIndicesForBuffers[bufferIndex] = ([currentIndexBuffer length] / sizeof(GLushort));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    [m_indexArray release];
    m_indexArray = nil;
    [m_indexArrays release];

    for (bufferIndex = 0; bufferIndex < m_numberOfVertexBuffers; bufferIndex++)
    {
        glGenBuffers(1, &m_vertexBufferHandle[bufferIndex]);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferHandle[bufferIndex]);

        NSData *currentVertexBuffer = [m_vertexArrays objectAtIndex:bufferIndex];
        GLfixed *vertexBuffer = (GLfixed *)[currentVertexBuffer bytes];
        glBufferData(GL_ARRAY_BUFFER, [currentVertexBuffer length], vertexBuffer, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    [m_vertexArray release];
    m_vertexArray = nil;
    [m_vertexArrays release];
    glFlush();
}

signed main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Window");
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // gluOrtho2D(-500, 500, -500, 500);
    glutDisplayFunc(displayMe);
    // glutKeyboardFunc(keyUser);
    // glutMotionFunc(mouse_move);
    // glutMouseFunc(mouse);
    glutMainLoop();
}