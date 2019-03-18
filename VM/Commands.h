#pragma once

#include <iostream>
#include <string>
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

CMD FromChar( char cmd ) {
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
    std::string s = {0, 0, 0, 0};
    int  i = 0;
    while( n > 0 ) {
        s[i] = (char)( n >> (4 * i) );
        std::cout<<s[i] + 0 <<" " << n <<"\n";
        ++i;
        n = n >> (i * 4);

    }

    return s;

}
