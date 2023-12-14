#include "pch.h"

#include "fileSystem.h"

#include <chrono>
#include <ctime>

static const std::string General_settings_File_Name = "settings/General_settings.txt";
static const std::string Job_settings_File_Name = "settings/data.txt";
static const std::string Save_File_Name = "saves/data.txt";


void Save_General_Settings(General_Settings settings) {

	std::ofstream outFile(General_settings_File_Name, std::ios::binary);
	GL_VALIDATE(outFile.is_open(), "file: [" << General_settings_File_Name << "] is open", "FAILED to open file: [" << General_settings_File_Name << "]", );

	outFile.write(reinterpret_cast<char*>(&settings), sizeof(General_Settings));
	outFile.close();
}

void TestFileSysstem() {

	std::ofstream outFile(General_settings_File_Name, std::ios::binary);
	GL_VALIDATE(outFile.is_open(), "file: [" << General_settings_File_Name << "] is open", "FAILED to open file: [" << General_settings_File_Name << "]", );

	/*outFile.write(reinterpret_cast<char*>(), sizeof());

	outFile << "This is my dummy data" << std::endl;
	outFile << 42 << std::endl;
	outFile << 3.1415 << std::endl;
	outFile.close();
	*/

	// Get the current time
	auto currentTimePoint = std::chrono::system_clock::now();
	std::time_t currentTime = std::chrono::system_clock::to_time_t(currentTimePoint);
	std::tm* timeInfo = std::localtime(&currentTime);

	GL_LOG(Trace, "Current time: " << std::put_time(timeInfo, "%Y-%m-%d %H:%M:%S"));

}
