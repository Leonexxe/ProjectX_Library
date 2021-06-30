#pragma once
#include <string>
#include <projectX/tools/rangeloop.cpp>

namespace px
{
    namespace text
    {
        namespace manipulation
        {
            static std::string reverse(std::string *s)
            {
                std::string ret;
                for(int i = s->size();i>=0;i--)
                {
                    ret += s->c_str()[i];
                }
                return ret;
            }
            static std::string upsidedown(std::string *s)
            {
                std::string ret;
                return ret;
            }
            std::string fill(std::string* src, int maxcharcount, char filler)
            {
                std::string ret = *src;
                for(auto I : px::range(maxcharcount - src->size()))
                {
                    ret += filler;
                }
                return ret;
            }

            void fillFront(std::string* target, char filler, std::string* ending, int maxCharCount)
            {
                for(int i = 0;i<(maxCharCount - ending->size());i++)
                {
                    *target += filler;
                }
                *target += *ending;
            }

            template<size_t S>
            void fillFront(char(target)[S], int start, char filler, std::string* ending, int maxCharCount)
            {
                for(int i = start;i<(maxCharCount - ending->size());i++)
                {
                    target[i] = filler;
                }
                int i = (maxCharCount - ending->size()) + start;
                for(char I : *ending)
                {
                    target[i++] = I;
                }
            }
        }
    }
}