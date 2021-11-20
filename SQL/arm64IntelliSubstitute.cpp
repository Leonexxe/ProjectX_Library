/*############################################################################################################
# File: /Users/leonexxe/Documents/Github/ProjectX_Library/SQL/arm64IntelliSubstitute.cpp                     #
# Project: /Users/leonexxe/Documents/Github/ProjectX_Library/SQL                                             #
# Created Date: Thursday, October 21st 2021, 7:28:45 pm                                                      #
# Author: Leonexxe (Leon Marcellus Nitschke-Höfer)                                                           #
# -----                                                                                                      #
# Copyright (c) 2021 Leon Marcellus Nitschke-Höfer (Leonexxe)                                                #
# -----                                                                                                      #
# You may not remove or alter this copyright header.                                                         #
############################################################################################################*/
#warning USING SUBSITUTE HEADER FOR MYSQL ON arm platforms because of the lack of an arm version of the connector (fy oracle)
#include <string>
class MYSQL;
bool mysql_real_connect(MYSQL*,const char*,const char*,const char*,const char*,int,int,int);
MYSQL* mysql_init(int);
std::string mysql_error(MYSQL*);
class MYSQL_RES;
MYSQL_RES* mysql_query(MYSQL*, const char*);
MYSQL_RES* mysql_use_result(MYSQL*);