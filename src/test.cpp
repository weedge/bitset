#include <iostream>
#include "BitSet.hpp"
#include <cmath>

int main()
{
    std::cout<<"test BitSet~!"<<std::endl;
    BitSet* bitset;
    unsigned int test_case_bit_size;
    test_case_bit_size = (unsigned int)pow(2,3);
    test_case_bit_size = (unsigned int)pow(2,10);
    
    bitset = new BitSet(test_case_bit_size);
    bitset->print();
    bitset->set(0);
    bitset->print();
    bitset->set(7);
    bitset->print();
    bitset->set(1);
    bitset->print();
    bitset->unSet(7);
    bitset->print();

    if(bitset->isSet(7)){
        std::cout<<"this pos 7 is set~!"<<std::endl;
    }

    if(bitset->isSet(1)){
        std::cout<<"this pos 1 is set~!"<<std::endl;
    }

    if(bitset->isSet(0)){
        std::cout<<"this pos 0 is set~!"<<std::endl;
    }

    return 0;
}




