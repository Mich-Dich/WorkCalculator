
#include "pch.h"
#include "application.h"

//
Application::Application() {}

//
Application::~Application() {}

//
void Application::Run() {

	while (1) {}
}

//
void Application::Shutdown() {}

//
Application* CreateApplication() {

	return new Application();
}
