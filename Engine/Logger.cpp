#include "Logger.h"

#ifdef LOGGER
vector <std::string> Logger::logList;
vector <Severity> Logger::severityList;

Logger::Logger(void){}
Logger::~Logger(void){}

void Logger::StringReplace(string& str, const string& from, const string& to)
{
	size_t pos = 0;
	do 
	{
		pos = str.find(from, pos);
		if( pos != string::npos )
		{
			str.replace( pos, from.length(), to);
			pos += to.length();
		}
	} while (pos != string::npos);
}

string Logger::Sanitize(string str)
{
	StringReplace( str, ">" , "&gt" );
	StringReplace(str, "<", "&lt");

	return str;
}

void Logger::Log( Severity severity, const char* message, const char * logFile, int logLine)
{
	std::stringstream ss;
	ss << logFile << "(" << logLine << ") - " << Sanitize(message); 
	std::string logEntry;
	logEntry = ss.str();
	
	logList.push_back(logEntry);
	severityList.push_back(severity);
}

void Logger::WriteFile()
{
	std::ofstream myFile("Log.html");
	
	myFile << "<!DOCTYPE html>" << std::endl << "<html>" 
		<< std::endl << "<head>" << std::endl << "<title>Log File</title>" << std::endl << "</head>"
		<< std::endl << "<body bgcolor = '#FFFFFF' >" << std::endl << "<h2>Log File</h2>";
	for(unsigned int i = 0; i < logList.size(); i ++)
	{
		switch (severityList[i])
		{
			case Info:
				myFile <<  "<font color=\"#000000\">";
				break;

			case Warning:
				myFile <<  "<font color=\"#FFFF00\">";
				break;

			case Error:
				myFile <<  "<font color=\"#FF0000\">"; 
				break;

			case Severe:
				myFile <<  "<font color=\"#FF0000\">"; 
				break;
		}
		myFile << logList[i].c_str() << "</font><br>";
	}
	myFile << "</body>" << std::endl << "</html>";	
	myFile.close();
}

void Logger::Shutdown()
{
	WriteFile();
}

#endif