#include "SDCardController.hpp"

#include <stdexcept>

#include <M5Stack.h>
#include <SD.h>

std::string SDCardController::ReadFileFromSDCard(std::string fileName)
{
	File file = SD.open(fileName.c_str());
	if (!file)
	{
		throw std::invalid_argument("file not found: " + fileName);
	}
	uint32_t file_size = file.size();
	if (file_size > kMaxReadSize)
	{
		throw std::invalid_argument("too large file size: " + fileName);
	}
	char content[kMaxReadSize] = {};
	for (int i = 0; i < file_size; i++)
	{
		content[i] = file.read();
	}
	file.close();
	return std::string(content);
}
