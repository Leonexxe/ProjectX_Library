#include "PXE3.cpp"

namespace PXE3
{
    template<short length>
    void bruteforce(PXE3::key* <length>Key, std::string cypher)
    {
        PXE3::key <length>Key_temp;
        for(int I = 0;I<127;I++)
        {
            for(int II = 1;II<length;II++)
            {
                Key_temp.subKeys[I].arr[II] = ;
            }
        }
    }
    
    std::list<char> subComb;
    std::list<std::list<char>> comb;
    
    short length = 0;
    short subPos = 0;
    short Pos = 0;
    short Counter = 1;
    short subCounter = 1;
    
    void generateNextComb()
    {
        comb.empty();
        for(int I = 0;I<127;I++)
        {
            if(I<Pos)
                comb.push_back(1,1,1,1,1):; // am at school right now, will insert proper code later;
            else
                generateNextSubComb();
                comb.push_back(subComb);
        }
    }
    
    void generateNextSubComb()
    {
        subCommb.empty();
        for(int I = 0;I<length;I++)
        {
            switch(subCounter)
            {
                case(127):
                    subPos++;
                    subCounter=1;
                    break;
                default:
                    subCounter++;
                    break;
            }
            for(int I = 0;I<subPos;I++)
            {
                subComb.push_back((char)127);
            }
        }
    }
}
