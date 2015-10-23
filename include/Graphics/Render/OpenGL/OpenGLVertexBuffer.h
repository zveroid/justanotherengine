#ifndef OPENGLVERTEXBUFFER_H
#define OPENGLVERTEXBUFFER_H

#include "Graphics/VertexBuffer.h"

namespace jaengine
{

	class COpenGLVertexBuffer :
		public IVertexBuffer
	{
	public:
		COpenGLVertexBuffer();
		virtual ~COpenGLVertexBuffer();

		virtual void BufferData(void* _data, u32 _count, VertexBufferDataType _type);
	};

}

#endif //OPENGLVERTEXBUFFER_H
