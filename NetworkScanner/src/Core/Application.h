#pragma once

#include "Core/Scanner.h"

namespace NS {

	enum class Platform
	{
		Windows = 0, MacOS, Linux
	};

	class Application
	{
	public:
		Application();
		~Application();

		void Run();

		inline Platform GetCurrentPlatform() const { return m_CurrentPlatform; }

		static Application* GetApplication() { return s_App; }

	private:
		void SetCurrentPlatform();

	private:
		std::shared_ptr<Scanner> m_Scanner;
		Platform m_CurrentPlatform;

		bool m_Running = true;

	public:
		static Application* s_App;
	};

}
