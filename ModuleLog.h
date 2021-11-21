#ifndef MODULE_LOG_H
#define MODULE_LOG_H

#include "Logger.h"
#include <string>
#include <map>

#define STRINGFY1(x) #x
#define TOSTRING1(x) STRINGFY1(x)
#define LOC1 __FILE__ ":" TOSTRING1(__LINE__)

enum SeverityLevel
{
	LOG_NOLOG,
	LOG_FATAL,
	LOG_ERROR,
	LOG_WARNING,
	LOG_INFO,
	LOG_DEBUG,
	LOG_TRACE
};

#define Log_Fatal(module_name, ...) module_name->log(LOC1, LOG_FATAL, __VA_ARGS__)
#define Log_Error(module_name, ...) module_name->log(LOC1, LOG_ERROR, __VA_ARGS__)
#define Log_Warning(module_name, ...) module_name->log(LOC1, LOG_WARNING, __VA_ARGS__)
#define Log_Info(module_name, ...) module_name->log(LOC1, LOG_INFO, __VA_ARGS__)
#define Log_Debug(module_name, ...) module_name->log(LOC1, LOG_DEBUG, __VA_ARGS__)
#define Log_Trace(module_name, ...) module_name->log(LOC1, LOG_TRACE, __VA_ARGS__)



class ModuleLog
{
	private:
		std::string m_moduleName;

		Logger *m_mainLogger;

		SeverityLevel m_severityLevel;

		std::string getSeverityString(SeverityLevel a_severity);

	public:
		ModuleLog(std::string module_name, SeverityLevel severity, Logger* mainLogger);

		SeverityLevel getSeverity() const;

		void setSeverity(SeverityLevel severity);
		void log(std::string logParameters, SeverityLevel a_severity, const char* msg, ...);
};

class ModuleLoggerSingleton
{
	public:
		~ModuleLoggerSingleton() {}
		static ModuleLoggerSingleton& getInstance()
		{
			static ModuleLoggerSingleton instance;
			return instance;
		}

		ModuleLog* GetLogger(std::string module_name);
		ModuleLog* GetLoggerIfExist(std::string module_name);

		void InitLogger(bool fileSink = false, std::string fileName = "app.log", bool syslogSink = false, bool syslogSinkServer = false, std::string sysLogServerAddr = "");
		void SetDefaultLogLevel(SeverityLevel new_defaultSeverityLevel);
		void SetAllLogLevel(SeverityLevel new_SeverityLevel);

	private:
		ModuleLoggerSingleton() : m_defaultSeverityLevel(LOG_INFO) {}

	private:
		Logger m_mainLogger;
		SeverityLevel m_defaultSeverityLevel;
		std::map < std::string, ModuleLog* > m_moduleLoggers;
};

#endif
