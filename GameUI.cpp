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
#include <ft2build.h>
#include FT_FREETYPE_H
#include "stb/stb_image.h"
#include "GameUI.h"
#include "common.h"

#define FONT_PATH "fonts/kremlin.ttf"
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

GLuint textureID;
FT_Library ft;


FT_Face face;




void renderText(const char* text, float x, float y, float sx, float sy) {
    const char* p;
    FT_GlyphSlot g = face->glyph;

    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(sx, sy, 1);

    for (p = text; *p; p++) {
        if (FT_Load_Char(face, *p, FT_LOAD_RENDER))
            continue;

        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_ALPHA,
                g->bitmap.width,
                g->bitmap.rows,
                0,
                GL_ALPHA,
                GL_UNSIGNED_BYTE,
                g->bitmap.buffer
        );

        glBegin(GL_QUADS);
        glTexCoord2d(0, 0); glVertex2f(0, 0);
        glTexCoord2d(0, 1); glVertex2f(0, g->bitmap.rows);
        glTexCoord2d(1, 1); glVertex2f(g->bitmap.width, g->bitmap.rows);
        glTexCoord2d(1, 0); glVertex2f(g->bitmap.width, 0);
        glEnd();

        glTranslatef(g->advance.x >> 6, g->advance.y >> 6, 0);
    }

    glPopMatrix();
}





void drawText2(const char* text, float x, float y) {
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    float sx = 2.0f / windowWidth;
    float sy = 2.0f / windowHeight;

    renderText(text, x * sx - 1.0f, 1.0f - y * sy, sx, sy);
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
    drawText2("Status Bar", 10.0f, 10.0f);
    drawText2("Game State", 250.0f, 700.0f);
    drawText2("Arena", 840.0f, 672.0f);

    glLineWidth(3.5);
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(1130.0f, 700.0f);
    glVertex2f(1130.0f, 100.0f);
    glVertex2f(550.0f, 100.0f);
    glVertex2f(550.0f, 700.0f);
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

    // Initialize FreeType and load the font
    if (FT_Init_FreeType(&ft)) {
        std::cerr << "Could not init FreeType Library" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (FT_New_Face(ft, FONT_PATH, 0, &face)) {
        std::cerr << "Could not open font " << FONT_PATH << std::endl;
        exit(EXIT_FAILURE);
    }
    FT_Set_Pixel_Sizes(face, 0, 48);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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
    sinit();

}