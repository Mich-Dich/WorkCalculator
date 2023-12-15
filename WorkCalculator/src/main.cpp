
#include "pch.h"
#include "application.h"

int main() {

	Application* app = new Application();
	app->Run();
	delete app;
}
