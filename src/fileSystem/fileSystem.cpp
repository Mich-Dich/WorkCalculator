#include "pch.h"

#include "fileSystem.h"

#include <chrono>
#include <ctime>

static const std::string General_settings_File_Name = "settings/General_settings.txt";
static const std::string Job_settings_File_Name = "settings/data.txt";
static const std::string Save_File_Name = "saves/data.txt";

std::tm fill_tm_struct(const Time_point_date& date);

void Save_General_Settings(General_Settings settings) {

	std::ofstream outFile(General_settings_File_Name, std::ios::binary);
	GL_VALIDATE(outFile.is_open(), "file: [" << General_settings_File_Name << "] is open", "FAILED to open file: [" << General_settings_File_Name << "]", );

	outFile.write(reinterpret_cast<char*>(&settings), sizeof(General_Settings));
	outFile.close();
}

void Test_Time_System() {

	// Get the current time
	auto currentTimePoint = std::chrono::system_clock::now();
	std::time_t currentTime = std::chrono::system_clock::to_time_t(currentTimePoint);
	std::tm* timeInfo = std::localtime(&currentTime);

	GL_LOG(Trace, "Current time: " << std::put_time(timeInfo, "%Y-%m-%d %H:%M:%S"));
	GL_LOG(Debug, "Week-day: " << (timeInfo->tm_wday + 6) % 7);



    Time_point_date date = { 2023, 12, 14 };

    std::tm ClactimeInfo = fill_tm_struct(date);


    GL_LOG(Trace, "Year: " << ClactimeInfo.tm_year + 1900);
    GL_LOG(Trace, "Month: " << ClactimeInfo.tm_mon + 1);
    GL_LOG(Trace, "Day: " << ClactimeInfo.tm_mday);
    GL_LOG(Trace, "Day of the week: " << (ClactimeInfo.tm_wday + 6) % 7);

}


std::tm fill_tm_struct(const Time_point_date& date) {

    std::tm timeInfo = {};
    timeInfo.tm_year = date.year - 1900;  // Years since 1900
    timeInfo.tm_mon = date.month - 1;     // Months since January (0-based)
    timeInfo.tm_mday = date.day;
    timeInfo.tm_hour = 0;
    timeInfo.tm_min = 0;
    timeInfo.tm_sec = 0;
    timeInfo.tm_yday = 0;

    std::chrono::system_clock::time_point timePoint = std::chrono::system_clock::from_time_t(std::mktime(&timeInfo));

    std::chrono::duration<int, std::ratio<60 * 60 * 24>> one_day(1);
    std::chrono::duration<int, std::ratio<60 * 60 * 24 * 7>> one_week(1);

    std::chrono::hours hours_since_sunday = std::chrono::duration_cast<std::chrono::hours>(timePoint.time_since_epoch()) % one_week;
    timeInfo.tm_wday = static_cast<int>(hours_since_sunday.count() / 24);  // Days since Sunday

    return timeInfo;
}