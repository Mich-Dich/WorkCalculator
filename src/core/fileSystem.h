#pragma once

#include "application.h"


void Test_Time_System();
void Save_General_Settings(General_Settings settings);
void Save_Job_Settings(Job_Settings settings);

bool Try_loading_General_Settings(General_Settings& inGeneral_Settings);
bool Try_loading_Job_Settings(Job_Settings& inJob_Settings);

bool Save_WorkRecords(const std::vector<WorkRecord_Day>& records);
bool Load_WorkRecords(std::vector<WorkRecord_Day>& records);
