#include <string>
#include <list>
#include <projectX/sysout.h>
#include "../tools/textmanipulation.cpp"
#include "convert.cpp"
namespace px
{
    namespace converters
    {
        void CharArrayToStr(char* src, std::string* target)
        {
            for(int I = 0;I<(sizeof(src) / sizeof(src[0]));I++)
            {
                *target += src[I];
            }
        }
        void CharArrayToStr(const char* src, std::string* target)
        {
            for(int I = 0;I<(sizeof(src) / sizeof(src[0]));I++)
            {
                *target += src[I];
            }
        }

        void strToInt(int* target, std::string* src)
        {
            int mult = 1;
            std::string str = px::text::manipulation::reverse(src);
            for(char I : str)
            {
                int c = 0;
                switch(I)
                {
                    case('0'):c=0;break;
                    case('1'):c=1;break;
                    case('2'):c=2;break;
                    case('3'):c=3;break;
                    case('4'):c=4;break;
                    case('5'):c=5;break;
                    case('6'):c=6;break;
                    case('7'):c=7;break;
                    case('8'):c=8;break;
                    case('9'):c=9;break;
                    default:std::cout << px::ErrorPrefix() << "\"" << I << "\"" << " is not a number!" << std::endl;continue;
                }
                *target+=c*mult;
                mult *= 10;
            }
        }

        namespace clone
        {
            template<typename type>
            void list_to_array(std::list<type>* source_list,type *target_array)
            {
                int i = 0;
                for(type I : *source_list)
                {   
                    target_array[i++] = I;
                }
            }
        }

        namespace pointers
        {
            template<typename type>
            void list_to_array(std::list<type>* source_list,type* *target_array)
            {
                int i = 0;
                for(type I : *source_list)
                {   
                    target_array[i++] = &I;
                }
            }
        }
    }
}