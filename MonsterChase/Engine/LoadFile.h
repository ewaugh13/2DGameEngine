#pragma once

#include <vector>
#include <string>
#include <stdint.h>

namespace MyEngine
{
	namespace File
	{
		std::vector<uint8_t> LoadFileToBuffer(const std::string & i_FileName);
	}
}