//
// Created by buldu on 5.06.2024.
//

#include <GL/glew.h>
#include <windows.h>
#include <GL/freeglut.h>
#include <cmath>
#include <string>
#include <iostream>
#include <tchar.h>
#include <io.h>
#include "stb/stb_image.h"
#include "GameUI.h"
#include "common.h"

#define STB_IMAGE_IMPLEMENTATION

int G_bButton1Down = 0;

#define TRUE 1
#define FALSE 0

float buttonX2 = 200.0f;
float buttonY2 = 350.0f;

float Buttonalpha2 = 400.0f;
float Buttonbeta2 = 350.0f;

float buttonWidth2 = 170.0f;
float buttonHeight2 = 60.0f;


bool buttonClicked2 = false;

void drawText2(const char *text, float x, float y) {
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(x, y);

    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
        text++;
    }
}



void mMotion(int x, int y)
{
    if (G_bButton1Down)
    {
        glutPostRedisplay();
    }
}


void MButton(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        G_bButton1Down = TRUE;
        int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
        y = windowHeight - y;

    }
    else
    {
        G_bButton1Down = FALSE;
    }
}


void sDisplay() {
    drawText2("Darwin Games BULDUK Version", 250.0f, 700.0f);
    drawText2("Powered By SS", 300.0f, 60.0f);
}

void lDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, glutGet(GLUT_WINDOW_HEIGHT));

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    sDisplay();
    glutSwapBuffers();
}

void dinit()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
}

void sinit() {
    static int initialized = 0;
    if (!initialized)
    {
        initialized = 1;
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutCreateWindow("System Boot");
        glutReshapeWindow(800, 800);
        glutDisplayFunc(lDisplay);
        glutMouseFunc(MButton);
        glutMotionFunc(mMotion);
        dinit();

        glutMainLoop();
    }
}


void GameUI::mainstream(int argc, char** argv) {
    std::cout << "GameUI is working" << std::endl;
    sinit();

}