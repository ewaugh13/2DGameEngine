#pragma once

#include "GLib.h"
namespace GLibHelper
{
	void * LoadFile(const char * i_pFilename, size_t & o_sizeFile);

	GLib::Sprites::Sprite * CreateSprite(const char * i_pFilename);

	const size_t SizeReadTable = 256;
	static uint8_t KeyStates[SizeReadTable];

	void KeyCallback(unsigned int i_VKeyID, bool bWentDown);
}