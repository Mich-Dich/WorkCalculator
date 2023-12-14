#include "pch.h"

#include "core/Logger.h"

#include "application.h"

//
Application::Application() {

	Logger::Log_Init("mainLogFile.txt", "[$B$T:$J$E] [$B$L$X - $A - $F:$G$E] $C$Z");
	// Create Window

}

//
Application::~Application() {}

//
void Application::Run() {
	
	General_Settings settings = {true, 16};
	Save_General_Settings(settings);
	Test_Time_System();
}

//
void Application::Shutdown() {}

//
Application* CreateApplication() {

	return new Application();
}
