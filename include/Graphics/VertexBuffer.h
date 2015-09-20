#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

namespace jaengine
{

	class CVertexBuffer
	{
	public:
		enum VertexBufferDataType
		{
			VBDT_VERTICES = 0,
		};

		CVertexBuffer();
		virtual ~CVertexBuffer();

		u32	GetHandle() { return m_Handle; }

		virtual void BufferData(void* _data, u32 _count, VertexBufferDataType _type) = 0;


	protected:
		u32 m_Handle;
	};

}

#endif VERTEXBUFFER_H
