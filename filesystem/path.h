/*############################################################################################################
# File: /Users/leonexxe/Documents/GitKraken/ProjectX_Library/filesystem/folder.                              #
# Project: /Users/leonexxe/Documents/GitKraken/ProjectX_Library/filesystem                                   #
# Created Date: Thursday, December 2nd 2021, 8:19:25 am                                                      #
# Author: Leonexxe (Leon Marcellus Nitschke-Höfer)                                                           #
# -----                                                                                                      #
# Copyright (c) 2021 Leon Marcellus Nitschke-Höfer (Leonexxe)                                                #
# -----                                                                                                      #
# You may not remove or alter this copyright header.                                                         #
############################################################################################################*/
#include "master.h"

namespace px::filesystem
{
    class path
    {
    private:
        std::list<std::string> segments;
    public:
        path(std::string p = "/");
        ~path();

        std::list<std::string> list();
        void stepOut();
    };
}