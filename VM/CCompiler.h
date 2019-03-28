#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include <map>

#include "Commands.h"
#include "CCommandHandler.h"
#include "CRam.h"
class CCompiler{
public:

    void Compile( const char* programPath, const char* destPath ) {
        varPosInCode.clear();
        labelPosInCode.clear();

        compile( programPath, destPath );
        //to fill labels and vars
        std::string bin = compile( programPath, destPath );
        std::ofstream out( destPath);
        out<< bin;

        out.close();
    }

    void Decompile( const char* programBinPath, const char* destPath ) {
        std::ofstream out( destPath );
        out << decompile( programBinPath );
    }

private:
    std::map<int, int> varPosInCode;
    std::map<int, int> labelPosInCode;



    std::string compile( const char* programPath, const char* destPath ) {
        std::ifstream in( programPath );
        std::string content( ( std::istreambuf_iterator<char>(in) ),
                             ( std::istreambuf_iterator<char>() ) );

        const char* program = content.data();

        std::stringstream bin;
        int iter = 0;
        int ip = 0;

        bool isData = false;
        bool isEnd = false;
        while( program[iter] != 0 && !isData && !isEnd ) {
            skip( program, iter );
            CMD cmd;
            switch ( program[iter] ) {
                case 'J': {
                    switch( program[++iter] ) {
                        case 'M': {
                            cmd = CMD::JMP;
                            bin << ToChar(cmd);
                            iter += 2;
                            int label = StringToInt(program, iter);
                            bin << IntToBinary(labelPosInCode[label]);
                            break;
                        }
                        case 'E':{
                            cmd = CMD::JE;
                            bin << ToChar(cmd);
                            iter += 1;
                            int label = StringToInt(program, iter);
                            bin << IntToBinary(labelPosInCode[label]);
                            break;
                        }
                        case 'A': {
                            cmd = CMD::JA;
                            bin << ToChar(cmd);
                            iter += 1;
                            int label = StringToInt(program, iter);
                            bin << IntToBinary(labelPosInCode[label]);
                            break;
                        }
                        case 'B':
                            cmd = CMD::JB;
                            bin << ToChar(cmd);
                            iter += 1;
                            int label = StringToInt(program, iter);
                            bin << IntToBinary(labelPosInCode[label]);
                            break;
                    }
                    break;

                }
                case 'C': {
                    cmd = CMD::CALL;
                    bin << ToChar(cmd);
                    iter += 4;
                    int label = StringToInt(program, iter);
                    bin << IntToBinary(labelPosInCode[label]);
                    break;
                }
                case 'D':
                    switch( program[++iter] ) {
                        case 'A':
                            cmd = CMD::DATA;
                            bin << ToChar(cmd);
                            iter += 3;
                            isData = true;
                            break;
                        case 'I':
                            cmd = CMD::DIV;
                            bin << ToChar(cmd);
                            iter += 2;
                            break;
                    }
                    break;
                case 'R':
                    cmd = CMD::RET;
                    bin << ToChar( cmd );
                    iter +=  3;
                    break;
                case 'I':
                    cmd = CMD::IN;
                    bin << ToChar( cmd );
                    iter +=  2;
                    break;
                case 'M':
                    cmd = CMD::MUL;
                    bin << ToChar( cmd );
                    iter +=  3;
                    break;
                case 'O':
                    cmd = CMD::OUT;
                    bin << ToChar( cmd );
                    iter +=  3;
                    break;
                case 'A':
                    cmd = CMD::ADD;
                    bin << ToChar( cmd );
                    iter +=  3;
                    break;
                case 'S':
                    switch( program[++iter] ) {
                        case 'U':
                            cmd = CMD::SUB;
                            bin << ToChar(cmd);
                            iter += 2;
                            break;
                        case 'T':
                            cmd = CMD::STOP;
                            bin << ToChar(cmd);
                            iter += 3;
                            break;
                    }
                    break;
                case 'P':
                    switch ( program[++iter] ) {
                        case 'R': {
                            cmd = CMD::PRINT;
                            bin << ToChar(cmd);
                            iter += 4;
                            int var = StringToInt(program, iter);
                            bin << IntToBinary(varPosInCode[var]);
                            break;
                        }
                        case 'U':
                            iter += 3;
                            switch ( program[iter] ) {
                                case 'R':
                                    cmd = CMD::PUSHR;
                                    bin << ToChar(cmd);
                                    iter += 1;
                                    bin << IntToBinary(StringToInt(program, iter));
                                    break;
                                default:
                                    cmd = CMD::PUSH;
                                    bin << ToChar(cmd);
                                    bin << IntToBinary(StringToInt(program, iter));
                                    break;
                            }
                            break;
                        case 'O':
                            cmd = CMD::POP;
                            skip( program, iter );

                            bin << ToChar( cmd );
                            iter += 2;
                            bin << IntToBinary( StringToInt( program, iter ) );
                            break;
                    }
                    break;
                case ':': {
                    cmd = CMD::LABEL;
                    bin << ToChar(cmd);
                    int label = StringToInt(program, ++iter);
                    int begIt = ip + 1 + 4; //ip + cmd + arg, should be after label, point to the next command
                    bin << IntToBinary(label); //label number


                    labelPosInCode[label] = begIt;
                    break;
                }

                case 'E':
                    cmd = CMD::END;
                    bin << ToChar(cmd);
                    iter += 3;
                    isEnd = true;

                    break;
            }

            increaseIp( ip, cmd );
        }

        //поиск строковых переменных формат :name(int) "str value" 5: "hello world"

        while( program[iter] != 0 && !isEnd ) {
            skip( program, iter );
            switch ( program[iter ++] ) {
                case 'E': {
                    CMD cmd = CMD::END;
                    bin << ToChar(cmd);
                    iter += 3;
                    isEnd = true;
                    ip += 1;
                    break;

                }
                case ':':
                    int var = StringToInt( program, iter );
                    skip( program, iter );

                    int begIt = iter + 1; //skip "
                    int endIt = findStringEnd( program, iter );
                    bin << ToChar( CMD::STR );
                    bin << IntToBinary( var ); //str name
                    bin << IntToBinary( endIt - begIt ); //str len

                   // std::cout<<"size = " << endIt - begIt <<"\n";
                    varPosInCode[var] = ip + 1 + 4; //skip STR + str name
                    increaseIp( ip, 1 + 4 + 4 + (endIt - begIt) );//STR + name + size + str

                    for( int i = begIt; i < endIt; i++) {
                        bin << program[i];
                    }

                    break;
            }
        }

        for (int j = 0; j < DEFAUL_RAM_SIZE - ip; ++j) {
            bin << 0;
        }

        return bin.str();
    }

    std::string decompile( const char* programBinPath ) {
        std::ifstream in( programBinPath );
        std::string content( (std::istreambuf_iterator<char>(in) ),
                             (std::istreambuf_iterator<char>()    ) );

        const char* bin = content.data();
        int size = content.size();

        std::stringstream program;
        int iter = 0;

        int ip = 0;
        CCommandHandler handler( bin );

        bool isEnd = false;
        bool isData = false;
        while( !isEnd && ! isData ) {
            CMD cmd = handler.GetNextCMD();
            switch( cmd ) {
                case CMD::LABEL: {
                    int label = handler.GetNextArg();
                    int ip = handler.GetIp();
                    //labelPosInCode[ip] = label;
                    program << ": " << ip << "\n";
                    break;
                }
                default:
                    program << ToString(cmd) << " ";
                    int argsCount = GetCMDArgsCount(cmd);
                    if (cmd == CMD::END) {
                        isEnd = true;
                    }
                    if (cmd == CMD::DATA) {
                        isData = true;
                    }
                    for (int i = 0; i < argsCount; ++i) {
                        program << handler.GetNextArg() << " ";
                    }

                    program << "\n";
                    break;
            }
        }


        while( !isEnd ) {
            CMD cmd = handler.GetNextCMD();
            if( cmd == CMD::END ) {
                isEnd = true;
                program << ToString(cmd) << " ";
                break;
            }
            int var = handler.GetNextArg();
            program << ": " << handler.GetIp() << " \"";
            int strSize = handler.GetNextArg();
            for (int i = 0; i < strSize; ++i) {
                program << ( ToChar( handler.GetNextCMD() ) );
            }
            program << "\"\n";
        }


        return program.str();

    }


    void increaseIp( int& ip, CMD cmd )
    {
        ip += 1 + GetCMDArgsCount( cmd ) * 4;

    }

    //for str vars
    void increaseIp( int& ip, int val )
    {
        ip += val;
    }

    void skip( const char* str, int& iter )
    {
        while ( !isalnum( str[iter] ) && str[iter] != ':' && str[iter] != '\"' ){
            ++iter;
        }
    }

    int StringToInt( const char* str, int& iter )
    {
        skip( str, iter );
        int n = 0;
        while( isdigit( str[iter] ) ) {
            n = n * 10 + str[iter] - '0';
            ++iter;
        }
        return n;
    }

    int findStringEnd( const char* str, int& iter )
    {
        skip( str, iter );
        if ( str[iter] != '\"' ) {
            std::cout<< "SOMETHING WRONG!!! STRING NOT FOUND\n";
            abort();
        }

        while( str[++iter] != '\"' );

        ++iter;

        return iter - 1;
    }
};