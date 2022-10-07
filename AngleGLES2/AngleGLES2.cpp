#include <iostream>
#include <SDL.h>

#include <GLES2/gl2.h> // https://www.khronos.org/registry/OpenGL/api/GLES2/gl2.h

extern "C" {
#include "glload.h"
#include "linmath.h"
#include "SimpleCShader.h"
}
//#include "Shader.h"

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
        640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    Assert(w);

    SDL_GLContext ctx = SDL_GL_CreateContext(w);
    Assert(ctx);

    Assert(SDL_GL_MakeCurrent(w, ctx) == 0);
    SDL_GL_SetSwapInterval(1);

    LoadFunctions();

    std::cout << "GL_VERSION = " << bglGetString(GL_VERSION) << std::endl;
    std::cout << "GL_VENDOR = " << bglGetString(GL_VENDOR) << std::endl;
    std::cout << "GL_RENDERER = " << bglGetString(GL_RENDERER) << std::endl;
    std::cout << "GL_RENDERER = " << bglGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    //Shader shaders("Shaders/vertexSample.vsh", "Shaders/fragmentSample.fsh");
    loadShaders("Shaders/vertexSample.vsh", "Shaders/fragmentSample.fsh");


    mat4x4 transform;
    mat4x4_identity(transform);
    mat4x4 rotate;
    mat4x4_rotate_Z(rotate, transform, M_PI / 2);



    float verticies[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
         0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    GLuint VBO;
    GLuint EBO;

    bglGenBuffers(1, &VBO);
    bglGenBuffers(1, &EBO);
    
    bglBindBuffer(GL_ARRAY_BUFFER, VBO);
    bglBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    bglBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    bglBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    bglVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    bglEnableVertexAttribArray(0);

    bglVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    bglEnableVertexAttribArray(1);

    bglBindBuffer(GL_ARRAY_BUFFER, 0);

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

        bglClearColor(0, 0, 0, 1);
        bglClear(GL_COLOR_BUFFER_BIT);
        
        //shaders.use();
        //bglUniformMatrix4fv(bglGetUniformLocation(shaders.ID, "transform"), 1, GL_FALSE, &rotate[0][0]);

        useProgram();
        setUniformMat4x4("transform", &rotate[0][0]);

        bglBindBuffer(GL_ARRAY_BUFFER, VBO);
        bglBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        bglDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
       

        SDL_GL_SwapWindow(w);
    }
    bglDeleteBuffers(1, &VBO);

    SDL_GL_DeleteContext(ctx);
    SDL_Quit();

    return 0;
}