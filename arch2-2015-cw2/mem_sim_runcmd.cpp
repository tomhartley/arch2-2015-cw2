//
//  mem_sim_runcmd.cpp
//  arch2-2015-cw2
//
//  Created by Tom on 04/01/2016.
//  Copyright © 2016 Tom Hartley. All rights reserved.
//

#include "mem_sim_runcmd.hpp"
#include <sstream>
#include <iomanip>

string processLine(string iStr, Memsys &memory) {
	stringstream sstr;
	sstr.str(iStr);
	string cmd;
	
	sstr>>cmd;
	if (cmd=="") {
		return "#Please enter a command";
	}
	if(cmd=="read-req"){
		uint32_t address;
		sstr>>address;
		return read_req(address, memory);
	}else if(cmd=="write-req"){
		uint32_t address;
		sstr>>address;
		string hexdata;
		sstr>>hexdata;
		vector<uint8_t> bytes = decodeHex(hexdata);
		return write_req(address, bytes, memory);
	} else if (cmd=="flush-req") {
		return flush_req(memory);
	} else if (cmd=="debug-req") {
		return debug_req(memory);
	} else if (cmd.at(0)=='#') {
		return "";
	} else {
		return "#Unrecognised Command";
	}
}

vector<uint8_t> decodeHex(string hexdata) {
	vector<uint8_t> bytes;
	//since 1 byte is 2 hex chars, we process it 2 chars by 2 chars.
	int numBytes = (int)hexdata.length()/2;
	for (int i = 0; i<numBytes; i++) {
		uint32_t newByte;
		string substr = hexdata.substr(i*2,2);
		stringstream sstr(substr);
		sstr >> hex >> newByte >> dec;
		bytes.push_back((uint8_t)newByte); //the cast is neccessary because uint8_t is actually just a typedef for unsigned char... so it inputs the char value. Ugh.
	}
	return bytes;
}

string encodeHex(const vector<uint8_t> &data) {
	stringstream output;
	for (int i = 0; i<data.size();i++) {
		output << hex << uppercase << setfill('0') << setw(2) << (uint32_t)data[i];
	}
	return output.str();
}

string write_req(uint32_t address, vector<uint8_t> &data, Memsys &memory) {
	unsigned setIndex;
	bool didHit;
	unsigned time = memory.write(address, data, setIndex, didHit);
	stringstream ostr;
	ostr << "write-ack " << setIndex << " " << (didHit ? "hit" : "miss") << " " << time;
	
	return ostr.str();
}

string read_req(uint32_t address, Memsys &memory) {
	vector<uint8_t> returnData;
	unsigned setIndex;
	bool didHit;
	unsigned time = memory.read(address, returnData, setIndex, didHit);
	stringstream ostr;
	ostr << "read-ack " << setIndex << " " << (didHit ? "hit" : "miss") << " " << time << " " << encodeHex(returnData);
	return ostr.str();
}

string flush_req(Memsys &memory) {
	unsigned time = memory.flush();
	stringstream ostr;
	ostr << "flush-ack " << time;
	return ostr.str();
}

string debug_req(Memsys &memory) {
	return "debug-ack-begin\ndebug-ack-end";
}
