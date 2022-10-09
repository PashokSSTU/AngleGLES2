#ifndef __SIMPLE_C_SHADER__
#define __SIMPLE_C_SHADER__

#include "glload.h"

extern char* vertex;
extern char* fragment;

const char* loadShaders(const char* vertex_shader, const char* fragment_shader);
void useProgram();

void setUniformMat4x4(const char* name, const GLfloat* value);
void setBoolFlag(const char* name, const GLint value);
void setAlphaTestMode(const char* isEnabled, const GLboolean enabled, const char* alphaTestMode, GLuint func, const char* refName, GLclampf ref);

void checkCompileErrors(unsigned int shader, const char* type);

#endif