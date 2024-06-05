#include <GL/glew.h>
#include <windows.h>
#include <GL/freeglut.h>
#include <cmath>
#include <string>
#include <iostream>
#include <tchar.h>
#include <io.h>
#include "stb/stb_image.h"
#include "common.h"

#define STB_IMAGE_IMPLEMENTATION

// Global variables
int g_bButton1Down = 0;
float g_fViewDistance = 0.0;
float g_yClick = 0.0;

#define TRUE 1
#define FALSE 0
#define VIEWING_DISTANCE_MIN 1.0

// Button bounds
float buttonX = 200.0f;
float buttonY = 200.0f;
float buttonWidth = 100.0f;
float buttonHeight = 50.0f;

GLuint loadTexture(const char* filename) {
    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (!data) {
        std::cerr << "Failed to load texture: " << filename << std::endl;
        std::cerr << "stbi_failure_reason: " << stbi_failure_reason() << std::endl;
        exit(1);
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, width, height, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);

    return textureID;
}

void drawText(const char *text, float x, float y) {
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(x, y);

    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
        text++;
    }
}

void drawButton(float x, float y, float width, float height) {
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    // Draw button text
    glColor3f(1.0f, 1.0f, 1.0f);
    drawText("Click Me", x + 10.0f, y + 20.0f);
}

void setupDisplay() {
    drawText("Powered By SS", 500.0f, 120.0f);

    // Draw the button
    drawButton(buttonX, buttonY, buttonWidth, buttonHeight);
}

void MouseButton(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        g_bButton1Down = TRUE;
        int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
        y = windowHeight - y;


        if (x >= buttonX && x <= buttonX + buttonWidth && y >= buttonY && y <= buttonY + buttonHeight)
        {
            std::cout << "islevsel" << std::endl;
        }
    }
    else
    {
        g_bButton1Down = FALSE;
    }
}

void MouseMotion(int x, int y)
{
    if (g_bButton1Down)
    {
        glutPostRedisplay();
    }
}

void loddDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, glutGet(GLUT_WINDOW_HEIGHT));

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    setupDisplay();
    glutSwapBuffers();
}

void Init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
}

void temploader(int argc, char** argv)
{
    static int initialized = 0;
    if (!initialized)
    {
        initialized = 1;
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutCreateWindow("System Boot");
        glutDisplayFunc(loddDisplay);
        glutMouseFunc(MouseButton);
        glutMotionFunc(MouseMotion);
        Init();

        glutMainLoop();
    }
}

void initLoader(int argc, char** argv) {
    temploader(argc, argv);
}
