//
//  mem_sim_memsystem.cpp
//  arch2-2015-cw2
//
//  Created by Tom on 14/01/2016.
//  Copyright © 2016 Tom Hartley. All rights reserved.
//

#include "mem_sim_memsystem.hpp"

Memsys::Memsys(Cache &chc, unsigned addressBits,unsigned wordSize):cache(&chc),wordSize(wordSize), memData(((uint32_t)1)<<addressBits,0){
	
}

unsigned Memsys::read(uint32_t address, vector<uint8_t> &outputData,unsigned &setIndex, bool &didHit) {
	outputData.clear();
	for (int i = (address+wordSize-1); i>=(int32_t)address; i--) {
		outputData.push_back(memData[i]);//address,address+1 -> address
	}
	setIndex = cache->getSet(address);
	unsigned cycles = cache->fetchData(address, didHit);
	return cycles;
}

unsigned Memsys::write(uint32_t address, vector<uint8_t> &inputData,unsigned &setIndex, bool &didHit) {
	for (int i=address; i<(wordSize+address); i++) {
		memData[i]=inputData[wordSize-(i-address)-1]; //2-(0-0), 2-(1-0) ...
	}
	setIndex = cache->getSet(address);
	unsigned cycles = cache->writeData(address, didHit);
	return cycles;
}

unsigned Memsys::flush() {
	unsigned cycles = cache->flushAll();
	return cycles;
}