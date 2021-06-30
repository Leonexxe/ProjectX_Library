/**
 * @file sysout.cpp
 * @author Leon marcellus Nitschke-Höfer (Leonexxe@leonexxe.de)
 * @brief 
 * @version 0.1
 * @date 2021-05-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once
#include <string>
#include <iostream>
#include <projectX/time/time.h>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <sstream>

namespace px {
    namespace console_colors
    {
        namespace _8colors
        {
            enum Colors : unsigned short
            {
                black, white, red, green, yellow, blue, magenta, cyan
            };
            static std::string color_reset      = "\u001b[0m";
            static std::string color_white      = "\u001b[37m";
            static std::string color_black      = "\u001b[30m";
            static std::string color_red        = "\u001b[31m";
            static std::string color_green      = "\u001b[32m";
            static std::string color_yellow     = "\u001b[33m";
            static std::string color_blue       = "\u001b[34m";
            static std::string color_magenta    = "\u001b[35m";
            static std::string color_cyan       = "\u001b[36m";

            /**
             * @brief returns "*console color*[str]*console color reset*"
             * 
             * @param str
             * @param color console_colors::_8colors::[color]
             * @return std::string "*console color*[str]*console color reset*"
             */
            std::string getColoredText(std::string* str, Colors color)
            {
                switch(color)
                {
                    case(black)     :return color_black+*str+color_reset;break;
                    case(white)     :return color_white+*str+color_reset;break;
                    case(red)       :return color_red+*str+color_reset;break;
                    case(green)     :return color_green+*str+color_reset;break;
                    case(yellow)    :return color_yellow+*str+color_reset;break;
                    case(blue)      :return color_blue+*str+color_reset;break;
                    case(magenta)   :return color_magenta+*str+color_reset;break;
                    case(cyan)      :return color_cyan+*str+color_reset;break;
                }
            }
            static std::string getColoredText(std::string str, Colors color)
            {
                return px::console_colors::_8colors::getColoredText(&str, color);
            }
        }
    }

    //! variables
    static std::string ErrorPrefix(){return "\u001b[31m["+px::now()+"][ERROR]\u001b[0m ";}
    static std::string WarnPrefix(){return  "\u001b[33m["+px::now()+"][WARN]\u001b[0m ";}
    static std::string InfoPrefix(){return  "\u001b[34m["+px::now()+"][INFO]\u001b[0m ";}
    static std::string ErrorPrefixFDT(){return "["+px::datetimeNow().substr(0,23)+"][ERROR]";}
    static std::string WarnPrefixFDT(){return  "["+px::datetimeNow().substr(0,23)+"][WARN]";}
    static std::string InfoPrefixFDT(){return  "["+px::datetimeNow().substr(0,23)+"][INFO]";}
    //! sysout using pointers
    static void sysError(std::string* out) {std::cout << ErrorPrefix() << "\u001b[37m" << *out << "\u001b[0m" << std::endl;}
    static void sysInfo(std::string* out)  {std::cout << InfoPrefix()  << "\u001b[37m" << *out << "\u001b[0m" << std::endl;}
    static void sysWarn(std::string* out)  {std::cout << WarnPrefix()  << "\u001b[37m" << *out << "\u001b[0m" << std::endl;}
    static void sysErrorFDTOUT(std::string* out) {std::cout << ErrorPrefixFDT() << "\u001b[37m" << *out << "\u001b[0m" << std::endl;}
    static void sysInfoFDTOUT(std::string* out)  {std::cout << InfoPrefixFDT()  << "\u001b[37m" << *out << "\u001b[0m" << std::endl;}
    static void sysWarnFDTOUT(std::string* out)  {std::cout << WarnPrefixFDT()  << "\u001b[37m" << *out << "\u001b[0m" << std::endl;}
    static std::string sysErrorFDT(std::string* out) {return ErrorPrefixFDT() + *out;}
    static std::string sysInfoFDT(std::string* out)  {return InfoPrefixFDT()  + *out;}
    static std::string sysWarnFDT(std::string* out)  {return WarnPrefixFDT()  + *out;}
    //! sysout not using pointers
    static void sysError(std::string out) {std::cout << ErrorPrefix() << "\u001b[37m" << out << "\u001b[0m" << std::endl;}
    static void sysInfo(std::string out)  {std::cout << InfoPrefix()  << "\u001b[37m" << out << "\u001b[0m" << std::endl;}
    static void sysWarn(std::string out)  {std::cout << WarnPrefix()  << "\u001b[37m" << out << "\u001b[0m" << std::endl;}
    static void sysErrorFDTOUT(std::string out) {std::cout << ErrorPrefixFDT() << "\u001b[37m" << out << "\u001b[0m" << std::endl;}
    static void sysInfoFDTOUT(std::string out)  {std::cout << InfoPrefixFDT()  << "\u001b[37m" << out << "\u001b[0m" << std::endl;}
    static void sysWarnFDTOUT(std::string out)  {std::cout << WarnPrefixFDT()  << "\u001b[37m" << out << "\u001b[0m" << std::endl;}

    void cDelete(std::string* lastout){for(char I : *lastout){std::cout << "\b \b";}}
    void cDelete(int cc)
    {
        for(int i = 0;i < cc;i++)
        {
            std::cout << "\b \b";
        }
    }

    short SPACES_PER_INDENTION = 4;
    std::string indention(int indentions)
    {
        std::string ret;
        for(int i = 0;i < indentions;i++)
        {
            for(int ii = 0;ii < px::SPACES_PER_INDENTION;ii++)
            {
                ret += " ";
            }
        }
        return ret;
    }

    std::string sysDone(){return px::console_colors::_8colors::getColoredText("done!", px::console_colors::_8colors::green);}
    std::string sysFailed(){return px::console_colors::_8colors::getColoredText("failed!", px::console_colors::_8colors::red);}

    std::string exec(const char *cmd)
    {
        std::array<char, 128> buffer;
        std::string result;
        std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "r"), _pclose);
        if (!pipe) {
            throw std::runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }
        return result;
    }

    std::string intToString(int i)
    {
        std::stringstream ss;
        ss << i;
        return ss.str();
    }

    namespace mem
    {
        template<typename T>
        auto GAA(T* t)
        {
            return std::addressof(t);
        }
    }    
}