Cache by th1614 - Tom Hartley
===========

This cache simulator contains 6 C++ files: broken down as follows
- 1 main file
- 4 classes
- 1 processing file


The 4 classes are (from high level to low level) as follows:

The Memory System
---------
(Memsys - in files mem\_sim\_memsystem.cpp & mem\_sim\_memsystem.hpp)

This takes read, write, and flush requests. It looks up and returns the appropriate data in a vector of uint8_t, and passes requests through to the cache to obtain information about the timing and hit/miss status, before returning this timing and hit/miss information.

The Cache
---------
(Cache - in files mem\_sim\_cache.cpp & mem\_sim\_cache.hpp)

The cache and the following two classes are entirely unconcerned with managing the actual data. All it manages is 'metadata', for example, whether a particular block is valid, or in the cache, or which block is the LRU.

This class contains a vector of sets (initialised in the constructor), as well as helper functions to look up the appropriate set for a particular word address.
It then despatches any read/write requests to that set to manage, and takes the hit/miss information and uses it to calculate the cycletime.

The flush signal communicates with each of the sets and asks them to both clear any dirty blocks, and return the number of dirty blocks. It sums them, and calculates the cycletime.


The Set
-------
(Set - in files mem\_sim\_set.cpp & mem\_sim\_set.hpp)

The set manages its blocks via a vector (initialised in the set constructor). It handles updating of statistics regarding LRU, as well as choosing which set to use for any new data that needs to enter the cache, as well as which set contains which data.

The Block
----------
(Block - in files mem\_sim\_block.cpp & mem\_sim\_set.hpp)

The block doesn't really do much - it's just a container for various bits of data, such as dirty & tag.