#pragma once

#include <fstream>
#include <sstream>
#include <vector>

#include "Commands.h"

class CCompiler{
public:

    void Compile( const char* programPath, const char* destPath ) {
        std::ifstream in( programPath );

        std::stringstream buffer;
        buffer << in.rdbuf();
        const char* program = buffer.str().data();

        std::stringstream bin;
        int iter = 0;

        while( program[iter] != 0 ) {
            skip( program, iter );
            CMD cmd;
            switch ( program[iter] ) {
                case 'P':
                    switch ( program[++iter] ) {
                        case 'U':
                            cmd = CMD::PUSH;
                            bin << ToChar( cmd );
                            iter +=  3;
                            bin << IntToBinary( StringToInt( program, iter ) );
                            break;
                        case 'O':
                            cmd = CMD::POP;
                            skip( program, iter );

                            bin << ToChar( cmd );
                            //and add args
                            iter += 2;
                    }
            }
        }
    }


    void Decompile( const char* programBinPath, const char* destPath ) {
        std::ifstream in( programBinPath );

        std::stringstream buffer;
        buffer << in.rdbuf();
        const char* programBin = buffer.str().data();

        std::stringstream program;
        int iter = 0;

        while ( iter < buffer.str().size() ) {
            buffer <<
        }
    }

private:

};