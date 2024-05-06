#include <GL/glut.h>

float xlightpos = 1.0;
bool side = true;

void init() {
    glEnable(GL_DEPTH_TEST); // depth testing for 3D rendering
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL); // color tracking for materials

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f); // bg colour
}

// Function to set up the camera
void setupCamera() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 800.0 / 600.0, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2.0, 2.0, 5.0,  // eye position
              1.0, -0.5, 0.0,  // look-at position
              0.0, 1.0, 0.0); // up vector
}

void yes()
{
    if (xlightpos < -1.0)
        side = true;
    else if (xlightpos >= 1.0)
        side = false;

    if (side)
        xlightpos += 0.001;
    else
        xlightpos -= 0.001;
}

void display() {
    // directional light
    GLfloat light_direction[] = { -1.0f, -1.0f, -1.0f, 0.0f };
    GLfloat light_color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_direction);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);

    // positional light
    GLfloat light_color1[] = { 0.2f, 1.0f, 1.0f, 0.7f };
    GLfloat light_position[] = { xlightpos, 2.0f, 2.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_color1);

    // positional light 2
    GLfloat light_color2[] = { 1.0f, 1.0f, 0.2f, 1.0f };
    GLfloat light_position2[] = { xlightpos, -2.0f, -2.0f, -1.0f };
    glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_color2);


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    setupCamera();

    glColor3f(1.0f, 0.0f, 0.0f);
    glutSolidCube(0.5);

    glColor3f(0.0f, 1.0f, 0.0f);
    glTranslatef(1.5f, 0.0f, 0.0f);
    glutSolidSphere(0.3, 32, 32);

    glColor3f(0.0f, 0.0f, 1.0f);
    glTranslatef(-1.5f, -1.5f, 0.0f);
    glutSolidCube(0.3);

    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(1.5f, 0.0f, 0.0f);
    glutSolidTeapot(0.3);


    // light balls to show where the light is coming from
    glColor3f(1.0f, 1.0f, 0.0f);
    glTranslatef(xlightpos, 2.0f, 2.0f);
    glutSolidSphere(0.05, 16, 16);

    glColor3f(1.0f, 1.0f, 0.0f);
    glTranslatef(xlightpos, -2.0f, -2.0f);
    glutSolidSphere(0.05, 16, 16);

    yes();


    glFlush();
    glutPostRedisplay();
}

void update(int value) {
    yes();

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Example");
    init();

    glutDisplayFunc(display);
    glutTimerFunc(16, update, 0);

    glutMainLoop();

    return 0;
}
