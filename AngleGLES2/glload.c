#include "glload.h"

#ifdef GL_VERSION_ES_CM_1_0
PFNGLGETSTRINGPROC glGetString;
PFNGLCLEARCOLORPROC glClearColor;
PFNGLCLEARPROC glClear;

PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLVERTEXPOINTERPROC glVertexPointer;
PFNGLENABLECLIENTSTATEPROC glEnableClientState;
PFNGLDISABLECLIENTSTATEPROC glDisableClientState;
PFNGLCOLORPOINTERPROC glColorPointer;
PFNGLBUFFERDATAPROC glBufferData;
PFNGLDRAWARRAYSPROC glDrawArrays;
PFNGLCOLOR4UBPROC glColor4ub;
PFNGLVIEWPORTPROC glViewport;
#endif

#ifdef GL_ES_VERSION_2_0
void (__stdcall * bglDisable)(GLenum cap);
void (__stdcall * bglEnable)(GLenum cap);
GLenum(__stdcall * bglGetError)(void);

// Buffer objects
void (__stdcall * bglGenBuffers)(GLsizei n, GLuint * buffers);
void (__stdcall * bglDeleteBuffers)(GLsizei n, const GLuint * buffers);
void (__stdcall * bglBindBuffer)(GLenum target, GLuint buffer);
void (__stdcall * bglBufferData)(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
void (__stdcall * bglBufferSubData)(GLenum target, GLintptr offset, GLsizeiptr size, const void* data);
GLboolean(__stdcall * bglIsBuffer)(GLuint buffer);
void (__stdcall * bglGetBufferParameteriv)(GLenum target, GLenum pname, GLint * params);

// Viewpoint and Clipping
void (__stdcall * bglDepthRangef)(GLfloat n, GLfloat f);
void (__stdcall * bglViewport)(GLint x, GLint y, GLsizei width, GLsizei height);

// Reading Pixels
void (__stdcall * bglReadPixels)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels);

// Vertices
void (__stdcall * bglVertexAttrib1f)(GLuint index, GLfloat x);
void (__stdcall * bglVertexAttrib1fv)(GLuint index, const GLfloat * v);
void (__stdcall * bglVertexAttrib2f)(GLuint index, GLfloat x, GLfloat y);
void (__stdcall * bglVertexAttrib2fv)(GLuint index, const GLfloat * v);
void (__stdcall * bglVertexAttrib3f)(GLuint index, GLfloat x, GLfloat y, GLfloat z);
void (__stdcall * bglVertexAttrib3fv)(GLuint index, const GLfloat * v);
void (__stdcall * bglVertexAttrib4f)(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
void (__stdcall * bglVertexAttrib4fv)(GLuint index, const GLfloat * v);
void (__stdcall * bglVertexAttribPointer)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
void (__stdcall * bglEnableVertexAttribArray)(GLuint index);
void (__stdcall * bglDisableVertexAttribArray)(GLuint index);
void (__stdcall * bglDrawArrays)(GLenum mode, GLint first, GLsizei count);
void (__stdcall * bglDrawElements)(GLenum mode, GLsizei count, GLenum type, const void* indices);

// Texturing
void (__stdcall * bglActiveTexture)(GLenum texture);
void (__stdcall * bglTexImage2D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels);
void (__stdcall * bglCopyTexImage2D)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
void (__stdcall * bglTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels);
void (__stdcall * bglCopyTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
void (__stdcall * bglCompressedTexImage2D)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data);
void (__stdcall * bglCompressedTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data);
void (__stdcall * bglGetTexParameterfv)(GLenum target, GLenum pname, GLfloat * params);
void (__stdcall * bglGetTexParameteriv)(GLenum target, GLenum pname, GLint * params);
void (__stdcall * bglTexParameterf)(GLenum target, GLenum pname, GLfloat param);
void (__stdcall * bglTexParameterfv)(GLenum target, GLenum pname, const GLfloat * params);
void (__stdcall * bglTexParameteri)(GLenum target, GLenum pname, GLint param);
void (__stdcall * bglTexParameteriv)(GLenum target, GLenum pname, const GLint * params);
void (__stdcall * bglGenerateMipmap)(GLenum target);
void (__stdcall * bglBindTexture)(GLenum target, GLuint texture);
void (__stdcall * bglDeleteTextures)(GLsizei n, const GLuint * textures);
void (__stdcall * bglGenTextures)(GLsizei n, GLuint * textures);
GLboolean(__stdcall * bglIsTexture)(GLuint texture);

// Rasterization
void (__stdcall * bglLineWidth)(GLfloat width);
void (__stdcall * bglFrontFace)(GLenum mode);
void (__stdcall * bglCullFace)(GLenum mode);
void (__stdcall * bglPolygonOffset)(GLfloat factor, GLfloat units);

// Pixel Rectangles
void (__stdcall * bglPixelStorei)(GLenum pname, GLint param);

// Shaders and Programs
GLuint(__stdcall * bglCreateShader)(GLenum type);
void (__stdcall * bglShaderSource)(GLuint shader, GLsizei count, const GLchar* const* string, const GLint * length);
void (__stdcall * bglCompileShader)(GLuint shader);
void (__stdcall * bglReleaseShaderCompiler)(void);
void (__stdcall * bglDeleteShader)(GLuint shader);
void (__stdcall * bglShaderBinary)(GLsizei count, const GLuint * shaders, GLenum binaryFormat, const void* binary, GLsizei length);
GLuint(__stdcall * bglCreateProgram)(void);
void (__stdcall * bglAttachShader)(GLuint program, GLuint shader);
void (__stdcall * bglDetachShader)(GLuint program, GLuint shader);
void (__stdcall * bglLinkProgram)(GLuint program);
void (__stdcall * bglUseProgram)(GLuint program);
void (__stdcall * bglDeleteProgram)(GLuint program);
void (__stdcall * bglGetActiveAttrib)(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name);
GLint(__stdcall * bglGetAttribLocation)(GLuint program, const GLchar * name);
void (__stdcall * bglBindAttribLocation)(GLuint program, GLuint index, const GLchar * name);
GLint(__stdcall * bglGetUniformLocation)(GLuint program, const GLchar * name);
void (__stdcall * bglGetActiveUniform)(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name);
void (__stdcall * bglUniform1f)(GLint location, GLfloat v0);
void (__stdcall * bglUniform1fv)(GLint location, GLsizei count, const GLfloat * value);
void (__stdcall * bglUniform1i)(GLint location, GLint v0);
void (__stdcall * bglUniform1iv)(GLint location, GLsizei count, const GLint * value);
void (__stdcall * bglUniform2f)(GLint location, GLfloat v0, GLfloat v1);
void (__stdcall * bglUniform2fv)(GLint location, GLsizei count, const GLfloat * value);
void (__stdcall * bglUniform2i)(GLint location, GLint v0, GLint v1);
void (__stdcall * bglUniform2iv)(GLint location, GLsizei count, const GLint * value);
void (__stdcall * bglUniform3f)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
void (__stdcall * bglUniform3fv)(GLint location, GLsizei count, const GLfloat * value);
void (__stdcall * bglUniform3i)(GLint location, GLint v0, GLint v1, GLint v2);
void (__stdcall * bglUniform3iv)(GLint location, GLsizei count, const GLint * value);
void (__stdcall * bglUniform4f)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
void (__stdcall * bglUniform4fv)(GLint location, GLsizei count, const GLfloat * value);
void (__stdcall * bglUniform4i)(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
void (__stdcall * bglUniform4iv)(GLint location, GLsizei count, const GLint * value);
void (__stdcall * bglUniformMatrix2fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
void (__stdcall * bglUniformMatrix3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
void (__stdcall * bglUniformMatrix4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
void (__stdcall * bglValidateProgram)(GLuint program);

// Shader Queries
GLboolean(__stdcall * bglIsShader)(GLuint shader);
void (__stdcall * bglGetShaderiv)(GLuint shader, GLenum pname, GLint * params);
void (__stdcall * bglGetAttachedShaders)(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders);
void (__stdcall * bglGetShaderInfoLog)(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
void (__stdcall * bglGetShaderSource)(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source);
void (__stdcall * bglGetShaderPrecisionFormat)(GLenum shadertype, GLenum precisiontype, GLint * range, GLint * precision);
void (__stdcall * bglGetVertexAttribfv)(GLuint index, GLenum pname, GLfloat * params);
void (__stdcall * bglGetVertexAttribiv)(GLuint index, GLenum pname, GLint * params);
void (__stdcall * bglGetVertexAttribPointerv)(GLuint index, GLenum pname, void** pointer);
void (__stdcall * bglGetUniformfv)(GLuint program, GLint location, GLfloat * params);
void (__stdcall * bglGetUniformiv)(GLuint program, GLint location, GLint * params);
GLboolean(__stdcall * bglIsProgram)(GLuint program);
void (__stdcall * bglGetProgramiv)(GLuint program, GLenum pname, GLint * params);
void (__stdcall * bglGetProgramInfoLog)(GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog);

// Per-Fragment Operations
void (__stdcall * bglScissor)(GLint x, GLint y, GLsizei width, GLsizei height);
void (__stdcall * bglSampleCoverage)(GLfloat value, GLboolean invert);
void (__stdcall * bglStencilFunc)(GLenum func, GLint ref, GLuint mask);
void (__stdcall * bglStencilFuncSeparate)(GLenum face, GLenum func, GLint ref, GLuint mask);
void (__stdcall * bglStencilOp)(GLenum fail, GLenum zfail, GLenum zpass);
void (__stdcall * bglStencilOpSeparate)(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
void (__stdcall * bglDepthFunc)(GLenum func);
void (__stdcall * bglBlendEquation)(GLenum mode);
void (__stdcall * bglBlendEquationSeparate)(GLenum modeRGB, GLenum modeAlpha);
void (__stdcall * bglBlendFuncSeparate)(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
void (__stdcall * bglBlendFunc)(GLenum sfactor, GLenum dfactor);
void (__stdcall * bglBlendColor)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

// Whole Framebuffer Operations
void (__stdcall * bglColorMask)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
void (__stdcall * bglDepthMask)(GLboolean flag);
void (__stdcall * bglStencilMask)(GLuint mask);
void (__stdcall * bglStencilMaskSeparate)(GLenum face, GLuint mask);
void (__stdcall * bglClear)(GLbitfield mask);
void (__stdcall * bglClearColor)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
void (__stdcall * bglClearDepthf)(GLfloat d);
void (__stdcall * bglClearStencil)(GLint s);

// Special Functions
void (__stdcall * bglFinish)(void);
void (__stdcall * bglFlush)(void);
void (__stdcall * bglHint)(GLenum target, GLenum mode);

// State and State Requests
void (__stdcall * bglGetBooleanv)(GLenum pname, GLboolean * data);
void (__stdcall * bglGetIntegerv)(GLenum pname, GLint * data);
void (__stdcall * bglGetFloatv)(GLenum pname, GLfloat * data);
GLboolean(__stdcall * bglIsEnabled)(GLenum cap);
const GLubyte * (__stdcall * bglGetString)(GLenum name);

// Framebuffer Objects
void (__stdcall * bglBindFramebuffer)(GLenum target, GLuint framebuffer);
void (__stdcall * bglBindRenderbuffer)(GLenum target, GLuint renderbuffer);
void (__stdcall * bglDeleteFramebuffers)(GLsizei n, const GLuint * framebuffers);
void (__stdcall * bglDeleteRenderbuffers)(GLsizei n, const GLuint * renderbuffers);
void (__stdcall * bglGenFramebuffers)(GLsizei n, GLuint * framebuffers);
void (__stdcall * bglGenRenderbuffers)(GLsizei n, GLuint * renderbuffers);
void (__stdcall * bglRenderbufferStorage)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
void (__stdcall * bglFramebufferRenderbuffer)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
void (__stdcall * bglFramebufferTexture2D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GLenum(__stdcall * bglCheckFramebufferStatus)(GLenum target);
GLboolean(__stdcall * bglIsFramebuffer)(GLuint framebuffer);
GLboolean(__stdcall * bglIsRenderbuffer)(GLuint renderbuffer);
void (__stdcall * bglGetFramebufferAttachmentParameteriv)(GLenum target, GLenum attachment, GLenum pname, GLint * params);
void (__stdcall * bglGetRenderbufferParameteriv)(GLenum target, GLenum pname, GLint * params);
#endif

void* loadProc(const char* t)
{
    void* result = NULL;
    result = SDL_GL_GetProcAddress(t);
    if (result == NULL)
    {
        printf("Error! Function \"%s\" didn't loaded!", t);
    }

    return result;
}

void LoadFunctions()
{
#ifdef GL_VERSION_ES_CM_1_0
    glGetString = (PFNGLGETSTRINGPROC)loadProc("glGetString");
    glClearColor = (PFNGLCLEARCOLORPROC)loadProc("glClearColor");
    glClear = (PFNGLCLEARPROC)loadProc("glClear");

    glGenBuffers = (PFNGLGENBUFFERSPROC)loadProc("glGenBuffers");
    glBindBuffer = (PFNGLBINDBUFFERPROC)loadProc("glBindBuffer");
    glVertexPointer = (PFNGLVERTEXPOINTERPROC)loadProc("glVertexPointer");
    glEnableClientState = (PFNGLENABLECLIENTSTATEPROC)loadProc("glEnableClientState");
    glDisableClientState = (PFNGLDISABLECLIENTSTATEPROC)loadProc("glDisableClientState");
    glColorPointer = (PFNGLCOLORPOINTERPROC)loadProc("glColorPointer");
    glBufferData = (PFNGLBUFFERDATAPROC)loadProc("glBufferData");
    glDrawArrays = (PFNGLDRAWARRAYSPROC)loadProc("glDrawArrays");
    glColor4ub = (PFNGLCOLOR4UBPROC)loadProc("glColor4ub");
    glViewport = (PFNGLVIEWPORTPROC)loadProc("glViewport");
#endif

#ifdef GL_ES_VERSION_2_0
    bglDisable =                                loadProc("glDisable");
    bglEnable =                                 loadProc("glEnable");
    bglGetError =                               loadProc("glGetError");
    bglGenBuffers =                             loadProc("glGenBuffers");
    bglDeleteBuffers =                          loadProc("glDeleteBuffers");
    bglBindBuffer =                             loadProc("glBindBuffer");
    bglBufferData =                             loadProc("glBufferData");
    bglBufferSubData =                          loadProc("glBufferSubData");
    bglIsBuffer =                               loadProc("glIsBuffer");
    bglGetBufferParameteriv =                   loadProc("glGetBufferParameteriv");
    bglDepthRangef =                            loadProc("glDepthRangef");
    bglViewport =                               loadProc("glViewport");
    bglReadPixels =                             loadProc("glReadPixels");
    bglVertexAttrib1f =                         loadProc("glVertexAttrib1f");
    bglVertexAttrib1fv =                        loadProc("glVertexAttrib1fv");
    bglVertexAttrib2f =                         loadProc("glVertexAttrib2f");
    bglVertexAttrib2fv =                        loadProc("glVertexAttrib2fv");
    bglVertexAttrib3f =                         loadProc("glVertexAttrib3f");
    bglVertexAttrib3fv =                        loadProc("glVertexAttrib3fv");
    bglVertexAttrib4f =                         loadProc("glVertexAttrib4f");
    bglVertexAttrib4fv =                        loadProc("glVertexAttrib4fv");
    bglVertexAttribPointer =                    loadProc("glVertexAttribPointer");
    bglEnableVertexAttribArray =                loadProc("glEnableVertexAttribArray");
    bglDisableVertexAttribArray =               loadProc("glDisableVertexAttribArray");
    bglDrawArrays =                             loadProc("glDrawArrays");
    bglDrawElements =                           loadProc("glDrawElements");
    bglActiveTexture =                          loadProc("glActiveTexture");
    bglTexImage2D =                             loadProc("glTexImage2D");
    bglCopyTexImage2D =                         loadProc("glCopyTexImage2D");
    bglTexSubImage2D =                          loadProc("glTexSubImage2D");
    bglCopyTexSubImage2D =                      loadProc("glCopyTexSubImage2D");
    bglCompressedTexImage2D =                   loadProc("glCompressedTexImage2D");
    bglCompressedTexSubImage2D =                loadProc("glCompressedTexSubImage2D");
    bglGetTexParameterfv =                      loadProc("glGetTexParameterfv");
    bglGetTexParameteriv =                      loadProc("glGetTexParameteriv");
    bglTexParameterf =                          loadProc("glTexParameterf");
    bglTexParameterfv =                         loadProc("glTexParameterfv");
    bglTexParameteri =                          loadProc("glTexParameteri");
    bglTexParameteriv =                         loadProc("glTexParameteriv");
    bglGenerateMipmap =                         loadProc("glGenerateMipmap");
    bglBindTexture =                            loadProc("glBindTexture");
    bglDeleteTextures =                         loadProc("glDeleteTextures");
    bglGenTextures =                            loadProc("glGenTextures");
    bglIsTexture =                              loadProc("glIsTexture");
    bglLineWidth =                              loadProc("glLineWidth");
    bglFrontFace =                              loadProc("glFrontFace");
    bglCullFace =                               loadProc("glCullFace");
    bglPolygonOffset =                          loadProc("glPolygonOffset");
    bglPixelStorei =                            loadProc("glPixelStorei");
    bglCreateShader =                           loadProc("glCreateShader");
    bglShaderSource =                           loadProc("glShaderSource");
    bglCompileShader =                          loadProc("glCompileShader");
    bglReleaseShaderCompiler =                  loadProc("glReleaseShaderCompiler");
    bglDeleteShader =                           loadProc("glDeleteShader");
    bglShaderBinary =                           loadProc("glShaderBinary");
    bglCreateProgram =                          loadProc("glCreateProgram");
    bglAttachShader =                           loadProc("glAttachShader");
    bglDetachShader =                           loadProc("glDetachShader");
    bglLinkProgram =                            loadProc("glLinkProgram");
    bglUseProgram =                             loadProc("glUseProgram");
    bglDeleteProgram =                          loadProc("glDeleteProgram");
    bglGetActiveAttrib =                        loadProc("glGetActiveAttrib");
    bglGetAttribLocation =                      loadProc("glGetAttribLocation");
    bglBindAttribLocation =                     loadProc("glBindAttribLocation");
    bglGetUniformLocation =                     loadProc("glGetUniformLocation");
    bglGetActiveUniform =                       loadProc("glGetActiveUniform");
    bglUniform1f =                              loadProc("glUniform1f");
    bglUniform1fv =                             loadProc("glUniform1fv");
    bglUniform1i =                              loadProc("glUniform1i");
    bglUniform1iv =                             loadProc("glUniform1iv");
    bglUniform2f =                              loadProc("glUniform2f");
    bglUniform2fv =                             loadProc("glUniform2fv");
    bglUniform2i =                              loadProc("glUniform2i");
    bglUniform2iv =                             loadProc("glUniform2iv");
    bglUniform3f =                              loadProc("glUniform3f");
    bglUniform3fv =                             loadProc("glUniform3fv");
    bglUniform3i =                              loadProc("glUniform3i");
    bglUniform3iv =                             loadProc("glUniform3iv");
    bglUniform4f =                              loadProc("glUniform4f");
    bglUniform4fv =                             loadProc("glUniform4fv");
    bglUniform4i =                              loadProc("glUniform4i");
    bglUniform4iv =                             loadProc("glUniform4iv");
    bglUniformMatrix2fv =                       loadProc("glUniformMatrix2fv");
    bglUniformMatrix3fv =                       loadProc("glUniformMatrix3fv");
    bglUniformMatrix4fv =                       loadProc("glUniformMatrix4fv");
    bglValidateProgram =                        loadProc("glValidateProgram");
    bglIsShader =                               loadProc("glIsShader");
    bglGetShaderiv =                            loadProc("glGetShaderiv");
    bglGetAttachedShaders =                     loadProc("glGetAttachedShaders");
    bglGetShaderInfoLog =                       loadProc("glGetShaderInfoLog");
    bglGetShaderSource =                        loadProc("glGetShaderSource");
    bglGetShaderPrecisionFormat =               loadProc("glGetShaderPrecisionFormat");
    bglGetVertexAttribfv =                      loadProc("glGetVertexAttribfv");
    bglGetVertexAttribiv =                      loadProc("glGetVertexAttribiv");
    bglGetVertexAttribPointerv =                loadProc("glGetVertexAttribPointerv");
    bglGetUniformfv =                           loadProc("glGetUniformfv");
    bglGetUniformiv =                           loadProc("glGetUniformiv");
    bglIsProgram =                              loadProc("glIsProgram");
    bglGetProgramiv =                           loadProc("glGetProgramiv");
    bglGetProgramInfoLog =                      loadProc("glGetProgramInfoLog");
    bglScissor =                                loadProc("glScissor");
    bglSampleCoverage =                         loadProc("glSampleCoverage");
    bglStencilFunc =                            loadProc("glStencilFunc");
    bglStencilFuncSeparate =                    loadProc("glStencilFuncSeparate");
    bglStencilOp =                              loadProc("glStencilOp");
    bglStencilOpSeparate =                      loadProc("glStencilOpSeparate");
    bglDepthFunc =                              loadProc("glDepthFunc");
    bglBlendEquation =                          loadProc("glBlendEquation");
    bglBlendEquationSeparate =                  loadProc("glBlendEquationSeparate");
    bglBlendFuncSeparate =                      loadProc("glBlendFuncSeparate");
    bglBlendFunc =                              loadProc("glBlendFunc");
    bglBlendColor =                             loadProc("glBlendColor");
    bglColorMask =                              loadProc("glColorMask");
    bglDepthMask =                              loadProc("glDepthMask");
    bglStencilMask =                            loadProc("glStencilMask");
    bglStencilMaskSeparate =                    loadProc("glStencilMaskSeparate");
    bglClear =                                  loadProc("glClear");
    bglClearColor =                             loadProc("glClearColor");
    bglClearDepthf =                            loadProc("glClearDepthf");
    bglClearStencil =                           loadProc("glClearStencil");
    bglFinish =                                 loadProc("glFinish");
    bglFlush =                                  loadProc("glFlush");
    bglHint =                                   loadProc("glHint");
    bglGetBooleanv =                            loadProc("glGetBooleanv");
    bglGetIntegerv =                            loadProc("glGetIntegerv");
    bglGetFloatv =                              loadProc("glGetFloatv");
    bglIsEnabled =                              loadProc("glIsEnabled");
    bglGetString =                              loadProc("glGetString");
    bglBindFramebuffer =                        loadProc("glBindFramebuffer");
    bglBindRenderbuffer =                       loadProc("glBindRenderbuffer");
    bglDeleteFramebuffers =                     loadProc("glDeleteFramebuffers");
    bglDeleteRenderbuffers =                    loadProc("glDeleteRenderbuffers");
    bglGenFramebuffers =                        loadProc("glGenFramebuffers");
    bglGenRenderbuffers =                       loadProc("glGenRenderbuffers");
    bglRenderbufferStorage =                    loadProc("glRenderbufferStorage");
    bglFramebufferRenderbuffer =                loadProc("glFramebufferRenderbuffer");
    bglFramebufferTexture2D =                   loadProc("glFramebufferTexture2D");
    bglCheckFramebufferStatus =                 loadProc("glCheckFramebufferStatus");
    bglIsFramebuffer =                          loadProc("glIsFramebuffer");
    bglIsRenderbuffer =                         loadProc("glIsRenderbuffer");
    bglGetFramebufferAttachmentParameteriv =    loadProc("glGetFramebufferAttachmentParameteriv");
    bglGetRenderbufferParameteriv =             loadProc("glGetRenderbufferParameteriv");    
#endif
}