#pragma once

#include <string>
#include <sstream>

struct General_Settings {
	bool DarkMode;
	uint16_t fontSize;
};

struct Time_Point {
	int hour;
	int min;
};

struct Time_point_date {
	int year;
	int month;
	int day;
	int hour;
	int min;
};

struct Job_Settings {
	float pay_per_h;						// hourly pay (standart)
	float pay_per_h_evening;				// hourly reate for evenings (increased pay)
	Time_Point Eving_pay_start_time;		// from what time do you get evening pay
	int max_h_per_month;					// max working hours per month
	int max_h_per_week;						// max working hours per week
};

void TestFileSysstem();

void Save_General_Settings(General_Settings settings);