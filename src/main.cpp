
#include "pch.h"
#include "application.h"

int main(int argc, char** argv) {

	Application* app = new Application();
	app->Run();
	delete app;
}
