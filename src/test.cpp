#include <iostream>
#include "BitSet.hpp"
#include <cmath>

void test_print(BitSet* bitset)
{
    bitset->print();
    char* str = bitset->toString();
    std::cout<<"bitset: "<<str<<" len:"<<strlen(str)<<std::endl;
    free(str);str=NULL;
}

//测试 init/toString/set/unSet/isSet/reset/fill
void test1()
{
    std::cout<<"test init/toString/set/unSet/isSet/reset/fill"<<std::endl;

    BitSet* bitset;
    unsigned int test_case_bit_size;
    test_case_bit_size = (unsigned int)pow(2,3);
    //test_case_bit_size = (unsigned int)pow(2,10);
    
    bitset = new BitSet(test_case_bit_size);
    test_print(bitset);

    bitset->set(0);
    test_print(bitset);

    bitset->set(7);
    test_print(bitset);

    bitset->set(1);
    test_print(bitset);

    bitset->unSet(7);
    test_print(bitset);

    if(bitset->isSet(7)){
        std::cout<<"this pos 7 is set~!"<<std::endl;
    }

    if(bitset->isSet(1)){
        std::cout<<"this pos 1 is set~!"<<std::endl;
    }

    if(bitset->isSet(0)){
        std::cout<<"this pos 0 is set~!"<<std::endl;
    }

    bitset->set(1023);
    test_print(bitset);
    if(bitset->isSet(1023)){
        std::cout<<"this pos 1023 is set~!"<<std::endl;
    }
    bitset->unSet(1023);
    test_print(bitset);
    if(!bitset->isSet(1023)){
        std::cout<<"this pos 1023 is unset~!"<<std::endl;
    }
    
    bitset->reset();
    std::cout<<"reset~!"<<std::endl;
    test_print(bitset);

    bitset->fill();
    std::cout<<"fill 1 for all pos~!"<<std::endl;
    test_print(bitset);

    delete bitset;
    bitset = NULL;
}

//测试bitset运算:&,|,^,~
void test2()
{
    std::cout<<"test operations: &, |, ^, ~"<<std::endl;
    /*
    {
        BitSet* b1;
        BitSet* b2;
        unsigned int test_case_bit_size;
        test_case_bit_size = (unsigned int)pow(2,3);
        //test_case_bit_size = (unsigned int)pow(2,10);

        b1 = new BitSet(test_case_bit_size);
        b2 = new BitSet(test_case_bit_size);

        delete b1;
        b1 = NULL;
        delete b2;
        b2 = NULL;

    }
    */

    {
        BitSet b3("101010101001");
        test_print(&b3);
        BitSet b4("110101001001");
        test_print(&b4);
        BitSet b5("110101000001");
        test_print(&b5);

        BitSet andOpBitSet = b3 & b4;
        test_print(&andOpBitSet);

        andOpBitSet.set(3);
        test_print(&andOpBitSet);
    }

    {
        std::cout<<"-------"<<std::endl;
        BitSet b3("10101010001");
        test_print(&b3);
        BitSet b4("110101000001");
        test_print(&b4);
        BitSet b5("11010100001");
        test_print(&b5);

        BitSet andOpBitSet = b3 & b4;
        test_print(&andOpBitSet);

        andOpBitSet.set(3);
        test_print(&andOpBitSet);
    }
    /*
    {
        BitSet b3("101010101000");
        test_print(&b3);
        BitSet b4("110101001001");
        test_print(&b4);

        BitSet andOpBitSet = b3 & b4;
        test_print(&andOpBitSet);

        andOpBitSet.set(3);
        test_print(&andOpBitSet);
    }
    */

}

int main()
{
    std::cout<<"test BitSet~!"<<std::endl;

    //test1();

    test2();

    return 0;
}




