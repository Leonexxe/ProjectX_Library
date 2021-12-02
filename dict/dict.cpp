/*############################################################################################################
# File: /Users/leonexxe/Documents/GitKraken/ProjectX_Library/dict/dict.cpp                                   #
# Project: /Users/leonexxe/Documents/GitKraken/ProjectX_Library/dict                                         #
# Created Date: Monday, November 22nd 2021, 2:49:26 pm                                                       #
# Author: Leonexxe (Leon Marcellus Nitschke-Höfer)                                                           #
# -----                                                                                                      #
# Copyright (c) 2021 Leon Marcellus Nitschke-Höfer (Leonexxe)                                                #
# -----                                                                                                      #
# You may not remove or alter this copyright header.                                                         #
############################################################################################################*/
#pragma once

#include "dict.h"
namespace px
{
    dict::dict(){}
    dict::dict(std::string key,std::string value)
        :key(key),value(value){}

    dict::~dict()
    {
        delete[] this->content;
    }

    void dict::add(std::string key,std::string value)
    {
        this->add(dict(key,value));
    }

    void dict::add(dict d)
    {
        this->resize(this->size()+1);
        this->content[this->size()-1] = d;
    }

    void dict::remove(std::string key)
    {
        unsigned long long rem = 0;
        for(unsigned long long I = 0; I < this->size();I++)
            if(this->content[I].key == key)
            {
                rem = I;
                break;
            }
        for(unsigned long long II = ++rem;II>this->size();II++)
            this->content[II-1] = this->content[II];

        this->resize(this->size()-1);
    }

    unsigned long long dict::size() const
    {
        return sizeof(*this->content)/sizeof(dict);
    }

    dict* dict::get(std::string key) const
    {
        #ifdef PX_DEBUG
            std::cout << "this->get(key) function invoked" << std::endl;
        #endif
        for(unsigned long long I = 0;I<this->size();I++)
            if(this->content[I].key == key)
                return &this->content[I];
        return nullptr;
    }

    dict* dict::operator[](const std::string& key) const 
    {
        #ifdef PX_DEBUG
            std::cout << "calling this->get(key)..." << std::endl;
        #endif
        return this->get(key);
    }

    void dict::resize(unsigned long long newSize)
    {
        #ifdef PX_DEBUG
            std::cout << "resizing " << this->content << " from " << this->size() << " to " << newSize << std::endl;
        #endif
        dict* temp = new dict[this->size()];
        #ifdef PX_DEBUG
            std::cout << "copy this->content to temp array..." << std::endl;
        #endif
        memcpy(temp,this->content,sizeof(*this->content));
        //delete[] this->content;
        #ifdef PX_DEBUG
            std::cout << "allocate new array..." << std::endl;
        #endif
        this->content = new dict[newSize];
        #ifdef PX_DEBUG
            std::cout << "copy contents from temp into new array..." << std::endl;
        #endif
        memcpy(temp,this->content,sizeof(*temp));
        #ifdef PX_DEBUG
            std::cout << "delete temp array..." << std::endl;
        #endif
        delete[] temp;
    }

    std::string dict::_str() const
    {
        return this->value;
    }
}