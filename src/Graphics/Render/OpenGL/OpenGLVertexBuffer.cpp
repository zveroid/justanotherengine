#include "stdafx.h"

#include <GL/glew.h>

#include "Graphics/Render/OpenGL/OpenGLVertexBuffer.h"

namespace jaengine
{

	COpenGLVertexBuffer::COpenGLVertexBuffer()
	{
		glGenBuffers(1, &m_Handle);
	}


	COpenGLVertexBuffer::~COpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_Handle);
	}

	void COpenGLVertexBuffer::BufferData(void* _data, u32 _count, VertexBufferDataType _type)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_Handle);
		glBufferData(GL_VERTEX_ARRAY, _count * 3 * sizeof(f32), _data, GL_DYNAMIC_DRAW);
	}
}