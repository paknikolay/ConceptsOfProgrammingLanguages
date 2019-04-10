#pragma once

#include <iostream>
#include <stdexcept>
#include <queue>
#include <vector>

#include <setjmp.h>

#define EXAMPLE_ONE_EXCEPTION 2
#define EXAMPLE_TWO_WRONG_EXCEPTION 3
#define EXAMPLE_TWO_RIGHT_EXCEPTION 4
#define EXAMPLE_THREE_EXCEPTION_ONE 5
#define EXAMPLE_THREE_EXCEPTION_TWO 6


#define MAX_TRY 100

jmp_buf ENV[MAX_TRY];
int jmp_count = -1;
bool isCleaning = false;
#define TRY(CODE) switch(int VAL = setjmp(ENV[++jmp_count])) {\
                    case 0: {\
                        CODE\
                        break;\
                    }\


#define CATCH(EXCEPTION, CODE) case EXCEPTION: {\
                                        isCleaning = true;\
                                        for (int i = 0; i < destructors[jmp_count].size(); ++i) { \
                                            destructors[jmp_count][i]();\
                                        }\
                                        jmp_count--;\
                                        CODE;\
                                        isCleaning = false;\
                                        break;\
                                }\
                                default:\
                                    for (int i = 0; i < destructors[jmp_count].size(); ++i) { \
                                        destructors[jmp_count][i]();\
                                    }\
                                    jmp_count--;\
                                    longjmp(ENV[jmp_count], VAL);\
                                    break;\
                    }\


#define THROW(EXCEPTION) if(!isCleaning) {\
                            longjmp(ENV[jmp_count], EXCEPTION);\
                            } else {\
                            std::cerr<<"during pocessing exception raised another exception!!!\n";\
                            abort();\
                            }\

#define CATCH_ALL(CODE) default:{\
                            isCleaning = true;\
                            for (int i = 0; i < destructors[jmp_count].size(); ++i) { \
                                destructors[jmp_count][i]();\
                            }\
                            jmp_count--;\
                            CODE;\
                            isCleaning = false;\
                            std::cerr<<"exception " << VAL << " occurred\n";\
                            break;\
                            }\
                 }\



class destructor
{
    const void* p;
    void(*destroy)(const void*);
public:
    destructor() : p(nullptr), destroy([](const void*){}) {}
    destructor(const destructor& rhs) : p(rhs.p), destroy(rhs.destroy) {}

    template <typename T>
    destructor(T& t) : p{std::addressof(t)}, destroy{[](const void* x) { if (x) reinterpret_cast<const T*>(x)->~T();}} {}

    void operator()() const { destroy(p); }
};


std::vector<destructor> destructors[MAX_TRY];
int destructor_count = 0;

#define MARK(obj) destructors[jmp_count].emplace_back(obj);
