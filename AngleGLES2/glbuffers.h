#ifndef __GLBUFFERS_H__
#define __GLBUFFERS_H__

#include "glload.h"

void glBufferObjectsInit();
void glBufferObjectsClear();
void pushVBO_ID(GLsizei size, GLuint VBO);
void pushEBO_ID(GLsizei size, GLuint EBO);
void pushTEX_ID(GLsizei size, GLuint TEX);

#endif