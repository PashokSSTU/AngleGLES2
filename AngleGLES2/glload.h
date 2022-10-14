#ifndef __GLLOAD_H__
#define __GLLOAD_H__
#include <GLES2/gl2.h> // https://www.khronos.org/registry/OpenGL/api/GLES2/gl2.h
#include "SDL.h"
#include <stdio.h>

#ifdef GL_VERSION_ES_CM_1_0
extern PFNGLGETSTRINGPROC glGetString;
extern PFNGLCLEARCOLORPROC glClearColor;
extern PFNGLCLEARPROC glClear;

extern PFNGLGENBUFFERSPROC glGenBuffers;
extern PFNGLBINDBUFFERPROC glBindBuffer;
extern PFNGLVERTEXPOINTERPROC glVertexPointer;
extern PFNGLENABLECLIENTSTATEPROC glEnableClientState;
extern PFNGLDISABLECLIENTSTATEPROC glDisableClientState;
extern PFNGLCOLORPOINTERPROC glColorPointer;
extern PFNGLBUFFERDATAPROC glBufferData;
extern PFNGLDRAWARRAYSPROC glDrawArrays;
extern PFNGLCOLOR4UBPROC glColor4ub;
extern PFNGLVIEWPORTPROC glViewport;
#endif

#ifdef GL_ES_VERSION_2_0

typedef double GLdouble;
typedef double GLclampd;


extern void (__stdcall * bglesDisable)(GLenum cap);
extern void (__stdcall * bglesEnable)(GLenum cap);
extern GLenum(__stdcall * bglGetError)(void);

// Buffer objects
extern void (__stdcall * bglGenBuffers)(GLsizei n, GLuint * buffers);
extern void (__stdcall * bglDeleteBuffers)(GLsizei n, const GLuint * buffers);
extern void (__stdcall * bglBindBuffer)(GLenum target, GLuint buffer);
extern void (__stdcall * bglBufferData)(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
extern void (__stdcall * bglBufferSubData)(GLenum target, GLintptr offset, GLsizeiptr size, const void* data);
extern GLboolean(__stdcall * bglIsBuffer)(GLuint buffer);
extern void (__stdcall * bglGetBufferParameteriv)(GLenum target, GLenum pname, GLint * params);

// Viewpoint and Clipping
extern void (__stdcall * bglDepthRangef)(GLfloat n, GLfloat f);
extern void (__stdcall * bglViewport)(GLint x, GLint y, GLsizei width, GLsizei height);

// Reading Pixels
extern void (__stdcall * bglReadPixels)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels);

// Vertices
extern void (__stdcall * bglVertexAttrib1f)(GLuint index, GLfloat x);
extern void (__stdcall * bglVertexAttrib1fv)(GLuint index, const GLfloat * v);
extern void (__stdcall * bglVertexAttrib2f)(GLuint index, GLfloat x, GLfloat y);
extern void (__stdcall * bglVertexAttrib2fv)(GLuint index, const GLfloat * v);
extern void (__stdcall * bglVertexAttrib3f)(GLuint index, GLfloat x, GLfloat y, GLfloat z);
extern void (__stdcall * bglVertexAttrib3fv)(GLuint index, const GLfloat * v);
extern void (__stdcall * bglVertexAttrib4f)(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
extern void (__stdcall * bglVertexAttrib4fv)(GLuint index, const GLfloat * v);
extern void (__stdcall * bglVertexAttribPointer)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
extern void (__stdcall * bglEnableVertexAttribArray)(GLuint index);
extern void (__stdcall * bglDisableVertexAttribArray)(GLuint index);
extern void (__stdcall * bglDrawArrays)(GLenum mode, GLint first, GLsizei count);
extern void (__stdcall * bglDrawElements)(GLenum mode, GLsizei count, GLenum type, const void* indices);

// Texturing
extern void (__stdcall * bglActiveTexture)(GLenum texture);
extern void (__stdcall * bglTexImage2D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels);
extern void (__stdcall * bglCopyTexImage2D)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
extern void (__stdcall * bglTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels);
extern void (__stdcall * bglCopyTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
extern void (__stdcall * bglCompressedTexImage2D)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data);
extern void (__stdcall * bglCompressedTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data);
extern void (__stdcall * bglGetTexParameterfv)(GLenum target, GLenum pname, GLfloat * params);
extern void (__stdcall * bglGetTexParameteriv)(GLenum target, GLenum pname, GLint * params);
extern void (__stdcall * bglTexParameterf)(GLenum target, GLenum pname, GLfloat param);
extern void (__stdcall * bglTexParameterfv)(GLenum target, GLenum pname, const GLfloat * params);
extern void (__stdcall * bglTexParameteri)(GLenum target, GLenum pname, GLint param);
extern void (__stdcall * bglTexParameteriv)(GLenum target, GLenum pname, const GLint * params);
extern void (__stdcall * bglGenerateMipmap)(GLenum target);
extern void (__stdcall * bglBindTexture)(GLenum target, GLuint texture);
extern void (__stdcall * bglDeleteTextures)(GLsizei n, const GLuint * textures);
extern void (__stdcall * bglGenTextures)(GLsizei n, GLuint * textures);
extern GLboolean(__stdcall * bglIsTexture)(GLuint texture);

// Rasterization
extern void (__stdcall * bglLineWidth)(GLfloat width);
extern void (__stdcall * bglFrontFace)(GLenum mode);
extern void (__stdcall * bglCullFace)(GLenum mode);
extern void (__stdcall * bglPolygonOffset)(GLfloat factor, GLfloat units);

// Pixel Rectangles
extern void (__stdcall * bglPixelStorei)(GLenum pname, GLint param);

// Shaders and Programs
extern GLuint(__stdcall * bglCreateShader)(GLenum type);
extern void (__stdcall * bglShaderSource)(GLuint shader, GLsizei count, const GLchar* const* string, const GLint * length);
extern void (__stdcall * bglCompileShader)(GLuint shader);
extern void (__stdcall * bglReleaseShaderCompiler)(void);
extern void (__stdcall * bglDeleteShader)(GLuint shader);
extern void (__stdcall * bglShaderBinary)(GLsizei count, const GLuint * shaders, GLenum binaryFormat, const void* binary, GLsizei length);
extern GLuint(__stdcall * bglCreateProgram)(void);
extern void (__stdcall * bglAttachShader)(GLuint program, GLuint shader);
extern void (__stdcall * bglDetachShader)(GLuint program, GLuint shader);
extern void (__stdcall * bglLinkProgram)(GLuint program);
extern void (__stdcall * bglUseProgram)(GLuint program);
extern void (__stdcall * bglDeleteProgram)(GLuint program);
extern void (__stdcall * bglGetActiveAttrib)(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name);
extern GLint(__stdcall * bglGetAttribLocation)(GLuint program, const GLchar * name);
extern void (__stdcall * bglBindAttribLocation)(GLuint program, GLuint index, const GLchar * name);
extern GLint(__stdcall * bglGetUniformLocation)(GLuint program, const GLchar * name);
extern void (__stdcall * bglGetActiveUniform)(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name);
extern void (__stdcall * bglUniform1f)(GLint location, GLfloat v0);
extern void (__stdcall * bglUniform1fv)(GLint location, GLsizei count, const GLfloat * value);
extern void (__stdcall * bglUniform1i)(GLint location, GLint v0);
extern void (__stdcall * bglUniform1iv)(GLint location, GLsizei count, const GLint * value);
extern void (__stdcall * bglUniform2f)(GLint location, GLfloat v0, GLfloat v1);
extern void (__stdcall * bglUniform2fv)(GLint location, GLsizei count, const GLfloat * value);
extern void (__stdcall * bglUniform2i)(GLint location, GLint v0, GLint v1);
extern void (__stdcall * bglUniform2iv)(GLint location, GLsizei count, const GLint * value);
extern void (__stdcall * bglUniform3f)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
extern void (__stdcall * bglUniform3fv)(GLint location, GLsizei count, const GLfloat * value);
extern void (__stdcall * bglUniform3i)(GLint location, GLint v0, GLint v1, GLint v2);
extern void (__stdcall * bglUniform3iv)(GLint location, GLsizei count, const GLint * value);
extern void (__stdcall * bglUniform4f)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
extern void (__stdcall * bglUniform4fv)(GLint location, GLsizei count, const GLfloat * value);
extern void (__stdcall * bglUniform4i)(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
extern void (__stdcall * bglUniform4iv)(GLint location, GLsizei count, const GLint * value);
extern void (__stdcall * bglUniformMatrix2fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
extern void (__stdcall * bglUniformMatrix3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
extern void (__stdcall * bglUniformMatrix4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
extern void (__stdcall * bglValidateProgram)(GLuint program);

// Shader Queries
extern GLboolean(__stdcall * bglIsShader)(GLuint shader);
extern void (__stdcall * bglGetShaderiv)(GLuint shader, GLenum pname, GLint * params);
extern void (__stdcall * bglGetAttachedShaders)(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders);
extern void (__stdcall * bglGetShaderInfoLog)(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
extern void (__stdcall * bglGetShaderSource)(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source);
extern void (__stdcall * bglGetShaderPrecisionFormat)(GLenum shadertype, GLenum precisiontype, GLint * range, GLint * precision);
extern void (__stdcall * bglGetVertexAttribfv)(GLuint index, GLenum pname, GLfloat * params);
extern void (__stdcall * bglGetVertexAttribiv)(GLuint index, GLenum pname, GLint * params);
extern void (__stdcall * bglGetVertexAttribPointerv)(GLuint index, GLenum pname, void** pointer);
extern void (__stdcall * bglGetUniformfv)(GLuint program, GLint location, GLfloat * params);
extern void (__stdcall * bglGetUniformiv)(GLuint program, GLint location, GLint * params);
extern GLboolean(__stdcall * bglIsProgram)(GLuint program);
extern void (__stdcall * bglGetProgramiv)(GLuint program, GLenum pname, GLint * params);
extern void (__stdcall * bglGetProgramInfoLog)(GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog);

// Per-Fragment Operations
extern void (__stdcall * bglScissor)(GLint x, GLint y, GLsizei width, GLsizei height);
extern void (__stdcall * bglSampleCoverage)(GLfloat value, GLboolean invert);
extern void (__stdcall * bglStencilFunc)(GLenum func, GLint ref, GLuint mask);
extern void (__stdcall * bglStencilFuncSeparate)(GLenum face, GLenum func, GLint ref, GLuint mask);
extern void (__stdcall * bglStencilOp)(GLenum fail, GLenum zfail, GLenum zpass);
extern void (__stdcall * bglStencilOpSeparate)(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
extern void (__stdcall * bglDepthFunc)(GLenum func);
extern void (__stdcall * bglBlendEquation)(GLenum mode);
extern void (__stdcall * bglBlendEquationSeparate)(GLenum modeRGB, GLenum modeAlpha);
extern void (__stdcall * bglBlendFuncSeparate)(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
extern void (__stdcall * bglBlendFunc)(GLenum sfactor, GLenum dfactor);
extern void (__stdcall * bglBlendColor)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

// Whole Framebuffer Operations
extern void (__stdcall * bglColorMask)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
extern void (__stdcall * bglDepthMask)(GLboolean flag);
extern void (__stdcall * bglStencilMask)(GLuint mask);
extern void (__stdcall * bglStencilMaskSeparate)(GLenum face, GLuint mask);
extern void (__stdcall * bglClear)(GLbitfield mask);
extern void (__stdcall * bglClearColor)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
extern void (__stdcall * bglClearDepthf)(GLfloat d);
extern void (__stdcall * bglClearStencil)(GLint s);

// Special Functions
extern void (__stdcall * bglFinish)(void);
extern void (__stdcall * bglFlush)(void);
extern void (__stdcall * bglHint)(GLenum target, GLenum mode);

// State and State Requests
extern void (__stdcall * bglGetBooleanv)(GLenum pname, GLboolean * data);
extern void (__stdcall * bglGetIntegerv)(GLenum pname, GLint * data);
extern void (__stdcall * bglGetFloatv)(GLenum pname, GLfloat * data);
extern GLboolean(__stdcall * bglesIsEnabled)(GLenum cap);
extern const GLubyte * (__stdcall * bglGetString)(GLenum name);

// Framebuffer Objects
extern void (__stdcall * bglBindFramebuffer)(GLenum target, GLuint framebuffer);
extern void (__stdcall * bglBindRenderbuffer)(GLenum target, GLuint renderbuffer);
extern void (__stdcall * bglDeleteFramebuffers)(GLsizei n, const GLuint * framebuffers);
extern void (__stdcall * bglDeleteRenderbuffers)(GLsizei n, const GLuint * renderbuffers);
extern void (__stdcall * bglGenFramebuffers)(GLsizei n, GLuint * framebuffers);
extern void (__stdcall * bglGenRenderbuffers)(GLsizei n, GLuint * renderbuffers);
extern void (__stdcall * bglRenderbufferStorage)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
extern void (__stdcall * bglFramebufferRenderbuffer)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
extern void (__stdcall * bglFramebufferTexture2D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
extern GLenum(__stdcall * bglCheckFramebufferStatus)(GLenum target);
extern GLboolean(__stdcall * bglIsFramebuffer)(GLuint framebuffer);
extern GLboolean(__stdcall * bglIsRenderbuffer)(GLuint renderbuffer);
extern void (__stdcall * bglGetFramebufferAttachmentParameteriv)(GLenum target, GLenum attachment, GLenum pname, GLint * params);
extern void (__stdcall * bglGetRenderbufferParameteriv)(GLenum target, GLenum pname, GLint * params);


//Alpha
#define GL_ALPHA_TEST                     0x0BC0
#define GL_ALPHA_TEST_FUNC                0x0BC1
#define GL_ALPHA_TEST_REF                 0x0BC2
#define FULLVIS_BEGIN					  2.9e30f
#define FULLVIS_END						  3.0e30f

extern GLboolean GL_ALPHA_TEST_IS_ENABLED;
extern GLuint ALPHA_TEST_MODE;
extern GLclampf ALPHA_TEST_REFERENCE;

void bglAlphaFunc(GLenum func, GLclampf ref);
void bglEnable(GLenum cap);
void bglDisable(GLenum cap);
GLboolean bglIsEnabled(GLenum cap);
GLuint bglGetAlphaParameterui(GLenum cap);
GLclampf bglGetAlphaParameterfi(GLenum cap);

//Fog
#define GL_FOG                            0x0B60
#define GL_FOG_INDEX                      0x0B61
#define GL_FOG_DENSITY                    0x0B62
#define GL_FOG_START                      0x0B63
#define GL_FOG_END                        0x0B64
#define GL_FOG_MODE                       0x0B65
#define GL_FOG_COLOR                      0x0B66
#define GL_EXP                            0x0800
#define GL_EXP2                           0x0801

typedef struct _FogParameters
{
	GLclampf fogColor[4];
	GLclampf linearStart;
	GLclampf linearEnd;
	GLclampf density;
	GLclampf equation;
	GLboolean isEnabled;

} FogParameters;

extern FogParameters fogParams;

void bglFogf(GLenum pname, GLfloat param);
void bglFogfv(GLenum pname, const GLfloat* params);

#endif

#define GL_QUADS 0x0007
#define VBO_TEXTURE_ENABLE	0x0001
#define VBO_TEXTURE_DISABLE 0x0000

void BGL_Init();
void BGL_SetVBO_TexMode(long mode);

void bglBegin(GLenum mode);
void bglEnd(void);
void bglVertex2d(GLdouble x, GLdouble y);
void bglVertex2f(GLfloat x, GLfloat y);
void bglVertex2i(GLint x, GLint y);
void bglVertex3d(GLdouble x, GLdouble y, GLdouble z);
void bglVertex3f(GLfloat x, GLfloat y, GLfloat z);
void bglVertex3fv(const GLfloat* v);
void bglColor4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
void bglColor4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
void bglTexCoord2d(GLdouble s, GLdouble t);
void bglTexCoord2f(GLfloat s, GLfloat t);

void* loadProc(const char* t);
void LoadFunctions();

#endif