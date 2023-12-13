#pragma once

#include <string>
#include <sstream>

#include "pch.h"

#define ENABLE_VALIDATION
#define ENABLED_ASSERTS

namespace Logger {

	enum LogMsgSeverity {
		Trace = 0,
		Debug = 1,
		Info = 2,
		Warn = 3,
		Error = 4,
		Fatal = 5,
		NUM_SEVERITIES = 6
	};
	static const char* SeperatorStringBig = "====================================================================================================================";
	static const char* SeperatorStringSmall = "--------------------------------------------------------------------------------------------------------------------";

	int Log_Init(const char* LogCoreFile, const char* LogFile, const char* Format);

	/*  Formating the LogMessages can be customised with the following tags
		to format all following Log Messages use: set_Formating(char* format);
		e.g. set_Formating("$B[$T] $L [$F]  $C$E")  or set_Formating("$BTime:[$M $S] $L $E ==> $C")

	$T		Time				hh:mm:ss
	$H		Hour				hh
	$M		Minute				mm
	$S		Secunde				ss
	$J		MilliSecunde		mm

	$N		Date				yyyy:mm:dd:
	$Y		Date Year			yyyy
	$O		Date Month			mm
	$D		Date Day			dd

	$F		Func. Name			main, foo
	$A		File Name			C:\Porject\main.c C:\Porject\foo.c
	$I		shortend File Name	main.c foo.c
	$G		Line				1, 42

	$L		LogLevel			[TRACE], [DEBUG] … [FATAL]
	$X		Alienment			add space for "INFO" & "WARN"
	$B		Color Begin			from here the color starts
	$E		Color End			from here the color ends
	$C		Text				Formated Message with variables
	$Z		New Line			Adds a new Line to the log*/
	void Set_Format(const char* newFormat);
	void Use_Format_Backup();

	// Define witch log levels should be written to log file directly and witch should be buffered
	//  0    =>   write all logs directly to log file
	//  1    =>   buffer: TRACE
	//  2    =>   buffer: TRACE + DEBUG
	//  3    =>   buffer: TRACE + DEBUG + INFO
	//  4    =>   buffer: TRACE + DEBUG + INFO + WARN
	void set_buffer_Level(int newLevel);
	void LogMsg(LogMsgSeverity level, const char* fileName, const char* funcName, int line, const char* message);
	const char* extractFileName(const char* filePath);


	class LogMessage : public std::ostringstream {

	public:
		LogMessage(LogMsgSeverity severity, const char* fileName, const char* funcName, int line);
		~LogMessage();

	private:
		LogMsgSeverity m_Severity;
		const char* m_FileName;
		const char* m_FuncName;
		int m_Line;

	};
}


// This enables the verious levels of the logging function (FATAL & ERROR are always on)
//  0    =>   FATAL + ERROR
//  1    =>   FATAL + ERROR + WARN
//  2    =>   FATAL + ERROR + WARN + INFO
//  3    =>   FATAL + ERROR + WARN + INFO + DEBUG
//  4    =>   FATAL + ERROR + WARN + INFO + DEBUG + TRACE
#define LOG_LEVEL_ENABLED 4
#define CORE_LOG_LEVEL_ENABLED 4
#define LOG_CLIENT_LEVEL_ENABLED 4
#define ASSERTS_ENABLED 1
#define MAX_MEASSGE_SIZE 1024


//  ===================================================================================  Client Logger  ===================================================================================

	#define GL_LOG_Fatal(message)					{ Logger::LogMessage(Logger::LogMsgSeverity::Fatal,__FILE__,__FUNCTION__,__LINE__).flush() << message; }
	#define GL_LOG_Error(message)					{ Logger::LogMessage(Logger::LogMsgSeverity::Error,__FILE__,__FUNCTION__,__LINE__).flush() << message; }

#if LOG_LEVEL_ENABLED >= 1
	#define GL_LOG_Warn(message, ...)				{ Logger::LogMessage(Logger::LogMsgSeverity::Warn,__FILE__,__FUNCTION__,__LINE__).flush() << message; }
#else
	#define GL_LOG_Warn(message, ...)				{;}
#endif

#if LOG_LEVEL_ENABLED >= 2
	#define GL_LOG_Info(message, ...)				{ Logger::LogMessage(Logger::LogMsgSeverity::Info,__FILE__,__FUNCTION__,__LINE__).flush() << message; }
#else
	#define GL_LOG_Info(message, ...)				{;}
#endif

#if LOG_LEVEL_ENABLED >= 3
	#define GL_LOG_Debug(message, ...)				{ Logger::LogMessage(Logger::LogMsgSeverity::Debug,__FILE__,__FUNCTION__,__LINE__).flush() << message; }
#else
	#define GL_LOG_Debug(message, ...)				{;}
#endif

#if LOG_LEVEL_ENABLED >= 4
	#define GL_LOG_Trace(message, ...)				{ Logger::LogMessage(Logger::LogMsgSeverity::Trace,__FILE__,__FUNCTION__,__LINE__).flush() << message; }
#else
	#define GL_LOG_Trace(message, ...)				{;}
#endif

	#define GL_LOG(severity, message)					GL_LOG_##severity(message)

//  ===================================================================================  Core Logger  ===================================================================================

	#define GL_CORE_LOG_Fatal(message)				{ Logger::LogMessage(Logger::LogMsgSeverity::Fatal,__FILE__,__FUNCTION__,__LINE__).flush() << message; }
	#define GL_CORE_LOG_Error(message)				{ Logger::LogMessage(Logger::LogMsgSeverity::Error,__FILE__,__FUNCTION__,__LINE__).flush() << message; }

#if CORE_LOG_LEVEL_ENABLED >= 1
	#define GL_CORE_LOG_Warn(message)				{ Logger::LogMessage(Logger::LogMsgSeverity::Warn,__FILE__,__FUNCTION__,__LINE__).flush() << message; }
#else
	#define GL_CORE_LOG_Warn(message)				{;}
#endif

#if CORE_LOG_LEVEL_ENABLED >= 2
	#define GL_CORE_LOG_Info(message)				{ Logger::LogMessage(Logger::LogMsgSeverity::Info,__FILE__,__FUNCTION__,__LINE__).flush() << message; }
#else
	#define GL_CORE_LOG_Info(message)				{;}
#endif

#if CORE_LOG_LEVEL_ENABLED >= 3
	#define GL_CORE_LOG_Debug(message)				{ Logger::LogMessage(Logger::LogMsgSeverity::Debug,__FILE__,__FUNCTION__,__LINE__).flush() << message; }
#else
	#define GL_CORE_LOG_Debug(message)				{;}
#endif

#if CORE_LOG_LEVEL_ENABLED >= 4
	#define GL_CORE_LOG_Trace(message)				{ Logger::LogMessage(Logger::LogMsgSeverity::Trace,__FILE__,__FUNCTION__,__LINE__).flush() << message; }
	#define GL_CORE_LOG_SEPERATOR					Logger::Set_Format("$C$Z");										\
													GL_CORE_LOG_Trace(Logger::SeperatorStringSmall)					\
													Logger::Use_Format_Backup();

	#define GL_CORE_LOG_SEPERATOR_BIG				Logger::Set_Format("$C$Z");										\
													GL_CORE_LOG_Trace(Logger::SeperatorStringBig)						\
													Logger::Use_Format_Backup();
#else
	#define GL_CORE_LOG_Trace(message, ...)			{;}
	#define GL_CORE_LOG_SEPERATOR					{;}
	#define GL_CORE_LOG_SEPERATOR_BIG				{;}
#endif


#define GL_CORE_LOG(severity, message)				GL_CORE_LOG_##severity(message)

#define THROW_ERR(message)							throw std::runtime_error(message)


// ---------------------------------------------------------------------------  Assertion & Validation  ---------------------------------------------------------------------------

#ifdef ENABLED_ASSERTS
	#define GL_CORE_ASSERT(expr, successMsg, failureMsg)						\
			if (expr) {															\
				GL_CORE_LOG(Trace, successMsg);									\
			} else {															\
				GL_CORE_LOG(Fatal, failureMsg);									\
				THROW_ERR(failureMsg);											\
			}
#else
	#define GL_CORE_ASSERT(expr, successMsg, failureMsg)						{expr;}
#endif // ASSERTS_ENABLED


#ifdef ENABLE_VALIDATION
	#define GL_CORE_VALIDATE(expr, successMsg, failureMsg, RetVal)				\
			if (expr) {															\
				GL_CORE_LOG(Trace, successMsg);									\
			} else {															\
				GL_CORE_LOG(Warn, failureMsg);									\
				RetVal;															\
			}
#else
	#define GL_CORE_VALIDATE(expr, successMsg, failureMsg, RetVal)				{expr;}
#endif // ENABLE_VALIDATION
