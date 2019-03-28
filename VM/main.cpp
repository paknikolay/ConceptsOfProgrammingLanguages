#include <stack>
#include <fstream>
#include <sstream>
#include <map>

#include "CCompiler.h"
#include "CVM.h"
int main() {
    CCompiler compiler;
    compiler.Compile("file", "out.bin");

    compiler.Decompile("out.bin", "out");

    std::ifstream in("out.bin");
    std::string content((std::istreambuf_iterator<char>(in)),
                        (std::istreambuf_iterator<char>()));

    char *bin = new char[content.size()];

    for (int i = 0; i < content.size(); ++i) {
     //   std::cout<<(unsigned char)content[i] + 0<<" ";
        bin[i] = content[i];
    }
  //  std::cout<<"\n________________________\n";
    CVM vm(bin);

    vm.Start();


return 0;
}
