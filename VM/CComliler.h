#pragma once

#include <fstream>
#include <sstream>
#include <vector>

#include "Commands.h"
#include "CCommandHandler.h"

class CCompiler{
public:

    void Compile( const char* programPath, const char* destPath ) {
        std::ifstream in( programPath );
        std::ofstream out( destPath );

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

        out << bin.str();
    }


    void Decompile( const char* programBinPath, const char* destPath ) {
        std::ifstream in( programBinPath );
        std::ofstream out( destPath );

        std::stringstream buffer;
        buffer << in.rdbuf();
        const char* bin = buffer.str().data();

        std::stringstream program;
        int iter = 0;

        CCommandHandler handler( bin );

        while( true ) {
            CMD cmd = handler.GetNextCMD();
            program << ToString( cmd );
            int argsCount = GetCMDArgsCount( cmd );
            if ( cmd == CMD::END) {
                break;
            }
            for( int i = 0; i < argsCount; ++i ) {
                program << handler.GetNextArg() << " ";
            }
        }


        out << program.str();
    }

private:

};