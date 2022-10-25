#include <stdlib.h>
#include "glbuffers.h"

typedef struct _BufferObjectData
{
	GLsizei size;
	GLuint ID;
} BufferObjectData;

static size_t vbo_hadlebuffer_size = 4096;
static size_t ebo_hadlebuffer_size = 4096;
static size_t tex_hadlebuffer_size = 4096;

static BufferObjectData* VBOhandles = NULL;
static BufferObjectData* EBOhandles = NULL;
static BufferObjectData* TEXhandles = NULL;

static unsigned int vbo_handles_count = 0;
static unsigned int ebo_handles_count = 0;
static unsigned int tex_handles_count = 0;

void glBufferObjectsInit()
{
	VBOhandles = malloc(sizeof(BufferObjectData) * vbo_hadlebuffer_size);
	EBOhandles = malloc(sizeof(BufferObjectData) * ebo_hadlebuffer_size);
	TEXhandles = malloc(sizeof(BufferObjectData) * tex_hadlebuffer_size);
}

void glBufferObjectsClear()
{
	if (vbo_handles_count)
	{
		for (int i = 0; i < vbo_handles_count; i++)
		{
			bglDeleteBuffers(VBOhandles[i].size, &VBOhandles[i].ID);
		}
		vbo_handles_count = 0;
		vbo_hadlebuffer_size = 0;
		free(VBOhandles);
	}

	if (ebo_handles_count)
	{
		for (int i = 0; i < ebo_handles_count; i++)
		{
			bglDeleteBuffers(EBOhandles[i].size, &EBOhandles[i].ID);
		}
		ebo_handles_count = 0;
		ebo_hadlebuffer_size = 0;
		free(EBOhandles);
	}

	if (tex_handles_count)
	{
		for (int i = 0; i < tex_handles_count; i++)
		{
			bglDeleteBuffers(TEXhandles[i].size, &TEXhandles[i].ID);
		}
		tex_handles_count = 0;
		tex_hadlebuffer_size = 0;
		free(TEXhandles);
	}
}

void pushVBO_ID(GLsizei size, GLuint VBO)
{
	if (vbo_handles_count >= vbo_hadlebuffer_size)
	{
		if (!VBOhandles || !vbo_hadlebuffer_size)
		{
			vbo_hadlebuffer_size = 4096;
			VBOhandles = (BufferObjectData*)malloc(vbo_hadlebuffer_size * sizeof(BufferObjectData));
		}
		else
			VBOhandles = (BufferObjectData*)realloc(VBOhandles, sizeof(BufferObjectData) * vbo_hadlebuffer_size * 2);
	}

	BufferObjectData tmp;
	tmp.size = size;
	tmp.ID = VBO;

	VBOhandles[vbo_handles_count++] = tmp;
}

void pushEBO_ID(GLsizei size, GLuint EBO)
{
	if (ebo_handles_count >= ebo_hadlebuffer_size)
	{
		if (!EBOhandles || !ebo_hadlebuffer_size)
		{
			ebo_hadlebuffer_size = 4096;
			EBOhandles = (BufferObjectData*)malloc(ebo_hadlebuffer_size * sizeof(BufferObjectData));
		}
		else
			EBOhandles = (BufferObjectData*)realloc(EBOhandles, sizeof(BufferObjectData) * ebo_hadlebuffer_size * 2);
	}

	BufferObjectData tmp;
	tmp.size = size;
	tmp.ID = EBO;

	EBOhandles[ebo_handles_count++] = tmp;
}

void pushTEX_ID(GLsizei size, GLuint TEX)
{
	if (tex_handles_count >= tex_hadlebuffer_size)
	{
		if (!TEXhandles || !tex_hadlebuffer_size)
		{
			tex_hadlebuffer_size = 4096;
			TEXhandles = (BufferObjectData*)malloc(tex_hadlebuffer_size * sizeof(BufferObjectData));
		}
		else
			TEXhandles = (BufferObjectData*)realloc(TEXhandles, sizeof(BufferObjectData) * tex_hadlebuffer_size * 2);
	}

	BufferObjectData tmp;
	tmp.size = size;
	tmp.ID = TEX;

	TEXhandles[tex_handles_count++] = tmp;
}