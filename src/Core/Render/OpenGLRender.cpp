#include <Windows.h>
#include <gl/GL.h>

#include "Types.h"
#include "Core/Device/Win32Device.h"
#include "Core/Render/OpenGLRender.h"

COpenGLRender::COpenGLRender() :
#ifdef WIN32
	m_RenderContext(0)
#endif // WIN32
{

}

COpenGLRender::~COpenGLRender()
{
}

bool COpenGLRender::Init(IDevice* _device)
{
#ifdef WIN32
    return InitWin32((CWin32Device*)_device);
#else
#	error "Not supported platform!"
#endif
}

void COpenGLRender::Deinit()
{
	if (m_RenderContext)
	{
		wglDeleteContext(m_RenderContext);
		m_RenderContext = 0;
	}
}

void COpenGLRender::Draw()
{
}

#ifdef WIN32
bool COpenGLRender::InitWin32(CWin32Device* _device)
{
	m_RenderContext = wglCreateContext(_device->GetDeviceContext());
	if (!m_RenderContext)
		return false;

	if (!wglMakeCurrent(_device->GetDeviceContext(), m_RenderContext))
	{
		wglDeleteContext(m_RenderContext);
		return false;
	}

	typedef BOOL(WINAPI * PFNWGLSWAPINTERVALEXTPROC) (int interval);
	PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;
	// vsync extension
	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
	// set vsync
	if (wglSwapIntervalEXT)
		wglSwapIntervalEXT(0);

	return true;
}
#endif
