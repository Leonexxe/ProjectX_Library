/*
Author: Leon Nitschke-Höfer (leonexxe@leonexxe.de)
dstructs.cpp (c) 2021
Desc: description
Created:  2021-07-26T03:26:05.903Z
Modified: 2021-08-02T00:26:55.358Z
*/

#include <list>
#include <string>
#include <memory>

namespace px
{
    namespace helper
    {
        class Property        
        {
        public:
            Property(){}
            virtual ~Property(){}
        };  
        
        template<typename T>
        class TypedProperty : public Property
        {
        private:
            T m_data;
            
        public:
            TypedProperty(const T& data)
                :m_data(data){}
        };
    }
    
    template<typename... types>
    class table
    {
    private:
        std::list<std::list<px::helper::Property>> data;
    public:
        table(){}

        template<typename T>
        bool add(int row,int column)
        {
        }
    };
}
