#include "ModuleLog.h"
#include <stdarg.h>
#include <stdio.h>

std::string ModuleLog::getSeverityString(SeverityLevel a_severity)
{
  switch (a_severity)
  {
    case LOG_FATAL:
      return "FATAL";
      break;

    case LOG_ERROR:
      return "ERROR";
      break;

    case LOG_WARNING:
      return "WARNING";
      break;

    case LOG_INFO:
      return "INFO";
      break;

    case LOG_DEBUG:
      return "DEBUG";
      break;

    case LOG_TRACE:
      return "TRACE";
      break;

    default:
      return "";
  }
  return "";
}

ModuleLog::ModuleLog(std::string module_name, SeverityLevel severity, Logger* mainLogger)
{
	m_moduleName = module_name;
	m_severityLevel = severity;
	m_mainLogger = mainLogger;
}

SeverityLevel ModuleLog::getSeverity() const
{
	return m_severityLevel;
}

void ModuleLog::setSeverity(SeverityLevel severity)
{
	m_severityLevel = severity;
}

void ModuleLog::log(std::string logParameters, SeverityLevel a_severity, const char* msg, ...)
{
	if(a_severity <= m_severityLevel)
	{
		char buffer[BUFFER_SIZE];

		va_list args;
    
		va_start(args, msg);
		vsnprintf(buffer, BUFFER_SIZE, msg, args);
		va_end(args);

		std::string logArgs = std::string(buffer);
		logArgs = "- " + m_moduleName + " " + logParameters + " " + "[" + getSeverityString(a_severity) + "] - " + logArgs;

		m_mainLogger->log(logArgs);
	}
}

ModuleLog* ModuleLoggerSingleton::GetLogger(std::string module_name)
{
    ModuleLog * aLogger;

	if(m_moduleLoggers.find(module_name) == m_moduleLoggers.end())
    {
        aLogger = new ModuleLog(module_name, m_defaultSeverityLevel, &m_mainLogger);
        m_moduleLoggers[module_name] = aLogger;
    }
    else
    {
		aLogger = m_moduleLoggers[module_name];
    }

    return aLogger;
}

ModuleLog* ModuleLoggerSingleton::GetLoggerIfExist(std::string module_name)
{
    ModuleLog * aLogger = NULL;

    if(m_moduleLoggers.find(module_name) != m_moduleLoggers.end())
    {
        aLogger = m_moduleLoggers[module_name];
    }

    return aLogger;
}

void ModuleLoggerSingleton::SetDefaultLogLevel(SeverityLevel new_defaultSeverityLevel)
{
    m_defaultSeverityLevel = new_defaultSeverityLevel;
}

void ModuleLoggerSingleton::SetAllLogLevel(SeverityLevel new_defaultSeverityLevel)
{
    std::map<std::string, ModuleLog*>::iterator iter;

    for(iter = m_moduleLoggers.begin(); iter != m_moduleLoggers.end(); iter++)
    {
		iter->second->setSeverity(new_defaultSeverityLevel);
    }
}

void ModuleLoggerSingleton::InitLogger(bool fileSink, std::string fileName, bool syslogSink, bool syslogSinkServer, std::string sysLogServerAddr)
{
	m_mainLogger.LoggerInit(fileSink, fileName, syslogSink, syslogSinkServer, sysLogServerAddr);
}
