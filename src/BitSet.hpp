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

        bool append(unsigned int pos);//根据当前位判断追加一段内存

        unsigned char* andOp(BitSet* bits);//与操作
        unsigned char* orOp(BitSet* bits);//或操作
        unsigned char* xorOp(BitSet* bits);//异或操作
        unsigned char* notOp();//非操作

    public:
        BitSet()
        {
            m_bits = (unsigned char*) malloc(1);
            m_bits[0]='\0';
            m_size=m_bytes=0;
        }

        BitSet(unsigned int size);
        BitSet(const char* bits);//string to init bitset

        ~BitSet()
        { 
            if(m_bits!=NULL){
                //std::cout<<"delete~"<<std::endl;
                free(m_bits);
                m_bits=NULL;
                m_size=m_bytes=0;
            }
        }

        unsigned char* getBits(){return m_bits;}
        unsigned int getBytes(){return m_bytes;}
        unsigned int getSize(){return m_size;}

        void setBits(unsigned char* bits)
        {
            if(m_bits!=NULL){
                //std::cout<<"free"<<std::endl;
                free(m_bits);
                m_bits=NULL;
            }

            m_bits = bits;

            /*
            int len = strlen((const char*)bits);
            m_bits = (unsigned char*) malloc(len+1);
            strcpy((char *)m_bits,(const char*)bits);
            m_bits[len] = '\0';
            */
        }

        void setBytes(unsigned int bytes){m_bytes=bytes;}
        void setSize(unsigned int size){m_size=size;}

        bool reset();//清空
        bool fill();//全部设置为1

		bool isEmpty();//是否为空


        //动态扩展
        bool set(unsigned int pos);//设置某位为1
        bool unSet(unsigned int pos);//设置某位为0
        bool isSet(unsigned int pos) const;//某位是否设置为1
    
        //操作符重载实现
        //http://en.wikipedia.org/wiki/Operators_in_C_and_C%2B%2B
        BitSet operator&(BitSet &bits);
        BitSet operator|(BitSet &bits);
        BitSet operator^(BitSet &bits);
        BitSet operator~();

        //for test
        void print() const;
        char* toString() const;
};
#endif //BITSET_HPP
