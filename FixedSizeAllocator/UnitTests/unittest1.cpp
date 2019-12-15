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
			assert(bitArray->AreAllClear());

			uint64_t * arrayBits = bitArray->GetBits();

			bitArray->SetBit(0);
			assert((*bitArray)[0]);
			assert(bitArray->IsBitSet(0));
			assert(!bitArray->IsBitClear(0));
			assert(*arrayBits == 1);

			bitArray->SetBit(2);
			assert((*bitArray)[2]);
			assert(bitArray->IsBitSet(2));
			assert(!bitArray->IsBitClear(2));
			assert(*arrayBits == 5);

			bitArray->ClearBit(0);
			assert(!(*bitArray)[0]);
			assert(!bitArray->IsBitSet(0));
			assert(bitArray->IsBitClear(0));
			assert(*arrayBits == 4);

			assert(!bitArray->AreAllClear());
			assert(!bitArray->AreAllSet());

			bitArray->SetAll();
			assert(bitArray->AreAllSet());
			assert(!bitArray->AreAllClear());
			assert(*arrayBits > 0);

			bitArray->ClearAll();
			assert(bitArray->AreAllClear());
			assert(!bitArray->AreAllSet());
			assert(*arrayBits == 0);

			size_t bitNumber = 0;
			bitArray->GetFirstClearBit(bitNumber);
			assert(bitNumber == 0);

			bitArray->SetBit(0);
			assert((*bitArray)[0]);
			bitArray->SetBit(1);
			assert((*bitArray)[1]);
			bitArray->SetBit(2);
			bitArray->GetFirstClearBit(bitNumber);
			assert(bitNumber == 3);

			bitArray->ClearBit(0);
			assert(!(*bitArray)[0]);
			bitArray->GetFirstSetBit(bitNumber);
			assert(bitNumber == 1);

			bitArray->ClearAll();
			bitArray->SetBit(33);
			bitArray->GetFirstSetBit(bitNumber);
			assert(bitNumber == 33);

			bitArray->ClearAll();
			bitArray->SetBit(64);
			bitArray->GetFirstSetBit(bitNumber);
			assert(bitNumber == 64);
		}

	};
}