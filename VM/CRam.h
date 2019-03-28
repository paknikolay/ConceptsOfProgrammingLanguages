#pragma once

#include <iostream>
#include <stdexcept>

#define DEFAUL_RAM_SIZE 1024 * 1024 * 4

class CRam{
public:
    explicit CRam( char* pogramImage, int64_t size = DEFAUL_RAM_SIZE )
    {
        storage = pogramImage;
    }

    char* GetPointer( int64_t index )
    {
        return storage + index;
    }

    char& operator[]( int64_t index )
    {
        return storage[index];
    }

    ~CRam()
    {
        delete storage;
    }

private:
    int64_t size;
    char* storage;
};