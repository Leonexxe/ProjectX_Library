#pragma once
#include "../constants/sizes.cpp"
#include "../tools/lists.cpp"
#include "../sysout.h"

namespace px
{
    namespace math
    {
        bool __init__(){srand(time(0));return 0;}
        bool m_init = __init__();
        static const int PERCENTAGE_ACCURACY = sizes::million;
        static const double PI = 3.14159265359; /*thanks google <3*/
        static const double* theFuckedUpNumber = &PI;
        /**
         * @brief calculate if a number is in between a min and a max
         * 
         * @param i 
         * @param min 
         * @param max 
         * @return int, returns -1 if x is smaller than min, returns 1 if x is bigger than max, returns 0 if x is in between min and max
         */
        static int isBetween(int x, int min, int max)
        {
            int ret = -1;
            if(x < max){ret += 1;}else{ret += 2;}
            if(x > min){ret += 0;}else{ret -= 1;}
            return ret;
        }

        static double percentage(int max, int part)
        {
            double percentage_small = double(part)/double(max);
            return percentage_small * 100;
        }

        template<typename type>
        type percent(type i, int percentage,bool ENHANCED_ACCURACY) {
            if(ENHANCED_ACCURACY)
            {
                long double multiplier = percentage*px::math::PERCENTAGE_ACCURACY/100;
                return i*multiplier/px::math::PERCENTAGE_ACCURACY;
            }
            long double multiplier = percentage/100;
            return i*multiplier;
        }

        template<typename inputType, typename returnType>
        returnType avarage(std::list<inputType>* input)
        {
            int i = 0;
            double total = 0;
            for(inputType I : *input)
            {
                total+=I;
                i++;
            }
            returnType av = total/i;
        }

        template<typename inputType, typename returnType>
        returnType power(inputType base, inputType exponent)
        {
            returnType result = base;
            for(int i = 0;i < exponent;i++)
            {
                result = result*exponent;
            }
            return result;
        }

        template<typename type>
        void useHighest(type* target, type* source)
        {
            if(*source > *target)
            {
                *target = *source;
            }
        }

        /**
         * @brief 
         * 
         * @tparam inputType 
         * @tparam returnType 
         * @param n total number of things
         * @param r number of things in a set
         * @return returnType 
         */
        template<typename inputType, typename returnType>
        returnType nPr(inputType n, inputType r)
        {
            returnType left;
            returnType right;
            std::cout << "(";
            for(inputType i = n;i>0;i--)
            {
                std::cout << i;
                if(i!=1)
                {
                    std::cout << "x";
                }
                left*=i;
            }
            std::cout << ")/";
            for(inputType i = (n-r);i>0;i--)
            {
                std::cout << i;
                if(i!=1)
                {
                    std::cout << "x";
                }
                right*=i;
            }
            std::cout << std::endl;
            std::cout << left << "/" << right << std::endl;
            if(left<right)
            {
                std::cout << px::ErrorPrefix() << &right << " is bigger than " << &left << "!" << std::endl;
            }
            
            return left/right;
        }

        template<typename returnType>
        returnType random()
        {
            return (returnType)rand();
        }

        /**
         * @brief this is **NOT** realtime safe! it is important that one can cast from inputType to returnType
         * 
         * @tparam inputType 
         * @tparam returnType 
         * @param min 
         * @param max 
         * @return returnType 
         */
        template<typename inputType,typename returnType>
        returnType random(inputType min, inputType max,std::list<inputType>* exclude = nullptr)
        {
            returnType R = (returnType)rand();
            while(R < min || R > max || px::tools::lists::contains(exclude,(inputType)R))
            {
                R = (returnType)rand();
                #ifdef PX_DEBUG
                    std::cout << R << std::endl;
                #endif
               
            }
            return R;
        }

        template<typename T>
        std::string int_to_hex(T i)
        {
          std::stringstream stream;
          stream << "0x" 
                 << std::setfill ('0') << std::setw(sizeof(T)*2) 
                 << std::hex << i;
          return stream.str();
        }
    }
}