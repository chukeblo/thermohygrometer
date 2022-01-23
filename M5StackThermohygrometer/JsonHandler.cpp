#include "JsonHandler.hpp"

#include <stdexcept>

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

std::map<std::string, std::string> JsonHandler::Parse(std::string raw)
{
    if (raw.empty())
    {
        throw std::invalid_argument("json string has no characters");
    }

    std::map<std::string, std::string> map;

    int count = 0;
    count = SkipBlankAndNewLineCharacters(raw, count);
    if (raw[count++] != kOpenBracket)
    {
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
        throw std::invalid_argument("does not end with close bracket ( '}' )");
    }
    count = SkipBlankAndNewLineCharacters(raw, count);
    if (count != raw.length() - 1)
    {
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

sKeyValuePairResult JsonHandler::ExtractKeyValuePair(std::string content, int index)
{
    if (content[index++] != kQuotationMark)
    {
        throw std::invalid_argument("key does not start with open quotation ( \" )");
    }
    char key[100];
    int key_index = 0;
    while (true)
    {
        if (content[index] == kEndOfString)
        {
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
        throw std::invalid_argument("key and value should be divided with colon ( : )");
    }
    index = SkipIfBlankCharacters(content, index);
    if (content[index++] != kQuotationMark)
    {
        throw std::invalid_argument("value does not start with open quotation ( \" )");
    }
    char value[100];
    int value_index = 0;
    while (true)
    {
        if (content[index] == kEndOfString)
        {
            throw std::invalid_argument("incorrectly comes to the end of json string");
        }
        if (content[index] == kQuotationMark)
        {
            value[value_index] = kEndOfString;
            break;
        }
        value[value_index++] = content[index++];
    }
    return sKeyValuePairResult{std::string(key), std::string(value), index + 1};
}