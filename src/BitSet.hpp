#ifndef BITSET_HPP
#define BITSET_HPP

#include <cstdlib>
#include <cstring>
#include <iostream>
#define BYTE_SIZE 8

class BitSet
{
    private:
        unsigned int m_size;//BitSit位数
        unsigned char* m_bits;//分配的内存空间
        unsigned int m_bytes;//字节数

    public:
        BitSet(){}
        BitSet(unsigned int size);

        ~BitSet() { free(m_bits); }

        bool set(unsigned int pos);
        bool unSet(unsigned int pos);
        bool isSet(unsigned int pos);
        void print();
};
#endif //BITSET_HPP
