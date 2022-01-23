#include "JsonHandler.hpp"

#include <M5Stack.h>
#include <stdexcept>

std::map<std::string, std::string> JsonHandler::Parse(std::string raw)
{
    if (raw.empty())
    {
        throw std::invalid_argument("json string has no characters");
    }

    std::map<std::string, std::string> map;

    int count = 0;
    count = SkipBlankAndNewLineCharacters(raw, count);
    if (raw[count++] != '{')
    {
        throw std::invalid_argument("does not start with open bracket ( '{' )");
    }
    while (true) {
        count = SkipBlankAndNewLineCharacters(raw, count);
        sKeyValuePairResult result = ExtractKeyValuePair(raw, count);
        map.insert(std::make_pair(result.key, result.value));
        count = result.index;
        if (raw[count++] != ',') {
            break;
        }
    }
    count = SkipBlankAndNewLineCharacters(raw, count);
    if (raw[count] != '}')
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
        if (content[index] != ' ' && content[index] != '\t')
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
        if (content[index] != ' ' && content[index] != '\t')
        {
            if (content[index] != '\r' && content[index] != '\n')
            {
                return index;
            }
        }
        index++;
    }
}

sKeyValuePairResult JsonHandler::ExtractKeyValuePair(std::string content, int index)
{
    if (content[index++] != '"')
    {
        throw std::invalid_argument("key does not start with open quotation ( \" )");
    }
    char key[100];
    int key_index = 0;
    while (true)
    {
        if (content[index] == '\0')
        {
            throw std::invalid_argument("incorrectly comes to the end of json string");
        }
        if (content[index] == '\"')
        {
            key[key_index] = '\0';
            break;
        }
        key[key_index++] = content[index++];
    }
    index = SkipIfBlankCharacters(content, ++index);
    if (content[index++] != ':')
    {
        throw std::invalid_argument("key and value should be divided with colon ( : )");
    }
    index = SkipIfBlankCharacters(content, index);
    if (content[index++] != '\"')
    {
        throw std::invalid_argument("does not end with close quotation ( \" )");
    }
    char value[100];
    int value_index = 0;
    while (true)
    {
        if (content[index] == '\0')
        {
            throw std::invalid_argument("incorrectly comes to the end of json string");
        }
        if (content[index] == '\"')
        {
            value[value_index] = '\0';
            break;
        }
        value[value_index++] = content[index++];
    }
    std::string key_string = key;
    std::string value_string = value;
    sKeyValuePairResult result{key_string, value_string, index + 1};
    return result;
}