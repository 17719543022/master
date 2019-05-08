#ifndef _INCL_INI_READER_H_
#define _INCL_INI_READER_H_
#include <string>
#include <map>
using namespace std;

class iniReader
{
	public:
		iniReader()
		{
		}
		~iniReader()
		{
		}
		bool readConfig(const string & filename);
		string readString(const char* section, const char* item, const char* default_value);
		int readInt(const char* section, const char* item, const int& default_value);
		float readFloat(const char* section, const char* item, const float& default_value);

	private:
		bool isSpace(char c);
		bool isCommentChar(char c);
		void trim(string & str);
		bool analyseLine(const string & line, string& section, string & key, string & value);

	private:
		map<string, map<string, string> >settings;
};

#endif