#pragma once

#include <functional>
#include <cstring>
#include <iostream>


class CStack {
public:
    CStack( int* buffer, int maxSize ) :
    maxSize( maxSize ),
    buffer( buffer )
    {
        size = 0;
    }

    ~CStack()
    {
    };

    void Push( const int& item )
    {
        buffer[size++] = item;
    }

    int Pop()
    {
        return buffer[--size];
    }

    const int &Top() const
    {
        return buffer[size - 1];
    }

    int GetEsp()
    {
        return size;
    }

private:
    int  size;
    int* buffer;
    int maxSize;
};
