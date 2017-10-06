#include <iostream>
#include <string>
#include <sstream>

#include <cstdlib>

#include <cstdint>

#include "mem_sim_runcmd.hpp"
#include "mem_sim_cache.hpp"
#include "mem_sim_memsystem.hpp"

using namespace std;

int main(int argc, char *argv[]) {
	
    if (argc!=9) {
        return 1;
    }
    
    int addressBits, bytesInWord, wordsInBlock, blocksInSet, setsInCache, cyclesPerHit, cyclesPerRead, cyclesPerWrite; //cyclesPerWrite/Read are both per-block.
    addressBits = atoi(argv[1]);
    bytesInWord = atoi(argv[2]);
    wordsInBlock = atoi(argv[3]);
    blocksInSet = atoi(argv[4]);
    setsInCache = atoi(argv[5]);
    cyclesPerHit = atoi(argv[6]);
    cyclesPerRead = atoi(argv[7]);
    cyclesPerWrite = atoi(argv[8]);
	
	Cache cch(setsInCache, bytesInWord, wordsInBlock, blocksInSet, cyclesPerHit, cyclesPerRead, cyclesPerWrite, addressBits);
	Memsys mem(cch, addressBits, bytesInWord);
	
    while(1){
        string line;

        if (getline(cin,line)) {
            string op = processLine(line, mem);
            if (op!="") {
                cout << op << endl;
            }
        } else {
            //End of File
            break;
        }

    }


    return 0;
}