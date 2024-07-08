#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <ctime>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


const float PI = 3.14159;

const int NUM_ORBITING_SPHERES = 5;
const float ORBIT_RADII[NUM_ORBITING_SPHERES] = { 2.0f, 3.5f, 4.5f, 5.8f, 6.4f };
const float ORBIT_SPEEDS[NUM_ORBITING_SPHERES] = { 0.07f, 0.05f, 0.06f, 0.05f, 0.09f };

float orbitAngles[NUM_ORBITING_SPHERES] = { 7.0f, -5.0f, 3.0f, 4.2f, -9.0f };

GLuint sunTextureID;
GLuint textureIDs[NUM_ORBITING_SPHERES];


void drawCelestialObject(float radius, GLuint textureID)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    GLUquadricObj* quadObj = gluNewQuadric();
    gluQuadricNormals(quadObj, GLU_SMOOTH);
    gluQuadricTexture(quadObj, GL_TRUE); // enable texture coordinates
    gluSphere(quadObj, radius, 20, 20);
    gluDeleteQuadric(quadObj);

    glDisable(GL_TEXTURE_2D);
}


GLuint loadTexture(const char* filename)
{
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true); // textures are loaded in correct orientation
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);
    if (!data)
    {
        std::cout << "No texture: " << filename;
        exit(1);
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, channels == 4 ? GL_RGBA : GL_RGB, width, height, 0, channels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);

    return textureID;
}

void generateTextures()
{
    sunTextureID = loadTexture("C:\\Users\\Bogdan\\Documents\\CodeBlocks\\testglut\\sun.jpeg");
    textureIDs[0] = loadTexture("C:\\Users\\Bogdan\\Documents\\CodeBlocks\\testglut\\talk.jpg");
    textureIDs[1] = loadTexture("C:\\Users\\Bogdan\\Documents\\CodeBlocks\\testglut\\round_thing.jpg");
    textureIDs[2] = loadTexture("C:\\Users\\Bogdan\\Documents\\CodeBlocks\\testglut\\shop.jpg");
    textureIDs[3] = loadTexture("C:\\Users\\Bogdan\\Documents\\CodeBlocks\\testglut\\sign.jpg");
    textureIDs[4] = loadTexture("C:\\Users\\Bogdan\\Documents\\CodeBlocks\\testglut\\cloud.jpg");
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // lighting
    GLfloat light_position[] = { 0.0f, 0.0f, -4.0f, 1.0f }; // light position = same position as sun
    GLfloat light_color[] = { 0.3f, 0.3f, 0.0f, 0.5f }; // light color
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
    glEnable(GL_COLOR_MATERIAL);

    // sun
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, sunTextureID);
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0.0f, 0.0f, -5.0f); // move away from camera
    glScalef(0.5f, 0.5f, 0.5f); // scale down
    drawCelestialObject(1.0f, sunTextureID);
    glDisable(GL_TEXTURE_2D);

    // planets
    for (int i = 0; i < NUM_ORBITING_SPHERES; ++i)
    {
        // calculate planet position
        float y = 0.0f;
        float x;
        float z = ORBIT_RADII[i] * sin(orbitAngles[i]);
        if (i != 0)
        {
            x = ORBIT_RADII[i] * cos(orbitAngles[i]);
            if (i % 2 == 0)
                y = cos(orbitAngles[i]);
            else
                y = sin(orbitAngles[i]);
        }
        else
            x = (ORBIT_RADII[i] + 5.0f) * cos(orbitAngles[i]);

        glPushMatrix();
        glTranslatef(x, y, z); // move to calculated position
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // rotate texture coordinates to align with sphere
        drawCelestialObject(0.2f + (i % 2 == 0 ? (float) i / 15 : -((float) i / 30)), textureIDs[i]);
        glPopMatrix();

        // angle for next frame
        orbitAngles[i] += ORBIT_SPEEDS[i];
    }

    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void framerate(int)
{
    // refresh display - draw again
    glutPostRedisplay();
    // 45 frames per 1000ms
    glutTimerFunc(1000 / 45, framerate, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1500, 700);
    glutCreateWindow("Taci Matei");

    glEnable(GL_DEPTH_TEST);

    generateTextures();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, framerate, 0);

    glutMainLoop();
    return 0;
}
