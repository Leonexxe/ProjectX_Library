#pragma once
#include <list>

namespace px
{
    namespace tools
    {
        namespace lists
        {
            /**
             * @brief get a element in a list by index
             * 
             * @tparam type 
             * @param list 
             * @param index 
             * @return type (list->back if (index > list))
             */
            template<typename type>
            type getElementByIndex(std::list<type> *list, int index)
            {
                int count = 0;
                for(type I : *list)
                {
                    if(count++ == index)
                    {
                        return I;
                    }
                }
                return list->back();
            }

            template<typename type>
            static const int getSize(std::list<type>* list) {
                int i = 0;
                for(type I : *list)  {
                    i++;
                }
                return i;
            }

            template<typename T>
            T* getFirst(std::list<T>* list)
            {
                T* ret = nullptr;
                for(T i : *list)
                {
                    ret = &i;
                    break;
                }
                return ret;
            }
            template<typename T>
            T* getLast(std::list<T>* list)
            {
                T* ret = nullptr;
                for(T i : *list)
                {
                    ret = &i;
                }
                return ret;
            }
        }
    }
}