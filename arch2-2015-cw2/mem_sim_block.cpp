//
//  mem_sim_block.cpp
//  arch2-2015-cw2
//
//  Created by Tom on 06/01/2016.
//  Copyright © 2016 Tom Hartley. All rights reserved.
//

#include "mem_sim_block.hpp"

Block::Block() {
	valid = false;
	tag = UINT32_MAX; //impossible to get an actual tag this high.
	accessIndex = 0;
	dirty = false;
}

void Block::setTag(uint32_t newTag) {
	tag=newTag;
	valid = true;
	dirty = false;
}

bool Block::tagMatches(uint32_t newTag) {
	return (tag==newTag);
}
