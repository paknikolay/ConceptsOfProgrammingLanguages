#include <iostream>

#include "tryCatch.h"

class A
{
public:
    A() { std::cout << "A being constructed\n"; }
    ~A() { std::cout << "A being destructed\n"; }
};


class B
{
public:
    B() { std::cout << "B being constructed\n"; }
    ~B() { std::cout << "B being destructed\n"; }
};



void example2(int iter=0) {

    A a;
    MARK(a);

    if (iter == 3) {
        THROW(EXAMPLE_TWO_RIGHT_EXCEPTION);
    }

    TRY(example2(iter + 1);)
    CATCH(EXAMPLE_TWO_WRONG_EXCEPTION, std::cerr << "wrong";);
}

int main()
{
/*************************************/
    TRY(B b; MARK(b);THROW(EXAMPLE_ONE_EXCEPTION))
    CATCH_ALL()

/*************************************/
    TRY(
        TRY(
            example2() ;
            )
        CATCH(EXAMPLE_TWO_RIGHT_EXCEPTION,))
    CATCH_ALL()


/*************************************/
    TRY(THROW(EXAMPLE_THREE_EXCEPTION_ONE))
    CATCH_ALL(THROW(EXAMPLE_THREE_EXCEPTION_TWO))

    return 0;
}