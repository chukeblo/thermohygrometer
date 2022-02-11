#include "JsonHandler.hpp"

#include <stdexcept>

#include <M5Stack.h>
#include "EventHandler.hpp"
#include "LogConstants.hpp"
#include "LogData.hpp"

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
	LogData* log_data = new LogData(LogLevel::kTrace, kJsonHandler, kSerialize, "in");
	EventHandler* event_handler = EventHandler::GetInstance();
	event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
	std::string json = { kOpenBracket };
	std::map<std::string, std::string>::iterator it = jsonMap.begin();
	bool beginning = false;
	do
	{
		if (beginning) {
			json.append({ kComma });
		}
		beginning = true;
		json.append(it->first);
		json.append({ kColon });
		json.append(it->second);
	} while (++it != jsonMap.end());
	json.append({ kCloseBracket });
	log_data = new LogData(LogLevel::kDebug, kJsonHandler, kSerialize, json);
	event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
	return json;
}

std::map<std::string, std::string> JsonHandler::Parse(std::string raw)
{
	LogData* log_data = new LogData(LogLevel::kTrace, kJsonHandler, kParse, std::string("in: raw=") + raw);
	EventHandler* event_handler = EventHandler::GetInstance();
	event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
	if (raw.empty())
	{
		
		log_data = new LogData(LogLevel::kError, kJsonHandler, kParse, "given json string is empty");
		event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
		throw std::invalid_argument("json string has no characters");
	}

	std::map<std::string, std::string> map;

	int count = 0;
	count = SkipBlankAndNewLineCharacters(raw, count);
	if (raw[count++] != kOpenBracket)
	{
		log_data = new LogData(LogLevel::kError, kJsonHandler, kParse,
			std::string("Json element does not start with open bracket ( { ): count=") +
			std::string(String(count).c_str())
		);
		event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
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
		log_data = new LogData(LogLevel::kError, kJsonHandler, kParse,
			std::string("Json element does not end with close bracket ( } ): count=") +
			std::string(String(count).c_str())
		);
		event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
		throw std::invalid_argument("does not end with close bracket ( '}' )");
	}
	count = SkipBlankAndNewLineCharacters(raw, count);
	if (count != raw.length() - 1)
	{
		log_data = new LogData(LogLevel::kError, kJsonHandler, kParse,
			std::string("Json body must end with close bracket ( } ): count=") +
			std::string(String(count).c_str())
		);
		event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
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
	LogData* log_data = new LogData(LogLevel::kTrace, kJsonHandler, kExtractKeyValuePair, std::string("in: raw=") + content);
	EventHandler* event_handler = EventHandler::GetInstance();
	event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
	if (content[index++] != kQuotationMark)
	{
		log_data = new LogData(LogLevel::kError, kJsonHandler, kExtractKeyValuePair,
			std::string("Key does not start with quotation ( \" ): count=") +
			std::string(String(index).c_str())
		);
		event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
		throw std::invalid_argument("key does not start with open quotation ( \" )");
	}
	char key[100];
	int key_index = 0;
	while (true)
	{
		if (content[index] == kEndOfString)
		{
			log_data = new LogData(LogLevel::kError, kJsonHandler, kExtractKeyValuePair,
				std::string("Json body incorrectly comes to the end: count=") +
				std::string(String(index).c_str())
			);
			event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
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
		log_data = new LogData(LogLevel::kError, kJsonHandler, kExtractKeyValuePair,
			std::string("Key and value must be divided with colon ( : ): count") +
			std::string(String(index).c_str())
		);
		event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
		throw std::invalid_argument("key and value should be divided with colon ( : )");
	}
	index = SkipIfBlankCharacters(content, index);
	if (content[index++] != kQuotationMark)
	{
		log_data = new LogData(LogLevel::kError, kJsonHandler, kExtractKeyValuePair,
			std::string("Value does not start with quotation ( \" ): count=") +
			std::string(String(index).c_str())
		);
		event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
		throw std::invalid_argument("value does not start with open quotation ( \" )");
	}
	char value[100];
	int value_index = 0;
	while (true)
	{
		if (content[index] == kEndOfString)
		{
			log_data = new LogData(LogLevel::kError, kJsonHandler, kExtractKeyValuePair,
				std::string("Json body incorrectly comes to the end: count=") +
				std::string(String(index).c_str())
			);
			event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
			throw std::invalid_argument("incorrectly comes to the end of json string");
		}
		if (content[index] == kQuotationMark)
		{
			value[value_index] = kEndOfString;
			break;
		}
		value[value_index++] = content[index++];
	}
	log_data = new LogData(LogLevel::kTrace, kJsonHandler, kExtractKeyValuePair,
		std::string("out: key=") + std::string(key) + std::string(",value=") +
		std::string(value) + std::string(",count=") + std::string(String(index + 1).c_str())
	);
	event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
	return sKeyValuePairResult{ std::string(key), std::string(value), index + 1 };
}