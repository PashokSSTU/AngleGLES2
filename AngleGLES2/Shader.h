#ifndef __SHADER_H__
#define __SHADER_H__

#include "glload.h"

extern char* vertex;
extern char* fragment;

const char* loadShaders(const char* vertex_shader, const char* fragment_shader);
void useProgram();

void setTransformMatrix();
void setBoolFlag(const char* name, const GLint value);
void setAlphaTestMode(const char* isEnabled, const GLboolean enabled, const char* alphaTestMode, GLuint func, const char* refName, GLclampf ref);
void setFogUniforms();

void checkCompileErrors(unsigned int shader, const char* type);

#endif