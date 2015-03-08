#include "BitSet.hpp"

BitSet::BitSet(unsigned int size)
{
    if(!this->init(size)) exit(-1);
}

BitSet::BitSet(const char* bits)
{
    unsigned int size = strlen(bits);
    if(!this->init(size)) exit(-1);
    
    unsigned int bit_index,char_index;
    for(bit_index=char_index=0; char_index<size; char_index++)
    {
        if(bits[char_index]=='1'){
            this->set(char_index);
        }else{
            this->unSet(char_index);
        }
    }
}

bool BitSet::init(unsigned int size)
{ 
    this->m_bytes = size%BYTE_SIZE>0 ? (size/BYTE_SIZE + 1) 
        : (size/BYTE_SIZE); 
    this->m_size = this->m_bytes*BYTE_SIZE; 
    this->m_bits = (unsigned char*) malloc(this->m_bytes+1);
    if(this->m_bits==NULL && this->m_bytes!=0) return false;
    memset(this->m_bits,0,this->m_bytes+1);
    this->m_bits[this->m_bytes] = '\0';

    return true;
}

bool BitSet::append(unsigned int pos){
    if(pos<this->m_size) return false;

    int new_len = (this->m_bytes*2*BYTE_SIZE>pos) ? (this->m_bytes*2) : (pos/BYTE_SIZE+1);
    this->m_bits = (unsigned char*)realloc(this->m_bits,new_len+1);
    memset(this->m_bits+this->m_bytes,0,new_len-this->m_bytes+1);
    this->m_bits[new_len] = '\0';
    this->m_size = new_len * BYTE_SIZE;
    this->m_bytes = new_len;

    return true;
}

bool BitSet::set(unsigned int pos)
{
    if(pos>=this->m_size){
        this->append(pos);
    }
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

bool BitSet::isSet(unsigned int pos) const
{
    if(pos>=this->m_size) return false;
    int index = pos/BYTE_SIZE;
    int bit_pos = pos%BYTE_SIZE;
    if((this->m_bits[index] & (128U>>bit_pos))) return true; 

    return false;
}

unsigned char* BitSet::andOp(BitSet* bits)
{
    unsigned char* opStr;
    int len = this->m_bytes > bits->getBytes() ? bits->getBytes() : this->m_bytes;
    opStr = (unsigned char*) malloc(len+1);
    memset(opStr,0,len+1);
    opStr[len] = '\0';

    //8字节
    for(int count=0; count<len/sizeof(unsigned long); count++)
    {
        ((unsigned long*)opStr)[count] = 
            ((unsigned long*)this->m_bits)[count] & ((unsigned long*)bits->getBits())[count];
    }

    //剩余的1字节处理
    for(int count=len-len%sizeof(unsigned long); count<len; count++)
    {
        ((unsigned char*)opStr)[count] = 
            ((unsigned char*)this->m_bits)[count] & ((unsigned char*)bits->getBits())[count];
    }
    
    return (unsigned char*)opStr;
}

BitSet BitSet::operator&(BitSet &bits)
{
    BitSet res;

    unsigned char* opStr = this->andOp(&bits);
    unsigned int len = strlen((const char*)opStr);

    res.setBits(opStr);
    res.setBytes(len);
    res.setSize(len*BYTE_SIZE);
    
    return res;
}

unsigned char* BitSet::orOp(BitSet* bits)
{
    unsigned char* opStr;
    int len,op_len,len1,len2;
    
    //处理多出部分
    len1 = this->m_bytes;
    len2 = bits->getBytes();
    if(len1 == len2){
        len = len1;
        op_len = len2;
        opStr = (unsigned char*) malloc(len+1);
    }else if(len1 > len2){
        len = len1;
        op_len = len2;
        opStr = (unsigned char*) malloc(len+1);
        memcpy(opStr+op_len,this->m_bits+op_len,len1-len2);
    }else{
        len = len2;
        op_len = len1;
        opStr = (unsigned char*) malloc(len+1);
        memcpy(opStr+op_len,bits->getBits()+op_len,len2-len1);
    }
    opStr[len] = '\0';
    
    //8字节
    for(int count=0; count<op_len/sizeof(unsigned long); count++)
    {
        ((unsigned long*)opStr)[count] = 
            ((unsigned long*)this->m_bits)[count] | ((unsigned long*)bits->getBits())[count];
    }

    //剩余的1字节处理
    for(int count=op_len - op_len%sizeof(unsigned long); count<op_len; count++)
    {
        ((unsigned char*) opStr)[count] = 
            ((unsigned char*)this->m_bits)[count] | ((unsigned char*)bits->getBits())[count];
    }

    return (unsigned char*)opStr;
}

BitSet BitSet::operator|(BitSet &bits)
{
    BitSet res;

    unsigned char* opStr = this->orOp(&bits);
    int len = strlen((const char*)opStr);

    res.setBits(opStr);
    res.setBytes(len);
    res.setSize(len*BYTE_SIZE);
    
    return res;
}

unsigned char* BitSet::xorOp(BitSet* bits)
{
    unsigned char* opStr;
    int len,op_len,len1,len2;

    len1 = this->m_bytes;
    len2 = bits->getBytes();
    if(len1==len2){
        len = op_len = len1;
    }else if(len1>len2){
        len = op_len = len1;
        bits->append(this->m_size);
    }else{
        len = op_len = len2;
        this->append(bits->getSize());
    }
    opStr = (unsigned char*) malloc(len+1);
    opStr[len] = '\0';

    //8字节
    for(int count=0; count<op_len/sizeof(unsigned long); count++)
    {
        ((unsigned long*)opStr)[count] = 
            ((unsigned long*)this->m_bits)[count] ^ ((unsigned long*)bits->getBits())[count];
    }

    //剩余的1字节处理
    for(int count=op_len - op_len%sizeof(unsigned long); count<op_len; count++)
    {
        ((unsigned char*) opStr)[count] = 
            ((unsigned char*)this->m_bits)[count] ^ ((unsigned char*)bits->getBits())[count];
    }

    return (unsigned char*)opStr;
}

BitSet BitSet::operator^(BitSet &bits)
{
    BitSet res;
    
    unsigned char* opStr = this->xorOp(&bits);
    int len = strlen((const char*)opStr);

    res.setBits(opStr);
    res.setBytes(len);
    res.setSize(len*BYTE_SIZE);
    
    
    return res;
}

unsigned char* BitSet::notOp()
{
    unsigned char* opStr;
    opStr = (unsigned char*) malloc(this->m_bytes+1);
    memset(opStr,0,this->m_bytes+1);

    //8字节
    for(int count=0; count<this->m_bytes/sizeof(unsigned long); count++)
    {
        ((unsigned long*)opStr)[count] = ~((unsigned long*)this->m_bits)[count] ;
    }

    //剩余的1字节处理
    for(int count=this->m_bytes - this->m_bytes%sizeof(unsigned long); count<this->m_bytes; count++)
    {
        ((unsigned char*)opStr)[count] = ~((unsigned char*)this->m_bits)[count] ;
    }

    opStr[this->m_bytes] = '\0';

    return (unsigned char*)opStr;
}

BitSet BitSet::operator~()
{
    BitSet res;

    unsigned char* opStr = this->notOp();
    int len = strlen((const char*)opStr);

    res.setBits(opStr);
    res.setBytes(len);
    res.setSize(len*BYTE_SIZE);
    
    return res;
}

bool BitSet::reset()
{
    if(this->m_bytes<=0) return false;
    
    for(int i=0;i<this->m_bytes;i++) {
        this->m_bits[i] &= 0;
    }
    
    return true;
}

bool BitSet::fill()
{
    if(this->m_bytes<=0) return false;
    for(int i=0;i<this->m_bytes;i++) {
        this->m_bits[i] |= (256U-1);
    }
    return true;
}

bool BitSet::isEmpty()
{
    //8字节
    for(int count=0; count<this->m_bytes/sizeof(unsigned long); count++) {
        if(((unsigned long*)this->m_bits)[count]){
			return false;
		}
    }

    //剩余的1字节处理
    for(int count=this->m_bytes - this->m_bytes%sizeof(unsigned long); count<this->m_bytes; count++) {
        if(((unsigned char*)this->m_bits)[count]){
			return false;
		}
    }

	return true;
}

void BitSet::print() const
{
    std::cout<<"this "<<this->m_bytes<<" bitset-chars to unsigned int of byte_size:"<<std::endl;
    for(unsigned int i=0; i<this->m_bytes; i++) {
        std::cout<<(unsigned int)this->m_bits[i];
    }

    std::cout<<std::endl;
}

char* BitSet::toString() const
{
    char* str;
    str = (char*) malloc(this->m_size+1);
    memset(str,0,this->m_size+1);
    str[this->m_size] = '\0';
    for(int i=0; i<this->m_size; i++){
        str[i] = (this->m_bits[i/BYTE_SIZE] & (128U>>(i%BYTE_SIZE))) ? '1' : '0';
    }

    return str;
}


