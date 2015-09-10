#include "Types.h"
#include "Core/Device/Device.h"
#ifdef WIN32
#include <Windows.h>
#include "Core/Device/Win32Device.h"
#endif
#include "Core/Render/Render.h"
#include "Core/Application.h"

CApplication::CApplication() : 
	m_Device(new OSDevice)
{

}

CApplication::~CApplication()
{

}

bool CApplication::Init()
{
	bool result = true;

	result &= m_Device->Init();
	return result;
}

bool CApplication::Deinit()
{
    return false;
}

void CApplication::Update()
{
	m_Device->Update();
}
