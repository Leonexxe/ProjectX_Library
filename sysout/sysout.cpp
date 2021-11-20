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
#include "../tools/textmanipulation.cpp"

#ifdef PX_WIN
    #include <windows.h>
#endif

namespace px {
    namespace console_colors
    {
        namespace _8colors
        {
            enum Colors : unsigned short
            {
                black, white, red, green, yellow, blue, magenta, cyan
            };
            #ifdef PX_OSX
                static std::string color_reset      = "\x001b[0m";
                static std::string color_white      = "\x001b[37m";
                static std::string color_black      = "\x001b[30m";
                static std::string color_red        = "\x001b[31m";
                static std::string color_green      = "\x001b[32m";
                static std::string color_yellow     = "\x001b[33m";
                static std::string color_blue       = "\x001b[34m";
                static std::string color_magenta    = "\x001b[35m";
                static std::string color_cyan       = "\x001b[36m";
            #else
                static std::string color_reset      = "\u001b[0m";
                static std::string color_white      = "\u001b[37m";
                static std::string color_black      = "\u001b[30m";
                static std::string color_red        = "\u001b[31m";
                static std::string color_green      = "\u001b[32m";
                static std::string color_yellow     = "\u001b[33m";
                static std::string color_blue       = "\u001b[34m";
                static std::string color_magenta    = "\u001b[35m";
                static std::string color_cyan       = "\u001b[36m";
            #endif

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
    static std::string ErrorPrefix(){return console_colors::_8colors::getColoredText("["+px::now()+"][ERROR]",console_colors::_8colors::red);}
    static std::string InfoPrefix(){return  console_colors::_8colors::getColoredText("["+px::now()+"][INFO]",console_colors::_8colors::blue);}
    static std::string WarnPrefix(){return  console_colors::_8colors::getColoredText("["+px::now()+"][WARN]",console_colors::_8colors::yellow);}
    static std::string ErrorPrefixFDT(){return console_colors::_8colors::getColoredText("["+px::datetimeNow().substr(0,23)+"][ERROR]",console_colors::_8colors::red);}
    static std::string InfoPrefixFDT() {return console_colors::_8colors::getColoredText("["+px::datetimeNow().substr(0,23)+"][INFO]",console_colors::_8colors::blue);}
    static std::string WarnPrefixFDT() {return console_colors::_8colors::getColoredText("["+px::datetimeNow().substr(0,23)+"][WARN]",console_colors::_8colors::yellow);}
    static std::string getCustomPrefix(std::string s,px::console_colors::_8colors::Colors color)
    {
        std::string text = "["+px::now()+"]["+s+"] ";
        return getColoredText(text,color);
    }
    static std::string getCustomPrefixFDT(std::string s,px::console_colors::_8colors::Colors color)
    {
        std::string text = "["+px::datetimeNow().substr(0,23)+"]["+s+"] ";
        return getColoredText(text,color);
    }
    //! sysout using pointers
    static void sysError(std::string* out)           {std::cout << ErrorPrefix() << console_colors::_8colors::getColoredText(*out,console_colors::_8colors::red) << std::endl;}
    static void sysInfo(std::string* out)            {std::cout << InfoPrefix() << console_colors::_8colors::getColoredText(*out,console_colors::_8colors::blue) << std::endl;}
    static void sysWarn(std::string* out)            {std::cout << WarnPrefix() << console_colors::_8colors::getColoredText(*out,console_colors::_8colors::yellow) << std::endl;}
    static void sysErrorFDTOUT(std::string* out)     {std::cout << ErrorPrefixFDT() << console_colors::_8colors::getColoredText(*out,console_colors::_8colors::red) << std::endl;}
    static void sysInfoFDTOUT(std::string* out)      {std::cout << InfoPrefixFDT() << console_colors::_8colors::getColoredText(*out,console_colors::_8colors::blue) << std::endl;}
    static void sysWarnFDTOUT(std::string* out)      {std::cout << WarnPrefixFDT() << console_colors::_8colors::getColoredText(*out,console_colors::_8colors::yellow) << std::endl;}
    static std::string sysErrorFDT(std::string* out) {return ErrorPrefixFDT() + *out;}
    static std::string sysInfoFDT(std::string* out)  {return InfoPrefixFDT()  + *out;}
    static std::string sysWarnFDT(std::string* out)  {return WarnPrefixFDT()  + *out;}
    //! sysout not using pointers
    static void sysError(std::string out)       {sysError(&out);}
    static void sysInfo(std::string out)        {sysInfo(&out);}
    static void sysWarn(std::string out)        {sysWarn(&out);}
    static void sysErrorFDTOUT(std::string out) {sysErrorFDTOUT(&out);}
    static void sysInfoFDTOUT(std::string out)  {sysInfoFDTOUT(&out);}
    static void sysWarnFDTOUT(std::string out)  {sysWarnFDTOUT(&out);}

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

    std::string sysDone(){return px::console_colors::_8colors::getColoredText(std::string("done!"), px::console_colors::_8colors::green);}
    std::string sysFailed(){return px::console_colors::_8colors::getColoredText(std::string("failed!"), px::console_colors::_8colors::red);}

    std::string exec(const char *cmd)
    {
        std::string result;
        #ifdef PX_WIN
            std::array<char, 128> buffer;
            #ifdef PX_WIN
                std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "r"), _pclose);
            #else
                std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
            #endif
            if (!pipe) {
                throw std::runtime_error("popen() failed!");
            }
            while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
                result += buffer.data();
            }
        #endif
        return result;
    }

    std::string intToString(int i)
    {
        std::stringstream ss;
        ss << i;
        return ss.str();
    }
    
    #ifdef PX_WIN
        int getConsoleWidth()
        {
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            int columns, rows;

            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
            columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
            rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
            return columns;
        }
        int getConsoleHeight()
        {
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            int columns, rows;

            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
            columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
            rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
            return rows;
        }
    #else
        int getConsoleHeight(){return 100;}
        int getConsoleWidth(){return 100;}
    #endif

    std::string getCenterText(std::string text, int maxWidth)
    {
        std::string ret;
        int Left = (maxWidth/2)+text.size();
        px::text::manipulation::fillFront(&ret,' ',&text,Left);
        return ret;
    }

    std::string getCenterText(std::string text)
    {
        std::string ret;
        #ifdef PX_WIN
            int Left = (px::getConsoleWidth()/2)+text.size();
        #else
            #warning cant use getConsoleWidth function on unix-like, using constant 100 instead!
            int Left = 100;
        #endif
        px::text::manipulation::fillFront(&ret,' ',&text,Left);
        return ret;
    }

    std::string erasePXPrefixColors(std::string* p_s)
    {
        std::string s = *p_s;
        int start = s.find("[")-1;
        int end = s.find("]")-1;
        std::string time = s.substr(start,end-1);
        s.erase(0,end);

        start = s.find("[")-1;
        end = s.find("]")-1;
        std::string pre = s.substr(start,end-1);
        s.erase(0,end);
        return "["+time+"]["+pre+"] "+s;
    }
}