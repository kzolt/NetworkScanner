#include "pch.h"
#include "Application.h"

namespace NS {
	
	Application* Application::s_App = nullptr;

	Application::Application()
	{
		s_App = this;
		SetCurrentPlatform();

		NS::Log::Init();
		NS_INFO("Log Initialized");

		m_Scanner = Scanner::Create();
		if (!m_Scanner->Init())
		{
			m_Running = false;
			return;
		}
	}

	Application::~Application()
	{
		m_Scanner->Shutdown();
	}

	void Application::Run()
	{
		if (!m_Running)
			return;

		m_Scanner->PrintVendorInfo();
	}

	void Application::SetCurrentPlatform()
	{
		#ifdef NS_PLATFORM_WINDOWS
			m_CurrentPlatform = Platform::Windows;
		#elif NS_PLATFORM_MACOS
            m_CurrentPlatform = Platform::MacOS;
        #else
			NS_WARN("Currently only windows is supported!");
		#endif
	}

}

