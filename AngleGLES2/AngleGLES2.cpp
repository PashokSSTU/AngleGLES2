#include <stdio.h>
#include <SDL.h>
#include <GLES/gl.h> // https://www.khronos.org/registry/OpenGL/api/GLES2/gl2.h

#define Assert(x) do {if (!(x)) __debugbreak(); } while (0)

int main(int argc, char* argv[])
{
    Assert(SDL_Init(SDL_INIT_VIDEO) == 0);

    SDL_SetHint(SDL_HINT_VIDEO_WIN_D3DCOMPILER, "1");

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);

    SDL_Window* w = SDL_CreateWindow("ANGLE", 100, 100, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    Assert(w);

    SDL_GLContext ctx = SDL_GL_CreateContext(w);
    Assert(ctx);

    Assert(SDL_GL_MakeCurrent(w, ctx) == 0);
    SDL_GL_SetSwapInterval(1);

    PFNGLGETSTRINGPROC glGetString = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    PFNGLCLEARCOLORPROC glClearColor = (PFNGLCLEARCOLORPROC)SDL_GL_GetProcAddress("glClearColor");
    PFNGLCLEARPROC glClear = (PFNGLCLEARPROC)SDL_GL_GetProcAddress("glClear");

    PFNGLGENBUFFERSPROC glGenBuffers = (PFNGLGENBUFFERSPROC)SDL_GL_GetProcAddress("glGenBuffers");
    PFNGLBINDBUFFERPROC glBindBuffer = (PFNGLBINDBUFFERPROC)SDL_GL_GetProcAddress("glBindBuffer");
    PFNGLVERTEXPOINTERPROC glVertexPointer = (PFNGLVERTEXPOINTERPROC)SDL_GL_GetProcAddress("glVertexPointer");
    PFNGLENABLECLIENTSTATEPROC glEnableClientState = (PFNGLENABLECLIENTSTATEPROC)SDL_GL_GetProcAddress("glEnableClientState");
    PFNGLDISABLECLIENTSTATEPROC glDisableClientState = (PFNGLDISABLECLIENTSTATEPROC)SDL_GL_GetProcAddress("glDisableClientState");
    PFNGLCOLORPOINTERPROC glColorPointer = (PFNGLCOLORPOINTERPROC)SDL_GL_GetProcAddress("glColorPointer");
    PFNGLBUFFERDATAPROC glBufferData = (PFNGLBUFFERDATAPROC)SDL_GL_GetProcAddress("glBufferData");
    PFNGLDRAWARRAYSPROC glDrawArrays = (PFNGLDRAWARRAYSPROC)SDL_GL_GetProcAddress("glDrawArrays");

    printf("GL_VERSION = %s\n", glGetString(GL_VERSION));
    printf("GL_VENDOR = %s\n", glGetString(GL_VENDOR));
    printf("GL_RENDERER = %s\n", glGetString(GL_RENDERER));

    int running = 1;
    while (running)
    {
        SDL_Event ev;
        while (SDL_PollEvent(&ev))
        {
            if (ev.type == SDL_QUIT)
            {
                running = 0;
                break;
            }
        }

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        GLuint vertexBuf;
        GLuint colorBuf;

        float vertex[] = { 0,0, 1,0, 1,1 };
        float color[] = { 1,0,0, 0,1,0, 0,0,1 };

        glGenBuffers(1, &vertexBuf);
        glBindBuffer(GL_VERTEX_ARRAY, vertexBuf);
            glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), vertex, GL_STATIC_DRAW);
            glVertexPointer(2, GL_FLOAT, 0, &vertexBuf);
        glBindBuffer(GL_COLOR_ARRAY, 0);

        glGenBuffers(1, &colorBuf);
        glBindBuffer(GL_COLOR_ARRAY, colorBuf);
            glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), color, GL_STATIC_DRAW);
            glColorPointer(2, GL_FLOAT, 0, &colorBuf);
        glBindBuffer(GL_COLOR_ARRAY, 0);
        

        glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);

        SDL_GL_SwapWindow(w);
    }

    SDL_GL_DeleteContext(ctx);
    SDL_Quit();

    return 0;
}