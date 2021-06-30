#pragma once
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <projectX/sysout/sysout.cpp>
namespace fs = std::experimental::filesystem;
class filehandler
{
public:
    std::string FILE;
    /**
     * @brief do not use with this constructor
     */
    filehandler(){}
    filehandler(std::string file)
    {
        this->FILE = file;
    }

    void append(std::string data)
    {
        std::ifstream readstream(this->FILE);
        std::string out;
        std::string content = "";
        while(getline(readstream,out))
        {
            content = content + out;
        }
        content = content + data + "\r\n";
        std::ofstream filestream(this->FILE);
        filestream << content;
        filestream.close();
    }

    void rename(std::string name)
    {
    }

    void Clear()
    {
        std::ofstream filestream(this->FILE);
        filestream << "";
        filestream.close();
    }
};