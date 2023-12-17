#include "pch.h"
#include "WorkRecord.h"

#include "core/fileSystem.h"

//
WorkRecord::WorkRecord() {

    Load_WorkRecords(m_Records);
}

//
WorkRecord::~WorkRecord() {

}


//
bool WorkRecord::Add_Record(WorkRecord_Day newRecord, std::vector<WorkRecord_Day>& recordArray, const Job_Settings& locJobSettings) {

    GL_VALIDATE(Validate_Work_Day_Data(newRecord), "", INVALID_VAR_MSG(newRecord), return false);

    newRecord.total_work_Time = calculateTimeDifference(newRecord.start_time, newRecord.end_time);
    Calc_Salary(newRecord, locJobSettings);

    recordArray.push_back(newRecord);
    Save_WorkRecords(recordArray);

    return true;
}

//
bool WorkRecord::Validate_Work_Day_Data(const WorkRecord_Day& WorkDay) {

    bool foundError = false;

    if (WorkDay.date.year < 2023 || WorkDay.date.year > 2100) {

        GL_LOG(Error, "Validate_Work_Day_Data() FAILED: Invalid Year");
        foundError = true;
    }

    if (WorkDay.date.month < 1 || WorkDay.date.month > 12) {

        GL_LOG(Error, "Validate_Work_Day_Data() FAILED: Invalid Month");
        foundError = true;
    }

    if (WorkDay.date.day < 1 || WorkDay.date.day > 31) {

        GL_LOG(Error, "Validate_Work_Day_Data() FAILED: Invalid Day");
        foundError = true;
    }

    if (WorkDay.start_time.hour < 0 || WorkDay.start_time.hour > 24) {

        GL_LOG(Error, "Validate_Work_Day_Data() FAILED: Invalid Start Time Hour");
        foundError = true;
    }

    if (WorkDay.start_time.min < 0 || WorkDay.start_time.min > 60) {

        GL_LOG(Error, "Validate_Work_Day_Data() FAILED: Invalid Start Time Min");
        foundError = true;
    }

    if (WorkDay.end_time.hour < 0 || WorkDay.end_time.hour > 24) {

        GL_LOG(Error, "Validate_Work_Day_Data() FAILED: Invalid End Time Hour");
        foundError = true;
    }

    if (WorkDay.end_time.min < 0 || WorkDay.end_time.min > 60) {

        GL_LOG(Error, "Validate_Work_Day_Data() FAILED: Invalid End Time Min");
        foundError = true;
    }


    return !foundError;
}


//
void WorkRecord::Calc_Salary(WorkRecord_Day& record, const Job_Settings& locJobSettings) {

    int TotlaMinutes = (record.total_work_Time.hour * 60) + record.total_work_Time.min;
    record.salary = (static_cast<double>(TotlaMinutes) / 60.0) * static_cast<double>(locJobSettings.pay_per_h);

    int Record_End_work = (record.end_time.hour * 60) + record.end_time.min;
    int Evening_Start = (locJobSettings.Evening_pay_start_time.hour * 60) + locJobSettings.Evening_pay_start_time.min;
    int Night_Start = (locJobSettings.Night_pay_start_time.hour * 60) + locJobSettings.Night_pay_start_time.min;

    if (Record_End_work > Evening_Start) {

        Time_Point OverLimit = calculateTimeDifference(locJobSettings.Evening_pay_start_time, record.end_time);
        record.salary += OverLimit.hour * (locJobSettings.pay_per_h * locJobSettings.pay_increase_evening)
            + (static_cast<double>(OverLimit.min) / 60.0) * (locJobSettings.pay_per_h * locJobSettings.pay_increase_evening);
    }

    if (Record_End_work > Night_Start) {

        Time_Point OverLimit = calculateTimeDifference(locJobSettings.Night_pay_start_time, record.end_time);
        record.salary += OverLimit.hour * (locJobSettings.pay_per_h * (locJobSettings.pay_increase_night - locJobSettings.pay_increase_evening))
            + (static_cast<double>(OverLimit.min) / 60.0) * (locJobSettings.pay_increase_night - locJobSettings.pay_increase_evening);
    }

    //GL_LOG(Debug, "Salary: " << record.salary);
}

//
void WorkRecord::Clear_Records() {

    m_Records.clear();
    Save_WorkRecords(m_Records);
}

// ----------------------------------------------------------------------- Time Calc -----------------------------------------------------------------------

//
Time_Point calculateTimeDifference(const Time_Point& startTime, const Time_Point& endTime) {

    Time_Point difference;

    int totalMinutes = (endTime.hour - startTime.hour) * 60 + (endTime.min - startTime.min);
    difference.hour = totalMinutes / 60;
    difference.min = totalMinutes % 60;

    return difference;
}

//
void Add_Time_Points(Time_Point& target, const Time_Point& second) {

    int totalMinutes = (target.hour + second.hour) * 60 + (target.min + second.min);
    target.hour = totalMinutes / 60;
    target.min = totalMinutes % 60;
}