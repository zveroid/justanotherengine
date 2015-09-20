#ifndef DEVICE_H
#define DEVICE_H

namespace jaengine
{

	class IDevice
	{
	public:
		virtual bool Init() = 0;
		virtual void Deinit() = 0;
		virtual void Update() = 0;

		virtual void SetWidth(u32 _width) { m_Width = _width; }
		virtual void SetHeight(u32 _height) { m_Height = _height; }

	protected:
		u32				m_Width;
		u32				m_Height;
	};

}

#endif //DEVICE_H
