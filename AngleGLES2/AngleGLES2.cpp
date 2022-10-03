#include <iostream>
#include <SDL.h>
#include <GLES2/gl2.h> // https://www.khronos.org/registry/OpenGL/api/GLES2/gl2.h
extern "C" {
#include "glload.h"
}

#define Assert(x) do {if (!(x)) __debugbreak(); } while (0)

const char* vertexShaderSource = "#version 210 core\n"
"(layout = 0) in vec3 aPos;\n"
"(layout = 1) in vec4 aCol;\n"
"out vec4 aColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   aColor = aCol;\n"
"}\0";

const char* fragShaderSource = "#version 210 core\n"
"in vec4 aColor;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = aColor;\n"
"}\0";


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
    //SDL_Window* w = SDL_CreateWindow("Balls", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    Assert(w);

    SDL_GLContext ctx = SDL_GL_CreateContext(w);
    Assert(ctx);

    Assert(SDL_GL_MakeCurrent(w, ctx) == 0);
    SDL_GL_SetSwapInterval(1);

    LoadFunctions();

    std::cout << "GL_VERSION = " << bglGetString(GL_VERSION) << std::endl;
    std::cout << "GL_VENDOR = " << bglGetString(GL_VENDOR) << std::endl;
    std::cout << "GL_RENDERER = " << bglGetString(GL_RENDERER) << std::endl;

    GLuint vertexShader;
    vertexShader = bglCreateShader(GL_VERTEX_SHADER);
    bglShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    bglCompileShader(vertexShader);

    int success;
    char infoLog[512];
    bglGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        bglGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLuint fragmentShader;
    fragmentShader = bglCreateShader(GL_FRAGMENT_SHADER);
    bglShaderSource(fragmentShader, 1, &fragShaderSource, NULL);

    bglGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        bglGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLuint shaderProgram;
    shaderProgram = bglCreateProgram();
    bglAttachShader(shaderProgram, vertexShader);
    bglAttachShader(shaderProgram, fragmentShader);
    bglLinkProgram(shaderProgram);

    bglGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        bglGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAMM::FRAGMENT::LINKING_FAILED\n" << infoLog << std::endl;
    }

    bglDeleteShader(vertexShader);
    bglDeleteShader(fragmentShader);

    float verticies[] = {
        -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
         0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
    };

    GLuint VBO;

    bglGenBuffers(1, &VBO);
    bglBindBuffer(GL_ARRAY_BUFFER, VBO);
    bglBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    bglVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    bglEnableVertexAttribArray(0);

    bglVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
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

        bglClearColor(1, 0, 0, 1);
        bglClear(GL_COLOR_BUFFER_BIT);

        bglBindBuffer(GL_ARRAY_BUFFER, VBO);
        bglUseProgram(shaderProgram);
        bglDrawArrays(GL_TRIANGLES, 0, 3);
       

        SDL_GL_SwapWindow(w);
    }

    SDL_GL_DeleteContext(ctx);
    SDL_Quit();

    return 0;
}