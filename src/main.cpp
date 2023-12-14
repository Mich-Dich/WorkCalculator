
#include "pch.h"
#include "application.h"

int main(int argc, char** argv) {

	Application* app = CreateApplication();
	app->Run();
	app->Shutdown();
	delete app;
}
