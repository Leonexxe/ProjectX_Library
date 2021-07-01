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
    
    void generateNextComb()
    {
    }
    
    void generateNextSubComb()
    {
        for(int I = 0;I<length;I++)
        {
        }
    }
}
