#pragma once

#include "fileSystem/fileSystem.h"

class Application {

public:
	Application();
	virtual ~Application();

	void Run();
	void Shutdown();

private:

	bool m_Running = true;
	static General_Settings m_General_Settings;
	static Job_Settings m_Job_Settings;

};

Application* CreateApplication();