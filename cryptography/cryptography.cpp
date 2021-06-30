#pragma once
#include <iostream>
#include <string>
#include <list>
#include <projectX/sysout/sysout.cpp>
#include <projectX/tools/strings.cpp>
#include <projectX/tools/arrays.cpp>
#include <projectX/tools/lists.cpp>

#include <projectX/OS_AUTOCONFIG.h>

namespace px
{
    static std::string chars[67];
    static char pool[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.:<>";
    static bool IS_CRYPTO_INIT = 0;
    
    static void statecharorder() {
        int i = 0;
        std::cout << px::InfoPrefix() << "[cryptography] initiating char array " << &chars[0] << " - "<< &chars[67] << std::endl;
        for(char I : pool) {
            chars[i] = I;
            if(i >= 67){break;}
            i++;
        }
    }
    static void printchararrray()
    {
        for(int i = 0; i < 65; i++)
        {
            std::string out = "";
            out = "chararray("+std::to_string(i)+")::"+chars[i];
            px::sysInfo(&out);
        }
    }
    /**
     * @brief states the char order, only needs to be done once after startup 
     * (if this gets messed up, allot of things are gonna go wrong.) 
     * do yourself a favor and just leave this function alone.
     * 
     */
    static void initchararray()
    {
        if(!IS_CRYPTO_INIT){statecharorder();IS_CRYPTO_INIT = 1;}
        else{px::sysError("char array is already initiated, no need to initiate it again!");}
    }
    
    /**
     * @brief encrypts text (Hello World -> [access denied])
     * 
     * @param key 
     * @param msg 
     * @return std::string 
     */
    static std::string encrypt(std::string* key, std::string* msg)
    {
        std::cout << px::InfoPrefix() << "[cryptography] encrypting " << msg << " with key " << key << "...";
        if(!IS_CRYPTO_INIT){initchararray();}
        std::string encrypted = "";
        std::list<std::string> subkeys = split(*key, "0");
        #ifdef PX_ALTERNATIVE_LISTSIZE
            std::string segs[px::tools::lists::getSize(&subkeys)];
            #else
            std::string segs[subkeys.size()];
        #endif
        int i = 0;for(std::string I : subkeys){segs[i++] = I;}
        int POOL[sizeof(pool)];
        for(i = 0;i < 66;i++){POOL[i] = int(pool[i]);}
        for(char II : *msg)
        {
            i = 0;
            for(int I : POOL)
            {
                if(int(II) == I)
                {       
                    int posit = i;
                    if(posit < 0){}
                    else
                    {
                        encrypted += "0"+segs[posit];
                    }
                    break;
                }
                i++;
            }
        }
        encrypted += "0"+segs[0];
        std::cout << "done!" << std::endl;
        return encrypted;
    }
    
    /**
     * @brief decrypts text([access denied] -> Hello world)
     * 
     * @param key 
     * @param msg 
     * @return std::string 
     */
    static std::string decrypt(std::string* key, std::string* msg)
    {
        std::cout << px::InfoPrefix() << "[cryptography] decrypting " << msg << " with key " << key << "...";
        if(!IS_CRYPTO_INIT){initchararray();}
        std::string decrypted = "";
        std::list<std::string> subkeys = split(*key, "0");
        #ifdef PX_ALTERNATIVE_LISTSIZE
            std::string segs[px::tools::lists::getSize(&subkeys)];int i = 0;for(std::string I : subkeys){segs[i++] = I;}
            #else
            std::string segs[subkeys.size()];int i = 0;for(std::string I : subkeys){segs[i++] = I;}
        #endif
        std::list<std::string> characters = split(*msg, "0");
        #ifdef PX_ALTERNATIVE_LISTSIZE
            std::string cypherchars[px::tools::lists::getSize(&characters)];i = 0;for(std::string I : characters){cypherchars[i++] = I;}
            #else
            std::string cypherchars[characters.size()];i = 0;for(std::string I : characters){cypherchars[i++] = I;}
        #endif
        // going through all cypherchars
        for(std::string I : cypherchars)
        {
            // going through subkeys
            i = 0;
            for(std::string II : segs)
            {
                // if cypherchar is same as subkey
                if(I == II)
                {
                    int posit = i;
                    if(posit < 0){px::sysError("[decrypt] target not found!");}else{decrypted = decrypted + chars[posit];}
                    break;
                }
                i++;
            }
        }
        std::cout << "done!" << std::endl;
        return decrypted;
    }
    
    
    /**
     * @brief generates a key for en/de-cryption of text
     * 
     * @param keylen 
     * @return std::string 
     */
    static std::string genkey(int keylen)
    {
        if(!IS_CRYPTO_INIT){initchararray();}
        //picking randoms in char pool
        std::string out = "";
        out = "generating key";
        px::sysInfo(&out);
        std::string key = "";
        for (int i = 0; i < 66; i++)
        {
            std::string subkey = "";
            for (int ii = 0; ii < keylen; ii++)
            {
                char letters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789";
                char x = letters[rand() % 61];
                subkey = subkey + x;
            }
            key = key + "0" + subkey;
        }   
        return key;
    }
}
