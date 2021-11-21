#ifndef LOGGER_H
#define LOGGER_H

#include "SYNCHBuffer.h"
#include "CThread.h"
#include <string>

static const int BUFFER_SIZE = 1024;

/// LOG Parameters File name + Function name + Line number
const std::string BLANK_SPACE = "  ";
const std::string COLON = ":";

class Logger : public CThread
{
  public:
    Logger();
    virtual ~Logger();
    virtual void LoggerInit(bool fileSink, std::string fileName, bool sysLogSink,
			    bool syslogSinkServer, std::string sysLogServerAddr);
    void log(std::string logmessage) { m_circularBuffer.add(logmessage); }

  private:
    //void start();
    void *run();

    void initLogger();
    const std::string& getFileName() const;

    /// Thread working state elements
    volatile bool m_stopThread;
    
    /// Circular buffer instance. Buffer gets BoostLog instances as elements
    SYNCHBuffer<std::string> m_circularBuffer;
};

#endif
