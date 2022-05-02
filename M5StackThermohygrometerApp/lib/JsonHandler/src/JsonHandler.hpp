#pragma once

#include <map>
#include <string>

#include <JsonElement.hpp>

class JsonHandler
{
private:
	typedef struct
	{
		std::string key;
		JsonElement* value;
		int index;
	} sKeyValuePairResult;

public:
	static std::string Serialize(std::map<std::string, std::string> jsonMap);
	static std::map<std::string, JsonElement*> Parse(std::string raw);

private:
	static int SkipIfBlankCharacters(std::string content, int index);
	static int SkipBlankAndNewLineCharacters(std::string content, int index);
	static JsonHandler::sKeyValuePairResult ExtractKeyValuePair(std::string content, int index);
};