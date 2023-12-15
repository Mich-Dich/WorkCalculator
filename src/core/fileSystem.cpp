#include "pch.h"

#include "fileSystem.h"

#include <chrono>
#include <ctime>

static const std::string General_settings_File_Name = "settings/General_settings.txt";
static const std::string Job_settings_File_Name = "settings/Job_settings.txt";
static const std::string Save_File_Name = "saves/data.txt";


//
void Test_Time_System() {

    Time_point_date date = { 2023, 12, 14 };
    
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
}

//
void Save_General_Settings(General_Settings settings) {

    std::ofstream outFile(General_settings_File_Name, std::ios::binary);
    GL_VALIDATE(outFile.is_open(), "", "FAILED to open file: [" << General_settings_File_Name << "]", );

    outFile.write(reinterpret_cast<char*>(&settings), sizeof(General_Settings));
    outFile.close();
}

//
void Save_Job_Settings(Job_Settings settings) {

    std::ofstream outFile(Job_settings_File_Name, std::ios::binary);
    GL_VALIDATE(outFile.is_open(), "", "FAILED to open file: [" << Job_settings_File_Name << "]", );

    outFile.write(reinterpret_cast<char*>(&settings), sizeof(Job_Settings));
    outFile.close();
}

//
bool Try_loading_General_Settings(General_Settings& inGeneral_Settings) {

    std::ifstream inFile(General_settings_File_Name, std::ios::binary);
    GL_VALIDATE(inFile.is_open(), "", "FAILED to open file: [" << General_settings_File_Name << "]", return false);

    inFile.read(reinterpret_cast<char*>(&inGeneral_Settings), sizeof(General_Settings));
    inFile.close();

    return true;
}

//
bool Try_loading_Job_Settings(Job_Settings& inJob_Settings) {

    std::ifstream inFile(Job_settings_File_Name, std::ios::binary);
    GL_VALIDATE(inFile.is_open(), "", "FAILED to open file: [" << General_settings_File_Name << "]", return false);

    inFile.read(reinterpret_cast<char*>(&inJob_Settings), sizeof(Job_Settings));
    inFile.close();

    int spacing = 30;

    return !(inJob_Settings.pay_per_h == 0.0f ||
        inJob_Settings.pay_increase_evening == 0.0f ||
        inJob_Settings.Evening_pay_start_time.hour == 0 ||
        inJob_Settings.pay_increase_night == 0.0f ||
        inJob_Settings.Night_pay_start_time.hour == 0 ||
        inJob_Settings.max_h_per_month == 0.0f ||
        inJob_Settings.max_h_per_week == 0);
}

//
bool Save_WorkRecords(const std::vector<WorkRecord_Day>& records) {

    std::ofstream outFile(Save_File_Name, std::ios::binary | std::ios::trunc);
    GL_VALIDATE(outFile.is_open(), "", "FAILED to open file: [" << Save_File_Name << "]", return false);

    size_t size = records.size();
    outFile.write(reinterpret_cast<char*>(&size), sizeof(size_t));

    for (const WorkRecord_Day& loopRecord : records)
        outFile.write(reinterpret_cast<const char*>(&loopRecord), sizeof(WorkRecord_Day));
    
    outFile.close();
    return true;
}

bool Load_WorkRecords(std::vector<WorkRecord_Day>& records) {

    std::ifstream inFile(Save_File_Name, std::ios::binary);
    GL_VALIDATE(inFile.is_open(), "", "FAILED to open file: [" << Save_File_Name << "]", records.clear(); return false);

    size_t size;
    inFile.read(reinterpret_cast<char*>(&size), sizeof(size_t));

    records.resize(size);
    inFile.read(reinterpret_cast<char*>(records.data()), size * sizeof(WorkRecord_Day));
    inFile.close();

    return true;

}
