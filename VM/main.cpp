#include <stack>
#include <fstream>
#include <sstream>
#include <map>

#include "CCompiler.h"
#include "CVM.h"
int main() {
    CCompiler compiler;
    compiler.Compile( "fibonacci", "fibonacci_out.bin" );

    compiler.Decompile( "fibonacci_out.bin", "fibonacci_out" );

    std::ifstream in( "fibonacci_out.bin" );
    std::string content( ( std::istreambuf_iterator<char>( in ) ),
                        ( std::istreambuf_iterator<char>() ) );

    char *bin = new char[content.size()];

    for ( int i = 0; i < content.size(); ++i)  {
        bin[i] = content[i];
    }
    CVM vm( bin );
    vm.Start();


    return 0;
}
