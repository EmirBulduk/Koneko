#include <GL/glew.h>
#include <windows.h>
#include <GL/freeglut.h>
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <png.h>
#include <cmath>
#include <string>
#include "neuralnetwork.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include <iostream>
#include <tchar.h>
#include <io.h>

GLuint texture;


struct Point {
    GLint x;
    GLint y;
};

struct GLColor {
    GLfloat red;
    GLfloat green;
    GLfloat blue;
};


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

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-0.5f, -0.5f);  // Bottom-left corner
    glTexCoord2f(1.0f, 0.0f); glVertex2f(0.5f, -0.5f);   // Bottom-right corner
    glTexCoord2f(1.0f, 1.0f); glVertex2f(0.5f, 0.5f);    // Top-right corner
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-0.5f, 0.5f);   // Top-left corner
    glEnd();

    glutSwapBuffers();
}

void drawText(const char *text, int x, int y) {
    glRasterPos2i(x, y);

    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
        text++;
    }
}

GLColor colors[7] = {
        {1.0f, 1.0f, 1.0f},
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f},
        {1.0f, 1.0f, 0.0f},
        {1.0f, 0.0f, 1.0f},
        {1.0f, 0.5f, 0.0f}
};

GLColor color = colors[0];

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 0);
    glColor3f(color.red, color.green, color.blue);
    glPointSize(1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1200.0, 0.0, 800.0);
    glEnable(GL_TEXTURE_2D);
    texture = loadTexture("app.png");
}

void draw_pixel(Point p) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(color.red, color.green, color.blue);
    glBegin(GL_POINTS);
    glVertex2i(p.x, p.y);
    glEnd();
    glFlush();
}

void draw_dda(Point p1, Point p2) {
    GLfloat dx = p2.x - p1.x;
    GLfloat dy = p2.y - p1.y;

    GLfloat x1 = p1.x;
    GLfloat y1 = p1.y;

    GLfloat step = 0;

    if(abs(dx) > abs(dy)) {
        step = abs(dx);
    } else {
        step = abs(dy);
    }

    GLfloat xInc = dx/step;
    GLfloat yInc = dy/step;

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(color.red, color.green, color.blue);
    glBegin(GL_POINTS);

    for(float i = 1; i <= step; i++) {
        glVertex2i(x1, y1);
        x1 += xInc;
        y1 += yInc;
    }
    glEnd();
    glFlush();

}

void draw_circle(Point pC, GLfloat radius) {
    GLfloat step = 1 / radius;
    GLfloat x, y;

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(color.red, color.green, color.blue);
    glBegin(GL_POINTS);

    for (GLfloat theta = 0; theta <= 360; theta += step) {
        x = pC.x + (radius * cos(theta));
        y = pC.y + (radius * sin(theta));
        glVertex2i(x, y);
    }
    glEnd();
    glFlush();
}



void setupDisplay(Point p1, Point p2) {

    GLColor stglColor = {1.0f, 1.0f, 1.0f};

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(stglColor.red, stglColor.green, stglColor.blue);
    glLineWidth(8.0f);
    glBegin(GL_LINES);
    glVertex2i(p1.x, p1.y);
    glVertex2i(p2.x, p2.y);
    glEnd();
    glFlush();



    Point p3 = {25, 25};
    Point p4 = {50, 50};
    Point p5 = {25, 50};
    Point p6 = {50, 25};

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex2d(p3.x, p3.y);
    glColor3f(2.0f, 1.0f, 1.0f);

    glVertex2d(p4.x, p4.y);
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex2d(p5.x, p5.y);
    glColor3f(2.0f, 1.0f, 1.0f);
    glVertex2d(p6.x, p6.y);
    glEnd();
    glFlush();

    drawText("POWERED BY Sentinel Systems", 500, 20);


}



void draw_ellipse(Point pC, GLfloat radiusY, GLfloat radiusX) {
    GLfloat step = 1/radiusX;
    GLfloat x, y;

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(color.red, color.green, color.blue);
    glBegin(GL_POINTS);
    for(GLfloat theta = 0; theta <= 360; theta += step) {
        x = pC.x + (radiusX * cos(theta));
        y = pC.y + (radiusY * sin(theta));
        glVertex2i(x, y);
    }
    glEnd();
    glFlush();
}

void mainMenuHandler(int choice) {
    Point p = {320, 240};
    Point p1 = {10, 100};
    Point p2 = {200, 100};

    Point pC = {600, 450};
    GLfloat radius = 200;

    switch(choice) {
        case 1:
            draw_pixel(p);
            break;

        case 2:
            exit(0);
            break;
    }
}

void importplayer() {
  std::cout << "importing player" << std::endl;
    printf("in proc");
}



void sbmtwoholder(int secim) {
    Point p1 = {400, 0};
    Point p2 = {400, 800};
    switch (secim) {

        case 1:
            importplayer();
            break;

        case 2:
            setupDisplay(p1, p2);
            break;
    }
}

void glutSetWindowTitle(char *name);

void subMenuHandler(int choice) {
    color = colors[choice];
}
void glutSetIconTitle(char *name);

void SetWindowIcon(HWND hwnd, HICON icon) {
    SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)icon);
    SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)icon);
}

HICON LoadIconFromFile(const char* filename) {
    return (HICON)LoadImage(NULL, filename, IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
}




void initGL() {
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
        exit(1);
    }
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);

    // Print working directory
    char cwd[1024];
    if (_getcwd(cwd, sizeof(cwd)) != NULL) {
        std::cout << "Current working directory: " << cwd << std::endl;
    } else {
        perror("_getcwd error");
    }

    // Load texture
    const char* imagePath = "app.png";  // Update the path if necessary
    std::cout << "Loading texture from: " << imagePath << std::endl;
    texture = loadTexture(imagePath);
    std::cout << "Texture loaded successfully" << std::endl;
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(1200, 800);
    glutCreateWindow("BULDUK");
    glutDisplayFunc(display);
    initGL();

    int subMenu = glutCreateMenu(subMenuHandler);
    glutAddMenuEntry("Default", 0);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Green", 2);
    glutAddMenuEntry("Blue", 3);
    glutAddMenuEntry("Yellow", 4);
    glutAddMenuEntry("Purple", 5);
    glutAddMenuEntry("Orange", 6);

    int sbmtwo = glutCreateMenu(sbmtwoholder);
    glutAddMenuEntry("import", 1);
    glutAddMenuEntry("SetupDisplay", 2);

    glutCreateMenu(mainMenuHandler);
    glutAddSubMenu("Main", sbmtwo);
    glutAddSubMenu("Change Color", subMenu);
    glutAddMenuEntry("Pixel", 1);
    glutAddMenuEntry("Exit", 2);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();

    return 0;
}