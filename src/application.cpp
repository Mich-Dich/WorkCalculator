
#include <fstream>
#include <filesystem>

#include "pch.h"
#include "application.h"

#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>

static const std::string File_Name = "saves/data.txt";

//
Application::Application() {}

//
Application::~Application() {}

//
void Application::Run() {


	std::ofstream outFile(File_Name);
	GL_VALIDATE(outFile.is_open(), "file: [" << File_Name << "] is open", "FAILED to open file: [" << File_Name << "]", );

	outFile << "This is my dummy data" << std::endl;
	outFile << 42 << std::endl;
	outFile << 3.1415 << std::endl;
	outFile.close();


	// Get the current time
	auto currentTimePoint = std::chrono::system_clock::now();
	std::time_t currentTime = std::chrono::system_clock::to_time_t(currentTimePoint);
	std::tm* timeInfo = std::localtime(&currentTime);

	GL_LOG(Trace, "Current time: " << std::put_time(timeInfo, "%Y-%m-%d %H:%M:%S"));


	//while (1) {}
}

//
void Application::Shutdown() {}

//
Application* CreateApplication() {

	return new Application();
}
