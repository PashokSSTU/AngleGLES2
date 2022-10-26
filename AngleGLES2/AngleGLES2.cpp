#include <iostream>
#include <SDL.h>

#include <GLES2/gl2.h> // https://www.khronos.org/registry/OpenGL/api/GLES2/gl2.h

extern "C" {
#include "glload.h"
#include "linmath.h"
#include "Shader.h"
#include "matrix_transforms.h"
#include "glbuffers.h"
}
//#include "Shader.h"
#include "stb_image.h"

unsigned char* textureBuffer;
int width, height, BPP;

#define Assert(x) do {if (!(x)) __debugbreak(); } while (0)

int main(int argc, char* argv[])
{
    Assert(SDL_Init(SDL_INIT_VIDEO) == 0);


    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    SDL_SetHint("SDL_HINT_OPENGL_ES_DRIVER", "1");

    SDL_Window* w = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        640, 640, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    Assert(w);

    SDL_GLContext ctx = SDL_GL_CreateContext(w);
    Assert(ctx);

    Assert(SDL_GL_MakeCurrent(w, ctx) == 0);
    SDL_GL_SetSwapInterval(1);

    LoadFunctions();
    glBufferObjectsInit();

    //textureBuffer = stbi_load("test_texture.png", &width, &height, &BPP, 4);

    BGL_Init();

    std::cout << "GL_VERSION = " << bglGetString(GL_VERSION) << std::endl;
    std::cout << "GL_VENDOR = " << bglGetString(GL_VENDOR) << std::endl;
    std::cout << "GL_RENDERER = " << bglGetString(GL_RENDERER) << std::endl;
    std::cout << "GL_RENDERER = " << bglGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    loadShaders("Shaders/vertexSample.vsh", "Shaders/fragmentSample.fsh");

    //bglEnable(GL_TEXTURE_2D);
    //GLuint texture;
    //bglGenTextures(1, &texture);
    //pushTEX_ID(1, texture);
    //bglBindBuffer(GL_TEXTURE_2D, texture);
    //bglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //bglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //bglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //bglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //bglTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureBuffer);
    //bglDisable(GL_TEXTURE_2D);
    //
    //if (textureBuffer)
        //stbi_image_free(textureBuffer);
    
    matrixStackInit();
    //bglViewport(0, 0, 100, 100);
    bglMatrixMode(GL_MODELVIEW);
    bglLoadIdentity();
    //bglScalef(100, 100, 0);
    //bglRotatef((M_PI * 0.0f) / 180.0f, 0.0f, 1.0f, 0.0f);
    //bglTranslatef(0.5f, 0.0f, 0.0f);

    bglMatrixMode(GL_PROJECTION);
    bglLoadIdentity();
    //bglOrthof(-1, 1, -1, 1, -10, 10);

    //float fogcol[4] = { 1.0f, 1.0f, 0.0f, 1.0f };

    //float verticies[] = {
    //    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.32f,
    //     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.32f,
    //     0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.32f,
    //    -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.32f,
    //};

    //unsigned int indices[] = {
    //    0, 1, 3,
    //    1, 2, 3
    //};

    //GLuint VBO;
    //GLuint EBO;

    //bglGenBuffers(1, &VBO);
    //bglGenBuffers(1, &EBO);
    //
    //bglBindBuffer(GL_ARRAY_BUFFER, VBO);
    //bglBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    //bglBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //bglBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //bglVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    //bglEnableVertexAttribArray(0);

    //bglVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    //bglEnableVertexAttribArray(1);

    //bglBindBuffer(GL_ARRAY_BUFFER, 0);

    bglEnable(GL_ALPHA_TEST);
    bglAlphaFunc(GL_EQUAL, 0.32f);
    bglDisable(GL_ALPHA_TEST);
    int running = 1;

    //bglEnable(GL_FOG);
    //bglFogf(GL_FOG_START, FULLVIS_BEGIN);
    //bglFogf(GL_FOG_END, FULLVIS_END);
    //bglFogf(GL_FOG_MODE, GL_LINEAR);
    //bglFogfv(GL_FOG_COLOR, fogcol);
    //bglDisable(GL_FOG);

    bool flag_render = true;

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

        bglClearColor(0, 0, 0, 0);
        bglClear(GL_COLOR_BUFFER_BIT);

        bglBegin(GL_TRIANGLES);

        bglColor4ub(255, 0, 0, 255);
        bglVertex2f(-1, -1);
        bglVertex2f(1, -1);
        bglVertex2f(0, 1);

        bglColor4ub(0, 0, 255, 255);
        bglVertex2f(-1, 1);
        bglVertex2f(1, 1);
        bglVertex2f(0, -1);

        bglEnd();

        SDL_GL_SwapWindow(w);
        glBufferObjectsClear();
    }

    SDL_GL_DeleteContext(ctx);
    SDL_Quit();

    return 0;
}