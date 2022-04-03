#include "JsonHandler.hpp"

#include <cstdio>
#include <stdexcept>

#include <M5Stack.h>
#include <ConsoleLogger.hpp>
#include <LogConstants.hpp>

static const char kOpenBracket = '{';
static const char kCloseBracket = '}';
static const char kQuotationMark = '\"';
static const char kComma = ',';
static const char kColon = ':';
static const char kEndOfString = '\0';
static const char kSpace = ' ';
static const char kTab = '\t';
static const char kCarriageReturn = '\r';
static const char kLineFeed = '\n';

std::string JsonHandler::Serialize(std::map<std::string, std::string> jsonMap)
{
	ConsoleLogger::Log(new LogData(LogLevel::kTrace, kJsonHandler, kSerialize, "in"));
	std::string json = { kOpenBracket };
	bool is_beginning = false;
	for (auto it = jsonMap.begin(); it != jsonMap.end(); it++)
	{
		if (is_beginning) {
			json.append({ kComma });
		}
		is_beginning = true;
		json.append({ kQuotationMark });
		json.append(it->first);
		json.append({ kQuotationMark });
		json.append({ kColon, kQuotationMark });
		json.append(it->second);
		json.append({ kQuotationMark });
	}
	json.append({ kCloseBracket });
	ConsoleLogger::Log(new LogData(LogLevel::kDebug, kJsonHandler, kSerialize, json));
	return json;
}

std::map<std::string, JsonElement*> JsonHandler::Parse(std::string raw)
{
	ConsoleLogger::Log(new LogData(LogLevel::kTrace, kJsonHandler, kParse, "in: raw=" + raw));
	if (raw.empty())
	{
		ConsoleLogger::Log(new LogData(LogLevel::kError, kJsonHandler, kParse, "given json string is empty"));
		throw std::invalid_argument("json string has no characters");
	}

	std::map<std::string, JsonElement*> map;

	int count = 0;
	count = SkipBlankAndNewLineCharacters(raw, count);
	if (raw[count++] != kOpenBracket)
	{
		ConsoleLogger::Log(new LogData(LogLevel::kError, kJsonHandler, kParse,
			"Json element does not start with open bracket ( { ): count=" + std::string(String(count).c_str())
		));
		throw std::invalid_argument("does not start with open bracket ( '{' )");
	}
	while (true)
	{
		count = SkipBlankAndNewLineCharacters(raw, count);
		sKeyValuePairResult result = ExtractKeyValuePair(raw, count);
		map.insert(std::make_pair(result.key, result.value));
		count = result.index;
		if (raw[count++] != kComma)
		{
			break;
		}
	}
	count = SkipBlankAndNewLineCharacters(raw, count);
	if (raw[count] != kCloseBracket)
	{
		ConsoleLogger::Log(new LogData(LogLevel::kError, kJsonHandler, kParse,
			"Json element does not end with close bracket ( } ): count=" +
			std::string(String(count).c_str())
		));
		throw std::invalid_argument("does not end with close bracket ( '}' )");
	}
	count = SkipBlankAndNewLineCharacters(raw, count);
	if (count != raw.length() - 1)
	{
		ConsoleLogger::Log(new LogData(LogLevel::kError, kJsonHandler, kParse,
			"Json body must end with close bracket ( } ): count=" +
			std::string(String(count).c_str())
		));
		throw std::invalid_argument("should end with close bracket ( '}' )");
	}

	return map;
}

int JsonHandler::SkipIfBlankCharacters(std::string content, int index)
{
	while (true)
	{
		if (content[index] != kSpace && content[index] != kTab)
		{
			return index;
		}
		index++;
	}
}

int JsonHandler::SkipBlankAndNewLineCharacters(std::string content, int index)
{
	while (true)
	{
		if (content[index] != kSpace && content[index] != kTab)
		{
			if (content[index] != kCarriageReturn && content[index] != kLineFeed)
			{
				return index;
			}
		}
		index++;
	}
}

JsonHandler::sKeyValuePairResult JsonHandler::ExtractKeyValuePair(std::string content, int index)
{
	ConsoleLogger::Log(new LogData(LogLevel::kTrace, kJsonHandler, kExtractKeyValuePair, "in: raw=" + content));
	if (content[index++] != kQuotationMark)
	{
		ConsoleLogger::Log(new LogData(LogLevel::kError, kJsonHandler, kExtractKeyValuePair,
			"Key does not start with quotation ( \" ): count=" + std::string(String(index).c_str())
		));
		throw std::invalid_argument("key does not start with open quotation ( \" )");
	}
	char key[100];
	int key_index = 0;
	while (true)
	{
		if (content[index] == kEndOfString)
		{
			ConsoleLogger::Log(new LogData(LogLevel::kError, kJsonHandler, kExtractKeyValuePair,
				"Json body incorrectly comes to the end: count=" + std::string(String(index).c_str())
			));
			throw std::invalid_argument("incorrectly comes to the end of json string");
		}
		if (content[index] == kQuotationMark)
		{
			key[key_index] = kEndOfString;
			break;
		}
		key[key_index++] = content[index++];
	}
	index = SkipIfBlankCharacters(content, ++index);
	if (content[index++] != kColon)
	{
		ConsoleLogger::Log(new LogData(LogLevel::kError, kJsonHandler, kExtractKeyValuePair,
			"Key and value must be divided with colon ( : ): count" + std::string(String(index).c_str())
		));
		throw std::invalid_argument("key and value should be divided with colon ( : )");
	}
	index = SkipIfBlankCharacters(content, index);
	if (content[index] != kQuotationMark)
	{
		char value[100];
		int value_index = 0;
		while (true)
		{
			if (content[index] == kEndOfString)
			{
				ConsoleLogger::Log(new LogData(LogLevel::kError, kJsonHandler, kExtractKeyValuePair,
					"Json body incorrectly comes to the end: count=" + std::string(String(index).c_str())
				));
				throw std::invalid_argument("incorrectly comes to the end of json string");
			}
			if (content[index] == kComma || content[index] == kSpace)
			{
				value[value_index] = kEndOfString;
				break;
			}
			if (content[index] < 0x30 || 0x39 < content[index])
			{
				ConsoleLogger::Log(new LogData(LogLevel::kError, kJsonHandler, kExtractKeyValuePair,
					"invalid number has been found: count=" + std::string(String(index).c_str())
				));
				throw std::invalid_argument("invalid number has been found");
			}
			value[value_index++] = content[index++];
		}
		int int_value = atoi(value);
		return sKeyValuePairResult{ std::string(key), new JsonNumberElement(int_value), index };
	}
	else
	{
		char value[100];
		int value_index = 0;
		index++;
		while (true)
		{
			if (content[index] == kEndOfString)
			{
				ConsoleLogger::Log(new LogData(LogLevel::kError, kJsonHandler, kExtractKeyValuePair,
					"Json body incorrectly comes to the end: count=" + std::string(String(index).c_str())
				));
				throw std::invalid_argument("incorrectly comes to the end of json string");
			}
			if (content[index] == kQuotationMark)
			{
				value[value_index] = kEndOfString;
				break;
			}
			value[value_index++] = content[index++];
		}
		ConsoleLogger::Log(new LogData(LogLevel::kTrace, kJsonHandler, kExtractKeyValuePair,
			"out: key=" + std::string(key) + ",value=" + value + ",count=" + std::string(String(index + 1).c_str())
		));
		return sKeyValuePairResult{ std::string(key), new JsonStringElement(value), index + 1 };
	}	
}