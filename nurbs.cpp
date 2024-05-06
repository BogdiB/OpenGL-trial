#include <GL/freeglut.h>
#include <cmath>

const float range = 7.0f;
const int sections = 1000;

void init()
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  gluPerspective(45.0, 1.0, 0.1, 100.0);
  glMatrixMode(GL_MODELVIEW);
}

float comp_height(float x, float y)
{
  return sinf(x) * cosf(y);
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt(10, 10, 5, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0);
  glBegin(GL_LINES);

  for (int i = 0; i < sections; i++) {
    for (int j = 0; j < sections; j++) {

      // start positions
      float start_x = range * (i / (float)sections);
      float start_y = range * (j / (float)sections);
      float start_z = comp_height(start_x, start_y);

      float x1 = range * ((i + 1) / (float)sections);
      float z1 = comp_height(x1, start_y);

      float y2 = range * ((j + 1) / (float)sections);
      float z2 = comp_height(start_x, y2);

      // draw lines in x direction
      glColor3f(1.0, 0.0, 1.0);
      glVertex3f(start_x, start_y, start_z);
      glVertex3f(x1, start_y, z1);

      // draw lines in y direction
      glColor3f(1.0, 1.0, 0.0);
      glVertex3f(start_x, start_y, start_z);
      glVertex3f(start_x, y2, z2);
    }
  }

  glEnd();
  glutSwapBuffers();
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Taci Matei");
  init();
  
  glutDisplayFunc(display);
  glutMainLoop();

  return 0;
}
