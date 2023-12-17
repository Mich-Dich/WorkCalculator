#pragma once

struct Job_Settings; // Forward declaration

struct WorkRecord_Day {
	Time_point_date date;
	Time_Point start_time;
	Time_Point end_time;
	Time_Point total_work_Time;
	double salary;

	WorkRecord_Day()
		: date({ 0, 0, 0 }), start_time({ 0, 0 }), end_time({ 0, 0 }), total_work_Time({ 0, 0 }), salary(0.0) {}

	WorkRecord_Day(const Time_point_date date, const Time_Point start_time, const Time_Point end_time)
		: date(date), start_time(start_time), end_time(end_time), total_work_Time({ 0, 0 }), salary(0.0) {}
};

struct WorkRecord_Week {
	float hours_Worked;
	float salary;
	std::vector<WorkRecord_Day> worked_Days;
};

struct WorkRecord_Month {
	float hours_worked;
	float salary;
	std::vector<WorkRecord_Week> worked_Weeks;
};


class WorkRecord {

public:
	WorkRecord();
	~WorkRecord();

	bool Add_Record(WorkRecord_Day newRecord, std::vector<WorkRecord_Day>& recordArray, const Job_Settings& locJobSettings);
	bool Validate_Work_Day_Data(const WorkRecord_Day& WorkDay);
	void Calc_Salary(WorkRecord_Day& record, const Job_Settings& locJobSettings);
	void Clear_Records();

	std::vector<WorkRecord_Day> m_Records = {};

private:

};


Time_Point calculateTimeDifference(const Time_Point& startTime, const Time_Point& endTime);
void Add_Time_Points(Time_Point& target, const Time_Point& second);
