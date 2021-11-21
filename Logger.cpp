#include "Logger.h"
#include <iostream>
#include <unistd.h>

void Logger::LoggerInit(bool fileSink, std::string fileName, bool sysLogSink,
			    bool syslogSinkServer, std::string sysLogServerAddr)
{
	start();
}

Logger::Logger()
{
}

Logger::~Logger()
{
}

/*void Logger::start()
{
	/// This function starts the logging thread
	m_stopThread = false;

	// Start logger thread
}*/

void* Logger::run()
{
	while(!m_stopThread)
	{
		std::string logMessage;

		while (m_circularBuffer.get(logMessage))
		{
			std::cout << logMessage;
		}

		usleep(10000);
	}

	return NULL;
}
