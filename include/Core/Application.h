#ifndef APPLICATION_H
#define APPLICATION_H

class IDevice;
class IRender;

class CApplication
{
public:
    CApplication();
    virtual ~CApplication();

    bool Init();
    bool Deinit();

    void Update();

	IDevice*	GetDevice() const { return m_Device; }
	IRender*	GetRender() const { return m_Render; }

private:
	IDevice*	m_Device;
	IRender*	m_Render;
};

#endif // CApplication_H
