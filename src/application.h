#pragma once

class Application {

public:
	Application();
	virtual ~Application();

	void Run();
	void Shutdown();

private:

	bool m_Running = true;

};

Application* CreateApplication();