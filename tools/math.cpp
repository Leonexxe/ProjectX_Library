#include <string>
#include <list>

namespace px
{
    namespace tools
    {
        namespace combinations
        {
            long COMBINATION_LIST_MAX_SIZE = -1;
            std::list<std::string> combinations(std::string* pool)
            {
                std::list<std::string> c_list;
            }

            template<typename type>
            std::list<std::list<type*>> combinations(std::list<type>* pool)
            {
                std::list<std::list<type*>> c_list;
                for(type I : *pool)
                {
                    if(sizeof(c_list>=
                    (px::tools::combinations::COMBINATION_LIST_MAX_SIZE - (px::tools::combinations::COMBINATION_LIST_MAX_SIZE / 10))
                    )) {
                        break;
                    }
                    else
                    {
                        std::list<type*> sub_list;
                        for(type II : *pool)
                        {
                            if(!&I == &II)
                            {
                                if(COMBINATION_LIST_MAX_SIZE != -1) {
                                    if(sizeof(sub_list>=
                                    (px::tools::combinations::COMBINATION_LIST_MAX_SIZE - (px::tools::combinations::COMBINATION_LIST_MAX_SIZE / 10))
                                    )) {
                                        break;
                                    }
                                    else {
                                        sub_list.push_back(&II);
                                    }
                                }
                            }
                        }
                    }
                }
                return c_list;
            }
        }
    }
}