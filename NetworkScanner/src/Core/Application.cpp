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
		m_Scanner->Init();
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{

	}

	void Application::SetCurrentPlatform()
	{
		#ifdef NS_PLATFORM_WINDOWS
			m_CurrentPlatform = Platform::Windows;
		#else
			NS_WARN("Currently only windows is supported!");
		#endif
	}

}

