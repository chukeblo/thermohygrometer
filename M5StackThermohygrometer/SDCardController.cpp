#include "SDCardController.hpp"

#include <stdexcept>

#include <M5Stack.h>
#include <SD.h>

std::string SDCardController::ReadFileFromSDCard(std::string file_name)
{
	File file = SD.open(file_name.c_str());
	if (!file)
	{
		throw std::invalid_argument("file not found: " + file_name);
	}
	uint32_t file_size = file.size();
	if (file_size > kMaxReadSize)
	{
		throw std::invalid_argument("too large file size: " + file_name);
	}
	char content[kMaxReadSize] = {};
	for (int i = 0; i < file_size; i++)
	{
		content[i] = file.read();
	}
	file.close();
	return std::string(content);
}
