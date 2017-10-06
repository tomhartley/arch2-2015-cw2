//
//  mem_sim_block.hpp
//  arch2-2015-cw2
//
//  Created by Tom on 06/01/2016.
//  Copyright © 2016 Tom Hartley. All rights reserved.
//

#ifndef mem_sim_block_hpp
#define mem_sim_block_hpp

#include <vector>
#include <cstdint>

using namespace std;

class Block
{
public:
	Block();
	void setTag(uint32_t block_addr);
	bool tagMatches(uint32_t addr);
	unsigned accessIndex; //0 indicates soon to be replaced! - gets reset to max on access
	bool valid;
	bool dirty;
	
private:
	uint32_t tag;
};


#endif /* mem_sim_block_hpp */
