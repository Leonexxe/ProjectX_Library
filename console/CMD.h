/*############################################################################################################
# File: /Users/leonexxe/Documents/GitKraken/ProjectX_Library/console/CMD.h                                   #
# Project: /Users/leonexxe/Documents/GitKraken/ProjectX_Library/console                                      #
# Created Date: Wednesday, November 24th 2021, 10:18:29 pm                                                   #
# Author: Leonexxe (Leon Marcellus Nitschke-Höfer)                                                           #
# -----                                                                                                      #
# Copyright (c) 2021 Leon Marcellus Nitschke-Höfer (Leonexxe)                                                #
# -----                                                                                                      #
# You may not remove or alter this copyright header.                                                         #
############################################################################################################*/
#pragma once
#include <string>
#include <list>

namespace px
{
    class CMD
    {
    private:
        std::string name;
        std::string(*execute)(std::string input,CMD* cmd);
    public:
        CMD(std::string name);

        std::list<std::string[2]> getSwitches(std::string input);
    };
}