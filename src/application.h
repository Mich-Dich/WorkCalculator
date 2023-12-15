#pragma once

#include "WorkRecord.h"

#include "HUD/imgui_hud.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

// ---------------------------------- Settings ----------------------------------

struct General_Settings {
	int Struct_Version = 1;
	bool DarkMode;
	uint16_t fontSize;
};

// MOVE TO WorkRecord.h
struct Job_Settings {
	int Struct_Version = 1;
	double pay_per_h;						// hourly pay (standart)
	double pay_increase_evening;			// hourly reate for evenings (increased pay)
	Time_Point Evening_pay_start_time;		// from what time do you get evening pay
	double pay_increase_night;				// hourly reate for evenings (increased pay)
	Time_Point Night_pay_start_time;		// from what time do you get night pay
	double max_h_per_month;					// max working hours per month
	int max_h_per_week;						// max working hours per week
};

class Application {

public:
	Application();
	virtual ~Application();

	void Run();
	void Shutdown();

private:

	Time_point_date Get_Time();
	bool m_Running = true;

	GLFWwindow* m_Window;
	imgui_hud* m_HUD;
	General_Settings m_General_Settings;
	Job_Settings m_Job_Settings;
	WorkRecord* m_WorkRecord;
};