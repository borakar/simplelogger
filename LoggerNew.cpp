#include "ModuleLog.h"
#include "Logger.h"

#include "unistd.h"


/*#define S1(x) #x
#define S2(x) S1(x)
#define LOCATION __FILE__ " : " S2(__LINE__)

#define STRINGFY(x) #x
#define TOSTRING(x) STRINGFY(x)
#define LOC __FILE__ ":" TOSTRING(__LINE__)*/

int main()
{
	ModuleLog *m_Log;
	ModuleLoggerSingleton::getInstance().InitLogger();

	m_Log = ModuleLoggerSingleton::getInstance().GetLogger("deneme");
	m_Log->setSeverity(LOG_TRACE);

	std::string h = "hello";
	int i = 0;

	while(1)
	{
		i++;
		//m_Log->log(LOC, LOG_TRACE, "%d\n", i);
		Log_Debug(m_Log, "%d\n", i);
		sleep(1);
	}

	return 0;
}
