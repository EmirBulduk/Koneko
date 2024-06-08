#ifndef COMMON_H
#define COMMON_H

#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H

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

extern FT_Library ft;
extern FT_Face face;


extern GLColor colors[7];
extern GLColor color;


void drawText(const char* text, int x, int y);

#endif // COMMON_H
