#pragma once

#include "CStack.h"
#include "Commands.h"
#include "CCommandHandler.h"
#include "CRam.h"

class CProcessor {
public:
    explicit CProcessor( CRam& ram,  int* stackBuffer, int stackMaxSize, int* retStackBuffer, int retStackMaxSize,
                        const char* initialProg ):
    ram(ram),
    stack( stackBuffer, stackMaxSize ),
    retStack( retStackBuffer, retStackMaxSize ),
    handler( initialProg )
    {
        retStack.Push(4);
    }

    bool NextStep()
    {
        CMD nextCmd = handler.GetNextCMD();
        if( nextCmd == CMD::STOP ) {
            return false;
        }
        const int* args = handler.GetCMDArgs( nextCmd );

        switch( nextCmd ) {
        #define DEF_CMD(name, num, argCount, code) \
        case CMD::name: \
            name( args );\
            return true;
        #include "CommandHelper.h"

        #undef DEF_CMD

        }
        return true;
    }

private:

        #define DEF_CMD(name, num, argCount, code) \
        void name ( const int* args ) \
        code
        #include "CommandHelper.h"

        #undef DEF_CMD

private:
    int rax;
    int rbx;
    int rcx;
    int rdx;

    bool isEnd;

    CRam& ram;
    CStack stack;
    CStack retStack;
    CCommandHandler handler;

};
