#pragma once

#include "HeapManager.h"
#include "Engine.h"

#define ALIGN_8 8
#define ALIGN_16 16
#define ALIGN_32 32

#pragma region Standard Allocators
void * operator new(size_t i_size);
void operator delete(void * i_ptr);

void * operator new[](size_t i_size);
void operator delete[](void * i_ptr);
#pragma endregion

// example to use tracked (new TRACK_NEW Actor("Eric", Point2D::Zero)
#pragma region Tracked Allocators
void * operator new(size_t i_size, const char * i_pFile, unsigned int i_Line);
void  operator delete(void * i_ptr, const char * i_pFile, unsigned int i_Line);

void * operator new[](size_t i_size, const char * i_pFile, unsigned int i_Line);
void operator delete[](void * i_ptr, const char * i_pFile, unsigned int i_Line);
#pragma endregion

static HeapManager * pHeapManager = Engine::initializeHeapManager();

