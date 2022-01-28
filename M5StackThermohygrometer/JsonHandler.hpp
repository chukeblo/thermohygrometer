#pragma once

#include <map>
#include <string>

typedef struct
{
	std::string key;
	std::string value;
	int index;
} sKeyValuePairResult;

class JsonHandler
{
public:
	static std::map<std::string, std::string> Parse(std::string raw);

private:
	static int SkipIfBlankCharacters(std::string content, int index);
	static int SkipBlankAndNewLineCharacters(std::string content, int index);
	static sKeyValuePairResult ExtractKeyValuePair(std::string content, int index);
};