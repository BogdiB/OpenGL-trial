#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>

float xPosition = 0.0;
float yPosition = 0.0;
// left is 0, right is 1
bool dirH = 0;
// down is 0, up is 1
bool dirV = 0;
bool ok = 0;
// in coordinates
float movementSpeed = 0.2;

void displayer()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glBegin(GL_QUADS);
    glVertex2f(xPosition, yPosition + 2.0);
    glVertex2f(xPosition, yPosition);
    glVertex2f(xPosition + 2.0, yPosition);
    glVertex2f(xPosition + 2.0, yPosition + 2.0);
    glEnd();

        if (dirH == 1 && ok == 0)
        {
            xPosition += movementSpeed;
            if (xPosition + 2 > 10)
            {
                dirH = !dirH;
                ok = 1;
            }
        }
        else if (dirH == 0 && ok == 0)
        {
            xPosition -= movementSpeed;
            if (xPosition < -10)
            {
                dirH = !dirH;
                ok = 1;
            }
        }
        if (dirV == 1 && ok == 1)
        {
            yPosition += movementSpeed;
            if (yPosition + 2 > 10)
            {
                dirV = !dirV;
                ok = 0;
            }
        }
        else if (dirV == 0 && ok == 1)
        {
            yPosition -= movementSpeed;
            if (yPosition < -10)
            {
                dirV = !dirV;
                ok = 0;
            }
        }

    glutSwapBuffers();
}

void reshaper(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-10, 10, -10, 10);
    glMatrixMode(GL_MODELVIEW);
}

void framerate(int)
{
    // refresh display - draw again
    glutPostRedisplay();
    // 60 frames per 1000ms
    glutTimerFunc(1000 / 60, framerate, 0);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("Gura Matei");

    glutDisplayFunc(displayer);
    glutReshapeFunc(reshaper);
    glutTimerFunc(0, framerate, 0);

    glClearColor(0.5, 0.0, 0.0, 1.0);

    glutMainLoop();

    return 0;
}
