#ifndef APPLICATION_H
#define APPLICATION_H

#include "Graphics/Render/Render.h"

namespace jaengine
{

	class IDevice;

	class CApplication
	{
	public:
		CApplication();
		virtual ~CApplication();

		static CApplication* GetInstance() { return m_Instance; }

		bool Init();
		void Deinit();

		void Update();

		bool IsRunning() { return m_State == AS_RUNNING; }
		void Quit() { m_State = AS_CLOSED; }
		void Pause() { m_State = AS_PAUSED; }
		void Resume() { m_State = AS_RUNNING; }

		IDevice*	GetDevice() const { return m_Device; }
		IRender*	GetRender() const { return m_Render; }

	private:
		enum ApplicationState
		{
			AS_NONE,
			AS_RUNNING,
			AS_PAUSED,
			AS_CLOSED
		};

		static CApplication*	m_Instance;

		IDevice*				m_Device;
		IRender*				m_Render;
		IRender::RenderType		m_RenderType;

		ApplicationState		m_State;
	};

}

#endif // CApplication_H
