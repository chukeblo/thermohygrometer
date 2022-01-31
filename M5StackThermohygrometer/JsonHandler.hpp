#pragma once

#include <map>
#include <string>

class JsonHandler
{
private:
	typedef struct
	{
		std::string key;
		std::string value;
		int index;
	} sKeyValuePairResult;

public:
	static std::string Serialize(std::map<std::string, std::string> jsonMap);
	static std::map<std::string, std::string> Parse(std::string raw);

private:
	static int SkipIfBlankCharacters(std::string content, int index);
	static int SkipBlankAndNewLineCharacters(std::string content, int index);
	static JsonHandler::sKeyValuePairResult ExtractKeyValuePair(std::string content, int index);
};