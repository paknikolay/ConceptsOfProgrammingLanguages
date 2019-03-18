#pragma once

#include <fstream>
#include <sstream>
class CCompiler{
public:
    CCompiler( const char* programPath ) {
        std::ifstream in( programPath );

        std::stringstream buffer( programPath );
        buffer << in.rdbuf();
        const char* program = buffer.str().data();

        int iter = 0;

        while( program[iter] != 0 ) {
            switch( program[iter] ) {
                case 'p':
            }
        }
    }

private:

};