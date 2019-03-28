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
/*
   ADD = 01,
    SUB = 02,
    PRINT = 11,
    PUSH = 10,
    POP = 20,
    END = 255,
    LABEL = 254,
    STR = 200,
 */

};

std::string ToString( CMD cmd )
{
    switch( cmd ) {
#define DEF_CMD(name, num, argCount, code) \
        case CMD::name: \
        return #name;
#include "CommandHelper.h"

#undef DEF_CMD

    /*    case CMD::ADD:
            return "ADD";
        case CMD::SUB:
            return "SUB";
        case CMD::PRINT:
            return "PRINT";
        case CMD::PUSH:
            return "PUSH";
        case CMD::POP:
            return "POP";
        case CMD::END:
            return "END";
            */

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
   /* if( IsSame( cmd, "ADD" ) ) {
        return CMD::ADD;
    }

    if( IsSame( cmd, "SUB" ) ) {
        return CMD::SUB;
    }
    if( IsSame( cmd, "PRINT" ) ) {
        return CMD::PRINT;
    }
    if( IsSame( cmd, "LABEL" ) ) {
    return CMD::LABEL;
    }*/
}

CMD FromChar( unsigned char cmd ) {
    switch (cmd) {
#define DEF_CMD(name, num, argCount, code) \
        case num: \
        return CMD::name;
#include "CommandHelper.h"

#undef DEF_CMD
        /*
        case 01:
            return CMD::ADD;
        case 02:
            return CMD::SUB;
        case 11:
            return CMD::PRINT;
        case 10:
            return CMD::PUSH;
        case 20:
            return CMD::POP;
        case 255:
            return CMD::END;
        case 254:
            return CMD::LABEL;*/
    }
}


char ToChar( CMD cmd ) {
    switch (cmd) {
#define DEF_CMD(name, num, argCount, code) \
        case CMD::name: \
        return num;
#include "CommandHelper.h"

#undef DEF_CMD
        /*
        case CMD ::ADD:
            return 01;
        case CMD ::SUB:
            return 02;
        case CMD::PUSH:
            return 10;
        case CMD::POP:
            return 20;
        case CMD::END:
            return 255;
        case CMD::LABEL:
            return 254;*/
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
       /* case CMD::PUSH:
            return 1;
        case CMD::POP:
            return 1;
        case CMD::LABEL:
            return 1;*/
        default:
            return 0;
    }
}