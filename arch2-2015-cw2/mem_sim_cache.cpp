 //
//  mem_sim_cache.cpp
//  arch2-2015-cw2
//
//  Created by Tom on 06/01/2016.
//  Copyright © 2016 Tom Hartley. All rights reserved.
//

#include "mem_sim_cache.hpp"

Cache::Cache(unsigned nNumSets,
		  unsigned nBytesPerWord,
		  unsigned nWordsPerBlock,
		  unsigned nBlocksPerSet,
		  unsigned nHitTime,
		  unsigned nMemReadTime,
		  unsigned nMemWriteTime,
		  unsigned nAddressBits) {
	numSets = nNumSets;
	bytesPerWord = nBytesPerWord;
	wordsPerBlock = nWordsPerBlock;
	blocksPerSet = nBlocksPerSet;
	hitTime = nHitTime;
	memReadTime = nMemReadTime;
	memWriteTime = nMemWriteTime;
	addressBits = nAddressBits;
	
	//now create numSets sets
	for (int i = 0; i < numSets; i++) {
		Set newSet(blocksPerSet,wordsPerBlock,bytesPerWord);
		sets.push_back(newSet);
	}
}

unsigned Cache::getSet(uint32_t address) {
	//address is a word aligned byte address
	//if there's 4 bytes per word, remove the last 2 bits [etc]
	unsigned bpw = bytesPerWord;
	while (bpw>>=1) address >>= 1; //equivalent of shifting addr by log2 of bpw
	
	//now address is a word address. now to get a block address
	unsigned wpb = wordsPerBlock;
	while (wpb>>=1) address >>= 1;
	
	//now address is a block address. time to find it's set
	//if there are 2 sets, it's the last bit. if 4, it's the last 2 bits
	
	unsigned mask = 0;
	for (int i = 1; i<numSets; i*=2) {
		//I've never written a for loop like this before
		mask = (mask << 1) + 1;
	}
	
	return address & mask; //bitwise &
}

unsigned Cache::fetchData(uint32_t address, bool &didHit) {
	unsigned setI = getSet(address);
	unsigned totalTime = 0;
	Set *theSet = &sets[setI];
	if (theSet->containsByte(address)) {
		//it's a hit!
		theSet->readData(address);
		totalTime+=hitTime;
		didHit = true;
	} else {
		//not a hit!
		totalTime+=hitTime;
		if (theSet->isLRUdirty()) {
			totalTime+=memWriteTime;
		}
		totalTime+=memReadTime;
		didHit = false;
		theSet->readData(address);
	}
	return totalTime;
}

unsigned Cache::writeData(uint32_t address, bool &didHit) {
	unsigned setI = getSet(address);
	unsigned totalTime = 0;
	Set* theSet = &sets[setI];
	if (theSet->containsByte(address)) {
		//it's a hit!
		theSet->writeData(address);
		totalTime+=hitTime;
		didHit = true;
	} else {
		//not a hit!
		totalTime+=hitTime;
		if (theSet->isLRUdirty()) {
			totalTime+=memWriteTime;
		}
		if (wordsPerBlock!=1) { //cheeky optimisation, no point bringing it into memory if you're about to overwrite it
			totalTime+=memReadTime;
		}
		didHit = false;
		theSet->writeData(address);
	}
	return totalTime;
}

unsigned Cache::flushAll() {
	unsigned totalDirty = 0;
	for (int i = 0; i<numSets; i++) {
		totalDirty+=sets[i].clearDirty();
	}
	return totalDirty*memWriteTime;
}

//read and it's in cache:
//--HIT_TIME

//read and it's not in cache:
//--HIT_TIME + READ_TIME + (potential WRITE_TIME if the thing that's getting evicted is 'dirty')


//write and it's in cache:
//set dirty bit, and update main memory [faked]
//time is: HIT_TIME

//write and it's not in cache:
//bring it into cache (READ_TIME) [Not neccesarry if 1word/block] [potentially evicting something else, which is WRITE_TIME]
//then set dirty bit, fake update main memory. + HIT_TIME

//flush...loop over everything in the memory.If dirty: ++WRITE_TIME

