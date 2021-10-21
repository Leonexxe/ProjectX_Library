#pragma once
#include <string>
#include <list>
namespace px
{
    namespace tools
    {
        namespace arrays
        {
            /**
             * @brief finds the array element that has the value of target and gives it's index number back.(-1 if not found)
             * example: a[5] = "cat", target="cat", return = 5
             * 
             * @param target 
             * @return int 
             */
            template<typename type, size_t S>
            int find(type target,type (&a)[S])
            {
                for(size_t i = 0; i < sizeof(a)/sizeof(a[0]);i++)
                {
                    if(a[i] == target)
                    {
                        return int(i);
                    }
                }
                return -1;
            }


            template<typename type>
            type* list_to_array(std::list<type>* list)
            {
                type* array[list->size()];
                int i = 0;
                for(type I : *list)
                {   
                    array[i++] = &I;
                }
                return array;
            }

            /**
             * @brief converts 'const char*' to 'char*' by calling strdup
             * 
             * @param CC 
             * @return char* 
             */
            char* constCharArrayToCharArray(const char* CC)
            {
                #ifdef PX_WIN
                    return _strdup(CC);
                #else
                    return strdup(CC);
                #endif
            }
        }
    }
}