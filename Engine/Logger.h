#ifdef LOGGING

#ifndef LOGGER
#define LOGGER
#include <vector>
#include <fstream>
#include <sstream>
#include "ExportHeader.h"
using std::vector;
using std::string;

enum Severity { Info, Warning, Error, Severe };

#define LOG( severity, message) Logger::Log( severity, message, __FILE__, __LINE__ );
#define END_LOG Logger::Shutdown();

#define ASSERT(expression, ...) if (!(expression)) {Logger::Log(Severe, #expression ## " " ## __VA_ARGS__, __FILE__, __LINE__); Logger::Shutdown(); exit(1);} 

#pragma warning ( disable : 4100)

template class ENGINE_SHARED vector <string>;
template class ENGINE_SHARED vector <Severity>;

class ENGINE_SHARED Logger
{
public:
	Logger(void);
	~Logger(void);
	static void StringReplace(string& str, const string& from, const string& to);
	static string Sanitize(string str);
	static void Log( Severity severity, const char* message, const char * logFile, int logLine);
	static void Shutdown();
private:
	static vector <string> logList;
	static vector <Severity> severityList;
	static void WriteFile();
};

#pragma warning ( default : 4100)

#endif
#else

#define LOG( severity, message)
#define END_LOG

#define ASSERT(expression, ...)

#endif