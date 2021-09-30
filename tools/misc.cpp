/*############################################################################################################
# File: c:\Users\Administrator\OneDrive\Dokumente\GitHub\ProjectX_Library\tools\misc.cpp                     #
# Project: c:\Users\Administrator\OneDrive\Dokumente\GitHub\ProjectX_Library\tools                           #
# Created Date: Thursday, September 2nd 2021, 7:45:37 pm                                                     #
# Author: Leonexxe (Leon Marcellus Nitschke-Höfer)                                                           #
# -----                                                                                                      #
# Copyright (c) 2021 Leon Marcellus Nitschke-Höfer (Leonexxe)                                                #
# -----                                                                                                      #
# You may not remove or alter this copyright header.                                                         #
############################################################################################################*/

#pragma once
#include <list>
#include <string>
#include "../sysout.h"
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
namespace px 
{
    std::list<boost::filesystem::path> FSListDir(boost::filesystem::path PATH,bool recursive = 1,bool doSysout = 0,int depth = 0, bool doNotCheckIsFolder = 0)
    {
        std::list<boost::filesystem::path> ret;
        if(doNotCheckIsFolder || boost::filesystem::is_directory(PATH))
        {
            if(doSysout)
            {
                for(int I = 0;I<depth;I++)
                    std::cout << "| ";
                std::cout << PATH.filename() << std::endl;
            }
            for(auto& entry : boost::make_iterator_range(boost::filesystem::directory_iterator(PATH), {}))
            {
                if(doSysout)
                    std::cout << entry << std::endl;
                if(boost::filesystem::is_directory(entry) && recursive)
                {
                    for(boost::filesystem::path I : FSListDir(entry,recursive,doSysout,++depth,1))
                        ret.push_back(I);
                }
            }
        }
        return ret;
    }
    std::list<boost::filesystem::path> FSFind(std::string filename,std::string baseFolder,bool recursive = 1,bool doSysout = 0)
    {
        std::list<boost::filesystem::path> ret;
        for(boost::filesystem::path I : FSListDir(baseFolder,1,1))
            if(I.filename() == filename)
                ret.push_back(I);
        return ret;   
    }
}