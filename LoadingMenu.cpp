#include <GL/glew.h>
#include <windows.h>
#include <GL/freeglut.h>
#include <cmath>
#include <string>
#include <iostream>
#include <tchar.h>
#include <io.h>
#include <cmath>
#include "stb/stb_image.h"
#include "GameUI.h"
#include "common.h"

#define STB_IMAGE_IMPLEMENTATION

int g_bButton1Down = 0;
float g_fViewDistance = 0.0;
float g_yClick = 0.0;

const float PI = 3.14159265358979323846;

const int windowWidth = 800;
const int windowHeight = 800;

#define TRUE 1
#define FALSE 0
#define VIEWING_DISTANCE_MIN 1.0

float buttonX = 200.0f;
float buttonY = 350.0f;

float Buttonalpha = 400.0f;
float Buttonbeta = 350.0f;

float buttonWidth = 170.0f;
float buttonHeight = 60.0f;


bool buttonClicked = false;


GLuint loadTexture(const char* filename) {
    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (!data) {
        std::cerr << "Texture load proccess failed " << filename << std::endl;
        std::cerr << "stdbi " << stbi_failure_reason() << std::endl;
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


void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * PI * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}


void drawThinRing(float cx, float cy, float outer_radius, int num_segments) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * PI * float(i) / float(num_segments);
        float x = outer_radius * cosf(theta);
        float y = outer_radius * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}


void drawText(const char *text, float x, float y) {
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(x, y);

    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
        text++;
    }
}




void Redirect()
{
    glutHideWindow(); // Hide the current window
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    GameUI gameUI;
    std::cout << "GameUI Loaded" << std::endl;
    gameUI.mainstream(0 ,NULL);
}



void drawButton(float x, float y, float width, float height, const char* label) {
    drawText(label, x + 10.0f, y + 20.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

}


void drawButton2(float x, float y, float width, float height, bool clicked, const char* label) {
    drawText(label, x + 10.0f, y + 20.0f);
    if (clicked) {
        glColor3f(0.0f, 1.0f, 0.0f);
    } else {
        glColor3f(1.0f, 0.0f, 0.0f);
    }
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

}


void setupDisplay() {
    drawText("Darwin Games BULDUK Version", 250.0f, 700.0f);
    drawText("Powered By SS", 300.0f, 60.0f);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);



    float centerX = windowWidth / 2 - 25;
    float centerY = windowHeight / 2 + 200;
    glColor3f(1.0, 0.5, 0.0);

    static float angle = 0.0f;
    float orbitRadius = 25.0f;
    float x = centerX + orbitRadius * cos(angle);
    float y = centerY + orbitRadius * sin(angle);

    drawCircle(x, y, 2, 100);
    drawCircle(centerX, centerY, 15, 100);
    for(int i = 0; i < 360; i += 46)
    {
        x = centerX + orbitRadius * cos(angle + i);
        y = centerY + orbitRadius * sin(angle + i);
        drawCircle(x, y, 2, 100);
        i++;
    }


    glColor3f(0.7, 0.5, 0.0);
    glAlphaFunc(GL_GREATER, 0.1f);
    drawThinRing( centerX, centerY, 25, 100);


    angle += 0.01f;

    drawButton(buttonX, buttonY, buttonWidth, buttonHeight, "Boot Game");
    drawButton2(Buttonalpha, Buttonbeta, buttonWidth, buttonHeight, buttonClicked, "Connect");


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
            std::cout << "Button 1 clicked" << std::endl;
            Redirect();
        }


        if(x >= Buttonalpha && x <= Buttonalpha + buttonWidth && y >= Buttonbeta && y <= Buttonbeta + buttonHeight)
        {
            buttonClicked = !buttonClicked;
            std::cout << "Button clicked!" << std::endl;
            glutPostRedisplay();
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

    glColor3f(1.0, 0.5, 0.0); // Orange color
    drawCircle(windowWidth / 2, windowHeight / 2, 15, 100);

    // Draw the orbiting circle
    static float angle = 0.0f;
    float orbitRadius = 25.0f;
    float x = windowWidth / 2 + orbitRadius * cos(angle);
    float y = windowHeight / 2 + orbitRadius * sin(angle);
    drawCircle(x, y, 2, 100);

    for(int i = 0; i < 360; i += 45)
    {
        //start this circle 1second later
        x = windowWidth / 2 + orbitRadius * cos(angle + i);
        y = windowHeight / 2 + orbitRadius * sin(angle + i);
        drawCircle(x, y, 2, 100);
    }


    glColor3f(0.7, 0.5, 0.0);
    glAlphaFunc(GL_GREATER, 0.1f);
    drawThinRing( windowWidth/ 2, windowHeight / 2, 25, 100);


    angle += 0.01f;
}


void timer(int value) {
    glutPostRedisplay(); // Request display update
    glutTimerFunc(16, timer, 0); // Call this function again in 16 milliseconds
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
        glutReshapeWindow(800, 800);
        glutDisplayFunc(loddDisplay);
        glutMouseFunc(MouseButton);
        glutMotionFunc(MouseMotion);
        Init();
        glutTimerFunc(0, timer, 0);

        glutMainLoop();
    }
}

void initLoader(int argc, char** argv) {
    temploader(argc, argv);
}
