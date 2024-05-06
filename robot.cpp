#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>

float xPosition = 0.0;
float zPosition = 0.0;
float rot = 0.0;
// left is 0, right is 1
bool dirH = 0;
// down is 0, up is 1
bool dirV = 0;
bool ok = 0;
// in coordinates
float movementSpeed = 0.2;

void keyPressed(unsigned char key, int x, int y)
{
    if ((key == 'w' || key == 'W') && rot < 30)
        ++rot;
    else if ((key == 's' || key == 'S') && rot > -30)
        --rot;
}

void head()
{
    glPushMatrix();

    glTranslatef(0, 0.3, 0);
    glutSolidSphere(0.1, 30, 30);

    glPopMatrix();
}

void body()
{
    glColor3f(1.0, 0.0, 1.0);
    glPushMatrix();

    glScalef(0.5, 1, 0.5);
    glutSolidCube(0.4);

    glPopMatrix();
}

void arms()
{
    // ASSUMING THE ROBOT IS FACING US

    // right arm
    glColor3f(1.0, 1.0, 0.0);
    glPushMatrix();

    glScalef(0.25, 0.5, 0.175);
    glRotatef(rot, 1.0, 0.0, 0.0);
    glTranslatef(-0.6, 0.1, 0);
    glutSolidCube(0.4);

    glPopMatrix();

    // left arm
    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();

    glScalef(0.25, 0.5, 0.175);
    glRotatef(-rot, 1.0, 0.0, 0.0);
    glTranslatef(0.6, 0.1, 0);
    glutSolidCube(0.4);

    glPopMatrix();
}

void legs()
{
    // ASSUMING THE ROBOT IS FACING US

    // right leg
    glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();

    glScalef(0.25, 0.5, 0.175);
    glRotatef(-rot, 1.0, 0.0, 0.0);
    glTranslatef(-0.25, -0.6, 0);
    glutSolidCube(0.4);

    glPopMatrix();

    // left leg
    glColor3f(0.0, 1.0, 0.0);
    glPushMatrix();

    glScalef(0.25, 0.5, 0.175);
    glRotatef(rot, 1.0, 0.0, 0.0);
    glTranslatef(0.25, -0.6, 0);
    glutSolidCube(0.4);

    glPopMatrix();
}

void makeRobot()
{
    head();
    body();
    arms();
    legs();
}

void displayer()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(-3, 0.0, 0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glColor3f(1.0, 1.0, 1.0);
    makeRobot();

    glutSwapBuffers();
}

void reshaper(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat) w / (GLfloat) h, 1.0, 40.0);
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
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("Taci Matei");
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glutKeyboardFunc(keyPressed);

    glutDisplayFunc(displayer);
    glutReshapeFunc(reshaper);
    glutTimerFunc(0, framerate, 0);

    glClearColor(0.0, 0.0, 0.0, 1.0);

    glutMainLoop();

    return 0;
}
