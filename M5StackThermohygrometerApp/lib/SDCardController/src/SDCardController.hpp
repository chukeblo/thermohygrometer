#pragma once

#include <string>

class SDCardController
{
private:
	static const int kMaxReadSize = 2048;

public:
	virtual std::string ReadFileFromSDCard(std::string file_name);
};