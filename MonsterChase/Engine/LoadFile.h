#pragma once

#include <vector>
#include <string>
#include <stdint.h>

namespace Engine
{
	namespace File
	{
		std::vector<uint8_t> LoadFileToBuffer(const std::string & i_FileName);
	}
}