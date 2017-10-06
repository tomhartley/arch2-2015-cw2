//
//  mem_sim_set.cpp
//  arch2-2015-cw2
//
//  Created by Tom on 06/01/2016.
//  Copyright © 2016 Tom Hartley. All rights reserved.
//

#include "mem_sim_set.hpp"
#include <assert.h>

Set::Set(unsigned blocksPerSet, unsigned wordsPerBlock, unsigned bytesPerWord) {
	wordsInBlock = wordsPerBlock;
	bytesInWord = bytesPerWord;
	numBlocks = blocksPerSet;
	for (int i = 0; i<blocksPerSet; i++) {
		Block newBlock;
		blocks.push_back(newBlock);
	}
}

int Set::getLruIndex() {
	for (int i = 0; i<numBlocks; i++) {
		Block *b = &blocks[i];
		if (b->accessIndex == 0) {
			return i;
		}
	}
	//if we get here there's an inconsistancy...
	assert(false);
}

bool Set::isLRUdirty() {
	Block* b = &blocks[getLruIndex()];
	return b->dirty;
}

bool Set::isLRUvalid() {
	Block* b = &blocks[getLruIndex()];
	return b->valid;
}

uint32_t Set::makeTag(uint32_t address) {
	//address is a word aligned byte address
	//if there's 4 bytes per word, remove the last 2 bits [etc]
	unsigned bpw = bytesInWord;
	while (bpw>>=1) address >>= 1; //equivalent of shifting addr by log2 of bpw
	
	//now address is a word address. now to get a block address // block address==tag
	unsigned wpb = wordsInBlock;
	while (wpb>>=1) address >>= 1;
	
	return address;
}

bool Set::containsByte(uint32_t addr) {
	int i = getMatchingIndex(addr);
	return (i!=-1);
}

int Set::getMatchingIndex(uint32_t addr) {
	uint32_t newTag = makeTag(addr);
	for (int i = 0; i<numBlocks; i++) {
		if (blocks[i].tagMatches(newTag)) {
			return i;
		}
	}
	return -1; //not found
}

void Set::decrementCounts(unsigned above) {
	//decrementing every index greater than above. For example if above is 4, then 5,6,7 go to 4,5,6 and 4 goes to 7.
	for (int i = 0; i<numBlocks; i++) {
		Block* b = &blocks[i];
		if (b->accessIndex>above) {
			b->accessIndex--;
		}
	}
}

void Set::writeData(uint32_t addr) {
	uint32_t tag = makeTag(addr);
	int i = getMatchingIndex(addr);
	if (i==-1) { //so this is a cache miss. Evict, evict!
		int x = getLruIndex();
		Block* replaceBlock = &blocks[x];
		decrementCounts(replaceBlock->accessIndex);
		replaceBlock->accessIndex = numBlocks-1; //if there's 8 blocks, it is now 7. This goes down to 0 - then it's the LRU
		replaceBlock->setTag(tag);
		replaceBlock->dirty = true; //set it as dirty, as we just updated it after bringing it in
	} else if (i!=-1) {
		Block* foundBlock = &blocks[i];
		foundBlock->dirty = true;
		decrementCounts(foundBlock->accessIndex);
		foundBlock->accessIndex = numBlocks-1;
	}
}

void Set::readData(uint32_t addr) {
	uint32_t tag = makeTag(addr);
	int i = getMatchingIndex(addr);
	if (i==-1) {
		//Bring it into the cache
		int x = getLruIndex();
		Block* replaceBlock = &blocks[x];
		decrementCounts(replaceBlock->accessIndex);
		replaceBlock->accessIndex = numBlocks-1; //if there's 8 blocks, it is now 7. This goes down to 0 - then it's the LRU
		replaceBlock->setTag(tag);
	} else if (i!=-1) {
		//it's in the cache already
		Block* foundBlock = &blocks[i];
		decrementCounts(foundBlock->accessIndex);
		foundBlock->accessIndex = numBlocks-1;
	}
}

int Set::clearDirty() {
	int dirtyCount = 0;
	for (int i = 0; i<blocks.size(); i++) {
		Block* b = &blocks[i];
		if (b->dirty) {
			dirtyCount++;
			b->dirty = false;
		}
	}
	return dirtyCount;
}













