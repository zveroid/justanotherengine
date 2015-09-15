#ifndef WIN32DEVICE_H
#define WIN32DEVICE_H

#include "Core/Device/Device.h"

class CWin32Device :
	public IDevice
{
public:
	CWin32Device();
	virtual ~CWin32Device();

	virtual bool Init() override;
	virtual void Deinit() override;
	virtual void Update() override;
	HWND		 GetWindowHandler() { return m_WindowHandler; }
	HDC			 GetDeviceContext() { return m_DeviceContext; }

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	HWND	m_WindowHandler;
	HDC		m_DeviceContext;

	bool	m_Fullscreen;

	HKL		m_KeyboardLayout;
	u32		m_KeyboardCodepage;
};

using OSDevice = CWin32Device;

#endif //WIN32DEVICE_H
