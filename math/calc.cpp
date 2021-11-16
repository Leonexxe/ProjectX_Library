/*############################################################################################################
# File: /Users/leonexxe/Documents/Github/ProjectX_Library/math/calc.cpp                                      #
# Project: /Users/leonexxe/Documents/Github/ProjectX_Library/math                                            #
# Created Date: Tuesday, October 12th 2021, 7:45:36 pm                                                       #
# Author: Leonexxe (Leon Marcellus Nitschke-Höfer)                                                           #
# -----                                                                                                      #
# Copyright (c) 2021 Leon Marcellus Nitschke-Höfer (Leonexxe)                                                #
# -----                                                                                                      #
# You may not remove or alter this copyright header.                                                         #
############################################################################################################*/
#include "../tools/strings.cpp"
namespace px
{
    struct calc_var {
        std::string name;
        std::string value;
        calc_var(std::string name, std::string value)
            : name(name), value(value){}
    };
    enum calc_mode {
        DEF,EQ
    };

    std::string calc(std::string input,std::list<calc_var> variables)
    {
        calc_mode mode = DEF;
        if(px::strContains(&input,"="))
            mode = EQ;

        for(calc_var v : variables)
        {
            
        }
    }

    std::string solve()
    {
    }
}