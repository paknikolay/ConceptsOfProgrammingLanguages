#pragma once

#include "Commands.h"

class CCommandHandler{
public:
    CCommandHandler( const char* bin ):
    bin( bin ),
    ip( 0 )
    {
    }

    const int* GetCMDArgs( CMD cmd )
    {
        int argCount = GetCMDArgsCount( cmd ) * 8;
        ip += argCount;
        return reinterpret_cast<const int*>( bin + ip - argCount );
    }

    int GetNextArg()
    {
        ip += 8;
        return *reinterpret_cast<const int*>( bin + ip );
    }

    CMD GetNextCMD()
    {
        return FromChar( bin[ip++] );
    }
private:
    const char* bin;
    int ip;
};