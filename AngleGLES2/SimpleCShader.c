#include "SimpleCShader.h"
#include <stdio.h>

char* vertex;
char* fragment;
GLuint program;

const char* loadShaders(const char* vertex_shader, const char* fragment_shader)
{
	FILE *vsh, *fsh;
	size_t v_length, f_length;
	errno_t er;

	// Read and save vertex shader (.vsh file) to char array
	if((er = fopen_s(&vsh, vertex_shader, "rb+")) != 0)
	{
		printf("ERROR::SHADER::FILE_NOT_SUCCESFULLY_OPEN\n");
	}

	fseek(vsh, 0, SEEK_END);
	v_length = ftell(vsh);
	rewind(vsh);

	vertex = (char*)malloc(v_length + 1);
	size_t vr = fread(vertex, sizeof(char), v_length, vsh);
	vertex[v_length] = '\0';

	if (fclose(vsh) == EOF)
	{
		printf("ERROR::SHADER::FILE_NOT_SUCCESFULLY_CLOSE\n");
	}

	// Read and save fragment shader (.fsh file) to char array
	if ((er = fopen_s(&fsh, fragment_shader, "rb+")) != 0)
	{
		printf("ERROR::SHADER::FILE_NOT_SUCCESFULLY_OPEN\n");
	}

	fseek(fsh, 0, SEEK_END);
	f_length = ftell(fsh);
	rewind(fsh);

	fragment = (char*)malloc(f_length + 1);
	size_t fr = fread(fragment, sizeof(char), f_length, fsh);
	fragment[f_length] = '\0';

	if (fclose(fsh) == EOF)
	{
		printf("ERROR::SHADER::FILE_NOT_SUCCESFULLY_CLOSE\n");
	}

	// Compiling shaders
	GLuint vertex_ID, fragment_ID;

	vertex_ID = bglCreateShader(GL_VERTEX_SHADER);
	bglShaderSource(vertex_ID, 1, (const GLchar**)&vertex, NULL);
	bglCompileShader(vertex_ID);
	checkCompileErrors(vertex_ID, "VERTEX");

	fragment_ID = bglCreateShader(GL_FRAGMENT_SHADER);
	bglShaderSource(fragment_ID, 1, (const GLchar**)&fragment, NULL);
	bglCompileShader(fragment_ID);
	checkCompileErrors(fragment_ID, "VERTEX");

	free(vertex);
	free(fragment);

	// Create and linking programm
	program = bglCreateProgram();
	bglAttachShader(program, vertex_ID);
	bglAttachShader(program, fragment_ID);
	bglLinkProgram(program);
	checkCompileErrors(program, "PROGRAM");

	// Deleting shaders
	bglDeleteShader(vertex_ID);
	bglDeleteShader(fragment_ID);
}

void useProgram()
{
	bglUseProgram(program);
}

void setUniformMat4x4(const char* name, const GLfloat* value)
{
	bglUniformMatrix4fv(bglGetUniformLocation(program, name), 1, GL_FALSE, value);
}

void checkCompileErrors(unsigned int shader, const char* type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		bglGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			bglGetShaderInfoLog(shader, 1024, NULL, infoLog);
			printf("ERROR::SHADER_COMPILATION_ERROR of type: %s\n", type);
			printf("%s", infoLog);
			printf("\n -- --------------------------------------------------- -- \n");
		}
	}
	else
	{
		bglGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			bglGetShaderInfoLog(shader, 1024, NULL, infoLog);
			printf("ERROR::PROGRAM_LINKING_ERROR of type: %s\n", type);
			printf("%s", infoLog);
			printf("\n -- --------------------------------------------------- -- \n");
		}
	}
}