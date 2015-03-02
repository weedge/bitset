#include "BitSet.hpp"

BitSet::BitSet(unsigned int size)
{
    this->m_bytes = size/BYTE_SIZE + 1; 
    this->m_size = this->m_bytes*BYTE_SIZE; 
    this->m_bits = (unsigned char*) malloc(this->m_bytes);
    memset(this->m_bits,0,this->m_bytes);
}

bool BitSet::set(unsigned int pos)
{
    if(pos>=this->m_size) return false;
    int index = pos/BYTE_SIZE;
    int bit_pos = pos%BYTE_SIZE;
    this->m_bits[index] |= 128U>>bit_pos;

    return true;
}

bool BitSet::unSet(unsigned int pos)
{
    if(pos>=this->m_size) return false;
    int index = pos/BYTE_SIZE;
    int bit_pos = pos%BYTE_SIZE;
    this->m_bits[index] &= ~(128U>>bit_pos);

    return true;
}

bool BitSet::isSet(unsigned int pos)
{
    if(pos>this->m_size) return false;
    int index = pos/BYTE_SIZE;
    int bit_pos = pos%BYTE_SIZE;
    if((this->m_bits[index] & (128U>>bit_pos))) return true; 

    return false;
}

void BitSet::print()
{
    std::cout<<"this "<<this->m_bytes<<" bitset chars:"<<std::endl;
    for(unsigned int i=0; i<this->m_bytes; i++) {
        std::cout<<(unsigned int)this->m_bits[i];
    }

    std::cout<<std::endl;

}

