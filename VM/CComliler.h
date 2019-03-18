#pragma once

#include <fstream>
#include <sstream>
#include <vector>

#include "Commands.h"

class CCompiler{
public:
    CCompiler( const char* programPath ) {
        std::ifstream in( programPath );

        std::stringstream buffer( programPath );
        buffer << in.rdbuf();
        const char* program = buffer.str().data();

        std::vector<char> bin;
        int iter = 0;

        while( program[iter] != 0 ) {

            CMD cmd;
            switch ( program[iter] ) {
                case 'P':
                    switch ( program[++iter] ) {
                        case 'U':
                            cmd = CMD::PUSH;
                            bin.push_back( ToChar( cmd ) );
                            iter +=  3;
                            break;
                        case 'O':
                            cmd = CMD::POP;
                            bin.push_back( ToChar( cmd ) );
                            //and add args
                            iter += 2;
                    }
            }



        }
    }

private:

};