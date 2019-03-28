#pragma once

#include "CRam.h"
#include "CProcessor.h"

#define RECURSION_DEPTH 100
class CVM {
public:
    CVM( const char* initialProg, int ramSize = DEFAUL_RAM_SIZE ):
    ram( ramSize ),
    processor( ram, reinterpret_cast<int*>( ram.GetPointer( 3 * ramSize / 4 ) ), 3 * ramSize / 4 - RECURSION_DEPTH,
               reinterpret_cast<int*>(ram.GetPointer( 3 * ramSize / 4 + RECURSION_DEPTH ) ) , RECURSION_DEPTH,
               initialProg )
    {
    }

    void Start()
    {
        while(processor.NextStep());
    }

private:
    char* programImage;
    CRam ram;
    CProcessor processor;

};
