#include "MemoryManagerGlobals.h"

#include "../Engine/Engine.h"

namespace MemoryManagerGlobals
{
	void InitGlobals()
	{
		pHeapManager = Engine::initializeHeapManager();

		FSAMapData = reinterpret_cast<FSAMap *>(pHeapManager->_alloc(sizeof(FSAMap) * numFSAs));

		FSASizes = reinterpret_cast<FSAInitData *>(pHeapManager->_alloc(sizeof(FSAInitData) * numFSAs));

		FSASizes[0] = { 16, 100 };
		FSASizes[1] = { 32, 200 };
		FSASizes[2] = { 96, 400 };
	};
}