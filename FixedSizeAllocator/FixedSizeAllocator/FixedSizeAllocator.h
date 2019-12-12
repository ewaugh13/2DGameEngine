#pragma once
class FixedSizeAllocator
{
public:
	FixedSizeAllocator();
	~FixedSizeAllocator();

	void * alloc();
	void free(void * i_ptr);
};

