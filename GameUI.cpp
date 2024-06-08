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



void initFreeType() {
    if (FT_Init_FreeType(&ft)) {
        std::cout << "Could not init FreeType Library" << std::endl;
        return;
    }

    if (FT_New_Face(ft, "fonts/corp.ttf", 0, &face)) {
        std::cout << "Failed to load font" << std::endl;
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, 48);
}

void drawText2(const char* text, float x, float y) {
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(x, y);

    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text);
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
    std::cout << "Mouse Position X: " << x << " Y: " << y << std::endl;
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
    drawText2("Status Bar", 200.0f, 780.0f);
    drawText2("Game State", 200.0f, 393.0f);
    drawText2("Arena", 830.0f, 670.0f);

    drawText2("Phase", 60.0f, 703.0f);
    drawText2("Player", 60.0f, 640.0f);
    drawText2("Time", 60.0f, 680.0f);

    glLineWidth(3.5);
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(1130.0f, 700.0f);
    glVertex2f(1130.0f, 100.0f);
    glVertex2f(550.0f, 100.0f);
    glVertex2f(550.0f, 700.0f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(580.0f, 650.0f);
    glVertex2f(1100.0f, 650.0f);
    glVertex2f(1100.0f, 150.0f);
    glVertex2f(580.0f, 150.0f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(22.0f, 767.0f);
    glVertex2f(458.0f , 767.0f);
    glVertex2f(458.0f, 440.0f );
    glVertex2f(22.0f, 440.0f);
    glEnd();

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




//init
void dinit()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
}



//second init
void sinit() {
    static int initialized = 0;
    if (!initialized)
    {
        initialized = 1;
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutCreateWindow("System Boot");
        glutReshapeWindow(1200, 800);
        glutDisplayFunc(lDisplay);
        glutMouseFunc(MButton);
        glutMotionFunc(mMotion);
        dinit();

        glutMainLoop();
    }
}

//mainstream Ana akış sistemi
void GameUI::mainstream(int argc, char** argv) {
    std::cout << "GameUI is working" << std::endl;
    initFreeType();
    sinit();

}