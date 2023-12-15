#include "pch.h"
#include "application.h"
#include "core/fileSystem.h"

#include <chrono>
#include <ctime>


using namespace std;

//
Application::Application() {

	Logger::Log_Init("mainLogFile.txt", "[$B$T:$J$E] [$B$L$X - $A - $F:$G$E] $C$Z");
    m_WorkRecord = new WorkRecord();
    m_HUD = new imgui_hud();

    if (!Try_loading_General_Settings(m_General_Settings)) {

        std::string buffer;
        GL_LOG(Warn, "Failed to load Job_Settings");

        std::cout << "  Enter Darkmode(Y/N): ";
        std::cin >> buffer;
        m_General_Settings.DarkMode = (buffer == "Y") ? true: false;

        std::cout << "  Enter FontSize: ";
        std::cin >> m_General_Settings.fontSize;

        Save_General_Settings(m_General_Settings);
    }

    if (!Try_loading_Job_Settings(m_Job_Settings)) {

        GL_LOG(Warn, "Failed to load Job_Settings");

        std::cout << "  Enter pay_per_h: ";
        std::cin >> m_Job_Settings.pay_per_h;

        std::cout << "  Enter pay_increase_evening(0-1): ";
        std::cin >> m_Job_Settings.pay_increase_evening;

        std::cout << "  Enter Eving_pay_start_time: ";
        std::cin >> m_Job_Settings.Evening_pay_start_time.min;
        m_Job_Settings.Evening_pay_start_time.hour = (m_Job_Settings.Evening_pay_start_time.min / 100);
        m_Job_Settings.Evening_pay_start_time.min = (m_Job_Settings.Evening_pay_start_time.min % 100);

        std::cout << "  Enter pay_increase_night(0-1): ";
        std::cin >> m_Job_Settings.pay_increase_night;

        std::cout << "  Enter Night_pay_start_time.hour: ";
        std::cin >> m_Job_Settings.Night_pay_start_time.min;
        m_Job_Settings.Night_pay_start_time.hour = (m_Job_Settings.Night_pay_start_time.min / 100);
        m_Job_Settings.Night_pay_start_time.min = (m_Job_Settings.Night_pay_start_time.min % 100);

        std::cout << "  Enter max_h_per_month: ";
        std::cin >> m_Job_Settings.max_h_per_month;

        std::cout << "  Enter max_h_per_week: ";
        std::cin >> m_Job_Settings.max_h_per_week;

        Save_Job_Settings(m_Job_Settings);
    }

	// Setup Window
    GL_ASSERT(glfwInit(), "", "[glfwInit] FAILED");

    const char* glsl_version = "#version 330 core";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // Create Window with graphics Context
    m_Window = glfwCreateWindow(1280, 720, "Work Calculator", NULL, NULL);
    GL_ASSERT(m_Window != NULL, "", "Failed to Create Window");

    glfwMakeContextCurrent(m_Window);
    glfwSwapInterval(1);    // Enable VSync

    GL_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "", "Unable to Context to OpenGL");   // tie window context to glad's opengl funcs

    int Screen_Width, Screen_Height;
    glfwGetFramebufferSize(m_Window, &Screen_Width, &Screen_Height);
    glViewport(0, 0, Screen_Width, Screen_Height);

    m_HUD->Init(m_Window, glsl_version);
}

//
Application::~Application() {}

//
void Application::Run() {


    while (!glfwWindowShouldClose(m_Window)) {

        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        m_HUD->NewFrame();
        m_HUD->Update();
        m_HUD->Render();
        glfwSwapBuffers(m_Window);
    }

    /*
    std::string ConsoleCommand;
    while (m_Running) {

        std::cout << std::endl << "Enter a Command: ";
        std::cin >> ConsoleCommand;

        for (char& c : ConsoleCommand)
            c = std::tolower(c);

        // add an entry to array
        if (ConsoleCommand == "add") {

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard remaining characters


            std::string input;
            std::cout << "Enter a date and time string (e.g., 2023-12-15 1600-1900): ";
            std::getline(std::cin, input);
            std::istringstream iss(input);

            WorkRecord_Day LocWorkDay;

            // Extracting values using getline and substr
            iss >> LocWorkDay.date.year;
            iss.ignore(); // Ignore the '-' separator
            iss >> LocWorkDay.date.month;
            iss.ignore(); // Ignore the '-' separator
            iss >> LocWorkDay.date.day;

            iss >> LocWorkDay.start_time.min;
            LocWorkDay.start_time.hour = (LocWorkDay.start_time.min / 100);
            LocWorkDay.start_time.min = (LocWorkDay.start_time.min % 100);
            iss.ignore(); // Ignore the '-' separator
            iss >> LocWorkDay.end_time.min;
            LocWorkDay.end_time.hour = (LocWorkDay.end_time.min / 100);
            LocWorkDay.end_time.min = (LocWorkDay.end_time.min % 100);

            GL_VALIDATE(m_WorkRecord->Add_Record(LocWorkDay, m_WorkRecord->m_Records, m_Job_Settings), "", "[m_WorkRecord->Add_Record] FAILED", );

        }

        // display a list (filtered by month and all)
        else if (ConsoleCommand == "list" || ConsoleCommand == "list_all") {

            std::cout << "Max number of records: " << m_WorkRecord->m_Records.size() << std::endl;

            bool filter = ConsoleCommand == "list";
            Time_Point Total_Time{};
            double Total_Salary = 0;

            for (const WorkRecord_Day& record : m_WorkRecord->m_Records) {

                if (filter && (record.date.month != Get_Time().month))
                    continue;

                std::cout << record.date.year << "-" << record.date.month << "-" << record.date.day
                    << std::setw(8) << std::right << "[" << PRINT_TIME_POINT(record.start_time) << " - " << PRINT_TIME_POINT(record.end_time) << "]"
                    << " [total: " << PRINT_TIME_POINT(record.total_work_Time) << "]" << std::setw(16) << "Salary: " << record.salary << std::endl;

                Add_Time_Points(Total_Time, record.total_work_Time);
                Total_Salary += record.salary;
            }
            std::cout << "  Total [time: " << PRINT_TIME_POINT(Total_Time) << "]   [Salary: " << Total_Salary << "]" << std::endl;
        }

        // Clear array 
        else if (ConsoleCommand == "clear") {

            m_WorkRecord->Clear_Records();
            std::cout << "Cleared Content of [m_Records]";
        }

        // help
        else if (ConsoleCommand == "h" || ConsoleCommand == "help")
            std::cout << "Possible Command are: add, clear, list, list all, exit";

        // exit
        else if (ConsoleCommand == "exit")
            m_Running = false;

        // INVALID command
        else
            std::cout << "INVALID Command" << std::endl;
    }
*/
}

//
void Application::Shutdown() {

    m_HUD->Shutdown();
    m_HUD->Shutdown();
    delete m_HUD;
    delete m_WorkRecord;
}

Time_point_date Application::Get_Time() {

    // Get the current time
    auto currentTimePoint = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(currentTimePoint);
    std::tm* timeInfo = std::localtime(&currentTime);

    Time_point_date TimeNow = {timeInfo->tm_year + 1900, timeInfo->tm_mon + 1, timeInfo->tm_mday};

    return TimeNow;
}
