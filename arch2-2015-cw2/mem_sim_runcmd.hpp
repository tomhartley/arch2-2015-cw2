//
//  mem_sim_runcmd.hpp
//  arch2-2015-cw2
//
//  Created by Tom on 04/01/2016.
//  Copyright © 2016 Tom Hartley. All rights reserved.
//

#ifndef mem_sim_runcmd_hpp
#define mem_sim_runcmd_hpp

#include <stdio.h>
#include <string>
#include <cstdint>

#include "mem_sim_memsystem.hpp"

using namespace std;

string processLine(string str, Memsys &memory);

vector<uint8_t> decodeHex(string hexdata);
string encodeHex(const vector<uint8_t> & data);

string write_req(uint32_t address, vector<uint8_t> &data, Memsys &memory);

string read_req(uint32_t address, Memsys &memory);

string flush_req(Memsys &memory);

string debug_req(Memsys &memory);


#endif /* mem_sim_runcmd_hpp */
