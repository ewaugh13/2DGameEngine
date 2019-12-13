// using .cpp files since I don't want to turn 
// my application into a library to resolve the linker problem
#include "HeapManager.cpp"
#include "BitArray.cpp"

#include "CppUnitTest.h"

#include <assert.h>
#include <Windows.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// initalize heap manager
			const size_t sizeHeap = 1024 * 1024;
			const unsigned int numDescriptors = 2048;
			void * pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);

			HeapManager * pHeapManager = HeapManager::create(pHeapMemory, sizeHeap, numDescriptors);
			assert(pHeapManager);

			size_t numBits = 100;
			BitArray * bitArray = new BitArray(numBits, pHeapManager);
			assert(bitArray);

			bitArray->SetBit(0);
			assert((*bitArray)[0]);
		}

	};
}