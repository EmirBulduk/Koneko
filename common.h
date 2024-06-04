#ifndef COMMON_H
#define COMMON_H

#include <GL/glew.h>


struct Point {
    GLint x;
    GLint y;
};

struct GLColor {
    GLfloat red;
    GLfloat green;
    GLfloat blue;
};

extern GLuint texture;


extern GLColor colors[7];
extern GLColor color;


void drawText(const char* text, int x, int y);

#endif // COMMON_H
