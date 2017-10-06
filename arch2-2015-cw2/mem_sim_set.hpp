//
//  mem_sim_set.hpp
//  arch2-2015-cw2
//
//  Created by Tom on 06/01/2016.
//  Copyright © 2016 Tom Hartley. All rights reserved.
//

#ifndef mem_sim_set_hpp
#define mem_sim_set_hpp
#include <vector>
#include <cstdint>

#include "mem_sim_block.hpp"

using namespace std;

class Set
{
public:
	Set(unsigned blocksPerSet,
		unsigned wordsPerBlock,
		unsigned bytesPerWord);
	bool containsByte(uint32_t addr);
	bool isLRUdirty();
	bool isLRUvalid();
	void writeData(uint32_t addr);
	void readData(uint32_t addr);
	int clearDirty();
private:
	vector<Block> blocks;
	unsigned wordsInBlock;
	unsigned bytesInWord;
	unsigned numBlocks;
	uint32_t makeTag(uint32_t address);
	int getLruIndex();
	int getMatchingIndex(uint32_t addr);
	void decrementCounts(unsigned above);
};

#endif /* mem_sim_set_hpp */

