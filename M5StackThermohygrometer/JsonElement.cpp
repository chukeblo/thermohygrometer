#include "JsonElement.hpp"

JsonElement::JsonElement(JsonElementType type) : type(type)
{
}

JsonElement::~JsonElement()
{
}

JsonNumberElement::JsonNumberElement(int data) : JsonElement(JsonElementType::kNumber), data(data)
{
}

JsonNumberElement::~JsonNumberElement()
{
}

JsonStringElement::JsonStringElement(std::string data) : JsonElement(JsonElementType::kString), data(data)
{
}

JsonStringElement::~JsonStringElement()
{
}