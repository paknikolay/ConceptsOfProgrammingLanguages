#pragma once

#include <iostream>
#include <string>
#include <bitset>
#include <sstream>

enum class CMD {
    PUSH = 10,
    POP = 20
};

std::string ToString( CMD cmd )
{
    switch( cmd ) {
        case CMD::PUSH:
            return "PUSH";
        case CMD::POP:
            return "POP";
    }
}

CMD FromChar( char cmd )
{
    switch( cmd ) {
        case 10:
            return CMD::PUSH;
        case 20:
            return CMD::POP;
    }
}

char ToChar( CMD cmd )
{
    switch( cmd ) {
        case CMD::PUSH:
            return 10;
        case CMD::POP:
            return 20;
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

void skip( const char* str, int& iter )
{
    while ( !isalnum( str[iter] ) ){
        ++iter;
    }
}

int StringToInt( const char* str, int& iter )
{
    skip( str, iter );
    int n = 0;
     while( isdigit( str[iter] ) ) {
         n += str[iter] - '0';
         ++iter;
     }
}


