/*############################################################################################################
# File: /Users/leonexxe/Documents/GitKraken/ProjectX_Library/dict/dict.h                                     #
# Project: /Users/leonexxe/Documents/GitKraken/ProjectX_Library/dict                                         #
# Created Date: Monday, November 22nd 2021, 2:49:19 pm                                                       #
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
    class dict
    {
    private:
        dict* content;
        std::string value;
        std::string key;

        void resize(unsigned long long newSize);

    public:
        dict();
        dict(std::string key, std::string value);
        ~dict();

        void remove(std::string key);
        void add(std::string key,std::string value);
        void add(dict d);
        dict* get(std::string key) const;

        unsigned long long size() const;

        std::string _str() const;
        long long _int() const;
        unsigned long long _uint() const;

        dict* operator[](const std::string& key) const;
    };
}