/*############################################################################################################
# File: /Users/leonexxe/Documents/GitKraken/ProjectX_Library/filesystem/path.cpp                             #
# Project: /Users/leonexxe/Documents/GitKraken/ProjectX_Library/filesystem                                   #
# Created Date: Thursday, December 2nd 2021, 8:19:13 am                                                      #
# Author: Leonexxe (Leon Marcellus Nitschke-Höfer)                                                           #
# -----                                                                                                      #
# Copyright (c) 2021 Leon Marcellus Nitschke-Höfer (Leonexxe)                                                #
# -----                                                                                                      #
# You may not remove or alter this copyright header.                                                         #
############################################################################################################*/
#pragma once
#include "master.h"

#ifdef PX_WIN
    #define PX_FS_FS "\\"
#else
    #define PX_FS_FS "/"
#endif

namespace px::filesystem
{
    path::path(std::string p = PX_FS_FS)
    {
    }

    std::string strPath()
    {
        std::string result = PX_FS_FS;
        for(std::string I : this->segments)
        {
            result+=I+PX_FS_FS;
        }
        return result;
    }

    void stepOut()
    {
    }
}