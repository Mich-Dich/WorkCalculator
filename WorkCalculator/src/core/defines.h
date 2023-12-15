#pragma once

struct Time_Point {
	int hour;
	int min;
};

struct Time_point_date {
	int year;
	int month;
	int day;
};


#define SET_TEXT_SIZE(size)					std::setw(size) << std::setfill('0') << std::right
#define PRINT_TIME_POINT(timePoint)			SET_TEXT_SIZE(2) << timePoint.hour << ":" << SET_TEXT_SIZE(2) << timePoint.min << std::setfill(' ')
