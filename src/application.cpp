#include "pch.h"

#include <fstream>
#include <filesystem>

#include "application.h"

//
Application::Application() {

	// Create Window

}

//
Application::~Application() {}

//
void Application::Run() {
	
	General_Settings settings = {true, 16};
	Save_General_Settings(settings);
}

//
void Application::Shutdown() {}

//
Application* CreateApplication() {

	return new Application();
}
