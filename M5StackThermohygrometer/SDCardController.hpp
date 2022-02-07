#pragma once

#include <string>

class SDCardController
{
private:
	static const int kMaxReadSize = 2048;

public:
	static std::string ReadFileFromSDCard(std::string fileName);
};