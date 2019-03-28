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
        int argCount = GetCMDArgsCount( cmd ) * 4;
        ip += argCount;
        return reinterpret_cast<const int*>( bin + ip - argCount );
    }

    int GetNextArg()
    {
        ip += 4;
        return *reinterpret_cast<const int*>( bin + ip - 4);
    }

    CMD GetNextCMD()
    {
        return FromChar( bin[ip++] );
    }

    const char* GetPointer( int ip )
    {
        return (bin + ip);
    }

    int GetIp()
    {
        return ip;
    }

    void SetIp( int newIp )
    {
        ip = newIp;
    }

private:
    const char* bin;
    int ip;
};