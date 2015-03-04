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

    protected:
        bool init(unsigned int size);//根据位数初始空间

    public:
        BitSet(){m_bits=NULL;m_size=m_bytes=0;}
        BitSet(unsigned int size);
        BitSet(const char* bits);//string to init bitset

        ~BitSet() { free(m_bits);m_bits=NULL;m_size=m_bytes=0; }

        unsigned char* getBits(){return m_bits;}
        unsigned int getBytes(){return m_bytes;}
        unsigned int getSize(){return m_size;}

        void setBits(unsigned char* bits){if(m_bits!=NULL){free(m_bits);}m_bits=bits;}
        void setBytes(unsigned int bytes){m_bytes=bytes;}
        void setSize(unsigned int size){m_size=size;}

        bool append(unsigned int pos);//根据当前位判断追加一段内存

        bool reset();//清空
        bool fill();//全部设置为1

        //动态扩展
        bool set(unsigned int pos);//设置某位为1
        bool unSet(unsigned int pos);//设置某位为0
        bool isSet(unsigned int pos);//某位是否设置为1
    
        //可用操作符重载实现
        unsigned char* andOp(BitSet* bits);//与操作
        unsigned char* orOp(BitSet* bits);//或操作
        unsigned char* xorOp(BitSet* bits);//异或操作
        BitSet* notOp();//非操作
        
        void print();
};
#endif //BITSET_HPP
