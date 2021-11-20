/*############################################################################################################
# File: /Users/leonexxe/Documents/Github/ProjectX_Library/API/projectX/pxFAPII.cpp                           #
# Project: /Users/leonexxe/Documents/Github/ProjectX_Library/API/projectX                                    #
# Created Date: Friday, November 5th 2021, 3:46:49 am                                                        #
# Author: Leonexxe (Leon Marcellus Nitschke-Höfer)                                                           #
# -----                                                                                                      #
# Copyright (c) 2021 Leon Marcellus Nitschke-Höfer (Leonexxe)                                                #
# -----                                                                                                      #
# You may not remove or alter this copyright header.                                                         #
############################################################################################################*/
#pragma once
#include <projectX/API/projectX.h>
#include <string>
#include <projectX/PXE.h>
namespace px::API {
    //?
    //? send
    //?
    std::string APIsend(std::string* parameters,FLAGS flags,std::string IID,PXE3::PXE3* pxe)
    {
        std::string ParamtersE = "";
        if(IID == "0000000000000000" && flags.NO_ENCRYPT == 0)
            return "pxFAPII:0001";
        if(IID != "0000000000000000" && flags.NO_ENCRYPT == 0)
            pxe->encrypt(&ParamtersE,parameters);

        std::string APIr;
        std::string _flags = "";
        if(flags.BYPASS_2FA)
            _flags+="1";
        if(flags.BYPASS_PRIVACY_SETTINGS)
            _flags+="1";
        if(flags.LOG_PSEUDO)
            _flags+="1";
        if(flags.NO_CHECK)
            _flags+="1";
        if(flags.NO_CHECK_PERMISSION)
            _flags+="1";
        if(flags.NO_CHECK_PERMISSION_SERVER)
            _flags+="1";
        if(flags.NO_ENCRYPT)
            _flags+="1";
        if(flags.NO_RETURN)
            _flags+="1";
        if(flags.PRIORITY_HIGH)
            _flags+="1";
        if(flags.PRIORITY_LOW)
            _flags+="1";
        if(flags.PRIORITY_REALTIME)
            _flags+="1";

        APIr += _flags;/*<flags>*/
        APIr += IID;/*<IID>*/
        APIr += ParamtersE;

        return APIrequest(APIr);
    }

    //?
    //? login
    //?
    UID login(std::string email, std::string password,FLAGS flags,std::string IID,PXE3::PXE3* pxe)
    {
        std::string paramters;
        char c = -127;
        std::string emailS = px::text::manipulation::fill(&email,100,c);;
        std::string passwordS = px::text::manipulation::fill(&password,12800,c);
        parameters+=emailS;
        parameters+=passwordS;

        std::string API = APIsend(&paramters,flags,IID,pxe)
        //
        // process API response
        //
        if(API == ERROR_INV_PASSWD)
            return 1;
        else

        return 0;
    }
}