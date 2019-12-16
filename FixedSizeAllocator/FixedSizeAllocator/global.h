#pragma once

#include "HeapManager.h"
#include "FixedSizeAllocator.h"

// number of fixed size allocators
const unsigned int numFSAs = 3;

// extern global HeapManager that is initalized by MemorySystem
extern HeapManager * pHeapManager;

// extern global for fixed sized allocator map that is initalized in Allocators
// and MemorySystem creates the maps
extern FSAMap FSAMapData[numFSAs];

// global for fixed sized allocator sizes initalized in Allocators
// note needs to be put in order of smallest block size to largest
extern FSAInitData FSASizes[numFSAs];