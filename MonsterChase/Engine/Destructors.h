#pragma once

template<typename T>
class DefaultDestructor
{
public:
	static void release(T * i_ptr) { delete i_ptr; }
};