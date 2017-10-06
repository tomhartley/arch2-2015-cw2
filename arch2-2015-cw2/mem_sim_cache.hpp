//
//  mem_sim_cache.hpp
//  arch2-2015-cw2
//
//  Created by Tom on 06/01/2016.
//  Copyright © 2016 Tom Hartley. All rights reserved.
//

#ifndef mem_sim_cache_hpp
#define mem_sim_cache_hpp

#include <stdio.h>
#include <vector>
#include <cstdint>

#include "mem_sim_set.hpp"

using namespace std;

class Cache
{
public:
	//constructor
	Cache(unsigned nSets,
		  unsigned nBytesPerWord,
		  unsigned nWordsPerBlock,
		  unsigned nBlocksPerSet,
		  unsigned nHitTime,
		  unsigned nMemReadTime,
		  unsigned nMemWriteTime,
		  unsigned nAddressBits);
	unsigned fetchData(uint32_t address, bool &didHit); //returns cycles
	unsigned writeData(uint32_t address, bool &didHit);
	unsigned flushAll(); //also returns cycles
	
	unsigned getSet(uint32_t address);
private:
	vector<Set> sets;
	
	unsigned numSets; //used
	unsigned bytesPerWord; //used
	unsigned wordsPerBlock; //used
	unsigned blocksPerSet;
	unsigned hitTime;
	unsigned memReadTime;
	unsigned memWriteTime;
	unsigned addressBits;
};

#endif /* mem_sim_cache_hpp */
