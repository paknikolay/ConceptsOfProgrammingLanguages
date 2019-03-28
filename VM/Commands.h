#pragma once

#include <iostream>
#include <string>
#include <bitset>
#include <sstream>

enum class CMD
{
#define DEF_CMD(name, num, argCount, code) \
    name = num,
#include "CommandHelper.h"

#undef DEF_CMD
};

std::string ToString( CMD cmd )
{
    switch( cmd ) {
        #define DEF_CMD(name, num, argCount, code) \
        case CMD::name: \
        return #name;
        #include "CommandHelper.h"

        #undef DEF_CMD
    }
}

bool IsSame( std::string cmd, const char* pattern )
{
    int i = 0;
    int len = 0, s = 0;
    while( cmd[i] != 0 || pattern[i] != 0 ) {
        if ( cmd[i] == pattern[i] ) {
            ++s;
        }
        ++len;
    }
    return  len == s;
}

CMD FromStr( std::string cmd )
{
        #define DEF_CMD(name, num, argCount, code) \
        if( IsSame( cmd, #name) ) \
        return CMD::name;
        #include "CommandHelper.h"

        #undef DEF_CMD
}

CMD FromChar( unsigned char cmd ) {
    switch (cmd) {
        #define DEF_CMD(name, num, argCount, code) \
        case num: \
        return CMD::name;
        #include "CommandHelper.h"

        #undef DEF_CMD
    }
}


char ToChar( CMD cmd ) {
    switch (cmd) {
        #define DEF_CMD(name, num, argCount, code) \
        case CMD::name: \
        return num;
        #include "CommandHelper.h"

        #undef DEF_CMD
    }
}

    std::string IntToBinary( int n )
    {
        std::stringstream buffer;
        for( int i = 0; i < 4; ++i ) {
            buffer << ( char ) n;
            n = ( n >> 8 );
        }

        return buffer.str();

    }



int GetCMDArgsCount( CMD cmd )
{
    switch( cmd ) {
        #define DEF_CMD(name, num, argCount, code) \
        case CMD::name: \
        return argCount;
        #include "CommandHelper.h"

        #undef DEF_CMD
        default:
            return 0;
    }
}