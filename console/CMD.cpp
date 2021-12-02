/*############################################################################################################
# File: /Users/leonexxe/Documents/GitKraken/ProjectX_Library/console/CMD.cpp                                 #
# Project: /Users/leonexxe/Documents/GitKraken/ProjectX_Library/console                                      #
# Created Date: Wednesday, November 24th 2021, 10:18:24 pm                                                   #
# Author: Leonexxe (Leon Marcellus Nitschke-Höfer)                                                           #
# -----                                                                                                      #
# Copyright (c) 2021 Leon Marcellus Nitschke-Höfer (Leonexxe)                                                #
# -----                                                                                                      #
# You may not remove or alter this copyright header.                                                         #
############################################################################################################*/
#pragma once
#include "CMD.h"

namespace px
{
    CMD::CMD(std::string name)
        :name(name){}


    std::list<std::string[2]> CMD::getSwitches(std::string input)
    {
        std::list<std::string[2]> result;
        std::string currentSwitch[2];

        bool isQuoted = 0;
        bool isArgument = 0;

        int cStart = 0;
        int cLength = 0;
        int pos = 0;
        bool isFirst = 1;
        for(char I : input)
        {
            if(I == ' ' && isFirst)
                isFirst = 0;
            else if(I == '"')
                isQuoted = 1;
            else if(I == ' ' && !isQuoted && !isArgument)
            {
                currentSwitch[0] = input.substr(cStart,cLength);
                cLength = 0;
                isArgument = 1;
            }
            else if(I == ' ' && !isQuoted && isArgument)
            {
                currentSwitch[1] = input.substr(cStart,cLength);
                cLength = 0;
                isArgument = 0;
            }
            else
            {
                if(cLength == 0)
                    cStart = pos;
                cLength++;
            }
            pos++;
        }

        return result;
    }
}