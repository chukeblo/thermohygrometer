#pragma once

#include <string>

#include "JsonElementType.hpp"

class JsonElement
{
public:
    JsonElement(JsonElementType type);
    virtual ~JsonElement();

public:
    JsonElementType type;
};

class JsonNumberElement : public JsonElement
{
public:
    JsonNumberElement(int data);
    ~JsonNumberElement();

public:
    int data;
}

class JsonStringElement : public JsonElement
{
public:
    JsonStringElement(std::string data);
    ~JsonStringElement();

public:
    std::string data;
}