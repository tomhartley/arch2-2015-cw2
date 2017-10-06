//
//  mem_sim_memsystem.hpp
//  arch2-2015-cw2
//
//  Created by Tom on 14/01/2016.
//  Copyright © 2016 Tom Hartley. All rights reserved.
//

#ifndef mem_sim_memsystem_hpp
#define mem_sim_memsystem_hpp

#include <stdio.h>
#include <cstdint>

#include "mem_sim_cache.hpp"

class Memsys
{
public:
	//constructor
	Memsys(Cache &chc,unsigned addressBits, unsigned wordSize);
	
	unsigned read(uint32_t address, vector<uint8_t> &outputData,unsigned &setIndex, bool &didHit);
	unsigned write(uint32_t address, vector<uint8_t> &inputData,unsigned &setIndex, bool &didHit);
	unsigned flush();
	
private:
	Cache* cache;
	vector<uint8_t> memData;
	unsigned wordSize;
};

#endif /* mem_sim_memsystem_hpp */
