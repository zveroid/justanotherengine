#include "Types.h"
#include "Core/Device/Device.h"
#ifdef WIN32
#include <Windows.h>
#include "Core/Device/Win32Device.h"
#endif
#include "Core/Render/Render.h"
#include "Core/Render/OpenGLRender.h"
#include "Core/Application.h"

CApplication* CApplication::m_Instance = 0;

CApplication::CApplication() : 
	m_Device(new OSDevice)
	, m_Render(0)
	, m_RenderType(IRender::RT_OPENGL)
	, m_State(AS_NONE)
{
	m_Instance = this;
}

CApplication::~CApplication()
{
	Deinit();
	delete m_Render;
	delete m_Device;
}

bool CApplication::Init()
{
	bool result = true;

	result &= m_Device->Init();
	if (!result)
		return false;

	switch (m_RenderType)
	{
	case IRender::RT_OPENGL:
		m_Render = new COpenGLRender;
		break;
	default:
		return false;
	}
	result &= m_Render->Init(m_Device);

	m_State = result ? AS_RUNNING : AS_NONE;

	return result;
}

void CApplication::Deinit()
{
	if (m_Render)
	{
		m_Render->Deinit();
	}
	if (m_Device)
	{
		m_Device->Deinit();
	}
}

void CApplication::Update()
{
	if (!IsRunning())
		return;

	m_Device->Update();
	m_Render->Draw();
}
