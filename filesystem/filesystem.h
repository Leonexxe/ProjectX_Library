/*############################################################################################################
# File: /Users/leonexxe/Documents/GitKraken/ProjectX_Library/filesystem/filesystem.h                         #
# Project: /Users/leonexxe/Documents/GitKraken/ProjectX_Library/filesystem                                   #
# Created Date: Wednesday, December 1st 2021, 12:57:12 pm                                                    #
# Author: Leonexxe (Leon Marcellus Nitschke-Höfer)                                                           #
# -----                                                                                                      #
# Copyright (c) 2021 Leon Marcellus Nitschke-Höfer (Leonexxe)                                                #
# -----                                                                                                      #
# You may not remove or alter this copyright header.                                                         #
############################################################################################################*/
#pragma once
#include "master.h"

namespace px
{
    class fileSystem 
    {
        fileSystem(std::string SystemRoot = "/",std::string fileSeperator = "/");
        ~fileSystem();
    };
}
