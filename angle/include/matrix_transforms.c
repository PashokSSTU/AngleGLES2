#include "matrix_transforms.h"

matrixStackModelView_t matrixStackModelView;
matrixStackProjection_t matrixStackProjection;
currentMode current_mode = GL_MODELVIEW;

mat4x4 transformMatrix;

void matrixStackInit()
{

	matrixStackModelView.matrices = 1;
	mat4x4_identity(matrixStackModelView.Stack[0]);

	matrixStackProjection.matrices = 1;
	mat4x4_identity(matrixStackProjection.Stack[0]);

	mat4x4_identity(transformMatrix);
}

void bglMatrixMode(currentMode mode)
{
	current_mode = mode;
}

void bglLoadIdentity()
{
	switch (current_mode)
	{
	case GL_MODELVIEW:
		mat4x4_identity(matrixStackModelView.Stack[matrixStackModelView.matrices - 1]);
		break;

	case GL_PROJECTION:
		mat4x4_identity(matrixStackProjection.Stack[matrixStackProjection.matrices - 1]);
		break;
	}

	mat4x4_mul(transformMatrix, matrixStackProjection.Stack[matrixStackProjection.matrices - 1], matrixStackModelView.Stack[matrixStackModelView.matrices - 1]);
}

void bglScalef(GLfloat x, GLfloat y, GLfloat z)
{
	switch (current_mode)
	{
	case GL_MODELVIEW:
		mat4x4_scale_aniso(matrixStackModelView.Stack[matrixStackModelView.matrices - 1],
			matrixStackModelView.Stack[matrixStackModelView.matrices - 1], x, y, z);
		break;

	case GL_PROJECTION:
		mat4x4_scale_aniso(matrixStackProjection.Stack[matrixStackProjection.matrices - 1],
			matrixStackProjection.Stack[matrixStackProjection.matrices - 1], x, y, z);
		break;
	}

	mat4x4_mul(transformMatrix, matrixStackProjection.Stack[matrixStackProjection.matrices - 1], matrixStackModelView.Stack[matrixStackModelView.matrices - 1]);
}

void bglTranslatef(GLfloat x, GLfloat y, GLfloat z)
{
	switch (current_mode)
	{
	case GL_MODELVIEW:
		mat4x4_translate_in_place(matrixStackModelView.Stack[matrixStackModelView.matrices - 1], x, y, z);
		break;

	case GL_PROJECTION:
		mat4x4_translate_in_place(matrixStackProjection.Stack[matrixStackProjection.matrices - 1], x, y, z);
		break;
	}

	mat4x4_mul(transformMatrix, matrixStackProjection.Stack[matrixStackProjection.matrices - 1], matrixStackModelView.Stack[matrixStackModelView.matrices - 1]);
}

void bglOrthof(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f)
{
	switch (current_mode)
	{
	case GL_MODELVIEW:
		mat4x4_ortho(matrixStackModelView.Stack[matrixStackModelView.matrices - 1], l, r, b, t, n, f);
		break;

	case GL_PROJECTION:
		mat4x4_ortho(matrixStackProjection.Stack[matrixStackProjection.matrices - 1], l, r, b, t, n, f);
		break;
	}

	mat4x4_mul(transformMatrix, matrixStackProjection.Stack[matrixStackProjection.matrices - 1], matrixStackModelView.Stack[matrixStackModelView.matrices - 1]);
}

void bglRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
	switch (current_mode)
	{
	case GL_MODELVIEW:
		mat4x4_rotate(matrixStackModelView.Stack[matrixStackModelView.matrices - 1], matrixStackModelView.Stack[matrixStackModelView.matrices - 1],
			x, y, z, angle);
		break;

	case GL_PROJECTION:
		mat4x4_rotate(matrixStackProjection.Stack[matrixStackProjection.matrices - 1], matrixStackProjection.Stack[matrixStackProjection.matrices - 1],
			x, y, z, angle);
		break;
	}

	mat4x4_mul(transformMatrix, matrixStackProjection.Stack[matrixStackProjection.matrices - 1], matrixStackModelView.Stack[matrixStackModelView.matrices - 1]);
}

void bglLoadMatrixf(const float* m)
{
	switch (current_mode)
	{
	case GL_MODELVIEW:

		(matrixStackModelView.Stack[matrixStackModelView.matrices - 1])[0][0] = m[0];
		(matrixStackModelView.Stack[matrixStackModelView.matrices - 1])[1][0] = m[1];
		(matrixStackModelView.Stack[matrixStackModelView.matrices - 1])[2][0] = m[2];
		(matrixStackModelView.Stack[matrixStackModelView.matrices - 1])[3][0] = m[3];
		(matrixStackModelView.Stack[matrixStackModelView.matrices - 1])[0][1] = m[4];
		(matrixStackModelView.Stack[matrixStackModelView.matrices - 1])[1][1] = m[5];
		(matrixStackModelView.Stack[matrixStackModelView.matrices - 1])[2][1] = m[6];
		(matrixStackModelView.Stack[matrixStackModelView.matrices - 1])[3][1] = m[7];
		(matrixStackModelView.Stack[matrixStackModelView.matrices - 1])[0][2] = m[8];
		(matrixStackModelView.Stack[matrixStackModelView.matrices - 1])[1][2] = m[9];
		(matrixStackModelView.Stack[matrixStackModelView.matrices - 1])[2][2] = m[10];
		(matrixStackModelView.Stack[matrixStackModelView.matrices - 1])[3][2] = m[11];
		(matrixStackModelView.Stack[matrixStackModelView.matrices - 1])[0][3] = m[12];
		(matrixStackModelView.Stack[matrixStackModelView.matrices - 1])[1][3] = m[13];
		(matrixStackModelView.Stack[matrixStackModelView.matrices - 1])[2][3] = m[14];
		(matrixStackModelView.Stack[matrixStackModelView.matrices - 1])[3][3] = m[15];

		break;

	case GL_PROJECTION:

		(matrixStackProjection.Stack[matrixStackProjection.matrices - 1])[0][0] = m[0];
		(matrixStackProjection.Stack[matrixStackProjection.matrices - 1])[1][0] = m[1];
		(matrixStackProjection.Stack[matrixStackProjection.matrices - 1])[2][0] = m[2];
		(matrixStackProjection.Stack[matrixStackProjection.matrices - 1])[3][0] = m[3];
		(matrixStackProjection.Stack[matrixStackProjection.matrices - 1])[0][1] = m[4];
		(matrixStackProjection.Stack[matrixStackProjection.matrices - 1])[1][1] = m[5];
		(matrixStackProjection.Stack[matrixStackProjection.matrices - 1])[2][1] = m[6];
		(matrixStackProjection.Stack[matrixStackProjection.matrices - 1])[3][1] = m[7];
		(matrixStackProjection.Stack[matrixStackProjection.matrices - 1])[0][2] = m[8];
		(matrixStackProjection.Stack[matrixStackProjection.matrices - 1])[1][2] = m[9];
		(matrixStackProjection.Stack[matrixStackProjection.matrices - 1])[2][2] = m[10];
		(matrixStackProjection.Stack[matrixStackProjection.matrices - 1])[3][2] = m[11];
		(matrixStackProjection.Stack[matrixStackProjection.matrices - 1])[0][3] = m[12];
		(matrixStackProjection.Stack[matrixStackProjection.matrices - 1])[1][3] = m[13];
		(matrixStackProjection.Stack[matrixStackProjection.matrices - 1])[2][3] = m[14];
		(matrixStackProjection.Stack[matrixStackProjection.matrices - 1])[3][3] = m[15];

		break;
	}
}

void bglPushMatrix()
{
	switch (current_mode)
	{
	case GL_MODELVIEW:
		matrixStackModelView.matrices++;
		break;

	case GL_PROJECTION:
		matrixStackProjection.matrices++;
		break;
	}

	mat4x4_mul(transformMatrix, matrixStackProjection.Stack[matrixStackProjection.matrices - 1], matrixStackModelView.Stack[matrixStackModelView.matrices - 1]);
}

void bglPopMatrix()
{
	switch (current_mode)
	{
	case GL_MODELVIEW:
		matrixStackModelView.matrices--;
		break;

	case GL_PROJECTION:
		matrixStackProjection.matrices--;
		break;
	}

	mat4x4_mul(transformMatrix, matrixStackProjection.Stack[matrixStackProjection.matrices - 1], matrixStackModelView.Stack[matrixStackModelView.matrices - 1]);
}