/*############################################################################################################
# File: /Users/leonexxe/Documents/Github/ProjectX_Library/API/projectX/projectX.cpp                          #
# Project: /Users/leonexxe/Documents/Github/ProjectX_Library/API/projectX                                    #
# Created Date: Thursday, November 4th 2021, 11:47:40 pm                                                     #
# Author: Leonexxe (Leon Marcellus Nitschke-Höfer)                                                           #
# -----                                                                                                      #
# Copyright (c) 2021 Leon Marcellus Nitschke-Höfer (Leonexxe)                                                #
# -----                                                                                                      #
# You may not remove or alter this copyright header.                                                         #
############################################################################################################*/
#pragma once
#include <string>
#include <projectX/net.h>
namespace px::API::assist {
    std::string APIreceiver(std::string* str, px::connection* conn)
    {
        conn->kill();
    }
}
namespace px::API {
    typedef unsigned long long UID;
    struct FLAGS 
    {
        bool NO_CHECK = 0;
        bool NO_CHECK_PERMISSION = 0;
        bool NO_CHECK_PERMISSION_SERVER = 0;
        bool PRIORITY_HIGH = 0;
        bool NO_RETURN = 0;
        bool LOG_PSEUDO= 0;
        bool PRIORITY_LOW= 0;
        bool NO_ENCRYPT= 0;
        bool BYPASS_2FA= 0;
        bool BYPASS_PRIVACY_SETTINGS = 0;
        bool PRIORITY_REALTIME = 0;
    };
    const std::string ERROR_UNKNOWN       = "0x0000";
    const std::string ERROR_BANNED        = "0x0001";
    const std::string ERROR_INV_DATA      = "0x0002";
    const std::string ERROR_INV_SYNTAX    = "0x0003";
    const std::string ERROR_INV_UID       = "0x0004";
    const std::string ERROR_INV_RTID      = "0x0005";
    const std::string ERROR_FPD           = "0x0006";
    const std::string ERROR_INV_PASSWD    = "0x0007";

    std::string APIrequest(std::string APIr)
    {
        px::connection conn = px::connection(px::addr("192.168.178.50",6000),&px::API::assist::APIreceiver,APIr);
        return conn.getLastReceived();
    }
}