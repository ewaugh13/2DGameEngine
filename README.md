# u0947296

Unique things I did:
- I created a unit test for my BitArray located in unittest1.cpp (part of the unit test project)
- I created 3 inline helper functions to get relevant information for a bit index like which byte to use
  and the bit evaulator to use for setting or clearing and checking if set or cleared in BitArray.h
- Created a method for the fixed size allocator to print out all of its blocks with each address and 
  whether they were allocated or not located in FixedSizeAllocator.cpp
- I like the struct I created to map a block size to a fixed size allocator for easy
  use when an allocation request comes in I can look at the maps and see if the size 
  is in that range located in FixedSizeAllocator.h and used in Allocators.cpp (methods _alloc() and _free())
- I was also pretty happy with my bit arithmetic in BitArray-inl.h and BitArray.cpp for setting and clearing
  aswell as the other evaulators
