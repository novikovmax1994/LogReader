#pragma once
#include <string>
#include <map>

typedef std::multimap<std::string, std::string> ResultMap;
typedef std::string::reverse_iterator RevIter;
typedef std::pair<std::string, std::string> StrPair;

class Reader {
public:
	Reader();
	ResultMap ReadLogFile();
	void setPath(std::string path);
	~Reader();

private:
	std::string file_path_;
	StrPair getSubStr(std::string full_string);
};