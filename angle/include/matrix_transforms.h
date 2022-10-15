#ifndef __MATRIX_TRANSFORMS__
#define __MATRIX_TRANSFORMS__

#include "GLES2/gl2.h"

// Matrix calculations library
#include "linmath.h"

#define GL_MAX_MODELVIEW_STACK_DEPTH		0x0020
#define GL_MAX_PROJECTION_STACK_DEPTH		0x0004

typedef struct _matrixStackModelView
{
	mat4x4 Stack[GL_MAX_MODELVIEW_STACK_DEPTH];
	size_t matrices; // amounth of matrixes;
} matrixStackModelView_t;

typedef struct _matrixStackProjection
{
	mat4x4 Stack[GL_MAX_PROJECTION_STACK_DEPTH];
	size_t matrices; // amounth of matrixes;
} matrixStackProjection_t;

extern matrixStackModelView_t matrixStackModelView;
extern matrixStackProjection_t matrixStackProjection;

typedef enum {
	GL_MODELVIEW,
	GL_PROJECTION
} currentMode;

extern currentMode current_mode;

extern mat4x4 transformMatrix;

void matrixStackInit();

void bglMatrixMode(currentMode mode);
void bglLoadIdentity();
void bglScalef(GLfloat x, GLfloat y, GLfloat z);
void bglTranslatef(GLfloat x, GLfloat y, GLfloat z);
void bglOrthof(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
void bglRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);

void bglLoadMatrixf(const float * m);

void bglPushMatrix();
void bglPopMatrix();

GLuint currentStack;

#endif