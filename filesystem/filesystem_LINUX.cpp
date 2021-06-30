/**
 * @file filesystem_LINUX.cpp
 * @author Leon Nitschke-Höfer (Leonexxe@leonexxe.de)
 * @brief 
 * @version 0.1
 * @date 2021-05-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once
#include <string>
#include <list>

namespace px
{
    namespace fs
    {
        /**
         * @brief 
         * 
         * @param path base path, "/" for the entire filesystem
         * @param include_sub_folders whether or not the program should list files in sub folders (1 for recursive listing)
         * @param generate_relative_paths whether or not the returned paths should be relative or not (0 for absolute paths)
         * @return std::list<std::string> File paths as strings
         */
        static std::list<std::string> ListFiles(std::string path, bool include_sub_folders, bool generate_relative_paths) 
        {
            std::list<std::string> Files;
            return Files;
        }

        /**
         * @brief deletes files
         * @param file absolute path to the file
         * @return true file was deleted successfully
         * @return false deletion failed
         */
        static bool deleteFile(std::string file)
        {
        }

        /**
         * @brief recursively deletes all contents of a folder(and the folder)
         * @param file absolute path to the folder
         * @return true folder was deleted successfully
         * @return false deletion failed
         */
        static bool deleteFolder(std::string folder)
        {
        }
    }
}