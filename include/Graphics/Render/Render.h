#ifndef RENDER_H
#define RENDER_H

namespace jaengine
{

	class IRender
	{
	public:
		enum RenderType
		{
			RT_OPENGL,
			RT_DIRECTX9,
			RT_DIRECTX11
		};

		virtual bool Init(IDevice* _device) = 0;
		virtual void Deinit() = 0;
		virtual void Draw() = 0;
	};

}

#endif // RENDER_H

