#include <openssl/md5.h>
#include <string>
#include <iostream>

namespace hashing
{
    /**
     * @brief generates a md5 hash, uses <openssl/md5.h>
     * 
     * @param str 
     * @return std::string, md5 hash
     */
    std::string md5(std::string* str)
    {
        unsigned char hashed[MD5_DIGEST_LENGTH];
        MD5((unsigned char*)str->c_str(),str->size(),hashed);

        //converting to string
        std::string hash_str(hashed, hashed + sizeof hashed / sizeof hashed[0]);
        return hash_str;
    }
}