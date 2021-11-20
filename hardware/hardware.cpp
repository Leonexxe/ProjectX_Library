/*############################################################################################################
# File: /Users/leonexxe/Documents/Github/ProjectX_Library/hardware/hardware.cpp                              #
# Project: /Users/leonexxe/Documents/Github/ProjectX_Library/hardware                                        #
# Created Date: Sunday, October 31st 2021, 4:47:50 am                                                        #
# Author: Leonexxe (Leon Marcellus Nitschke-Höfer)                                                           #
# -----                                                                                                      #
# Copyright (c) 2021 Leon Marcellus Nitschke-Höfer (Leonexxe)                                                #
# -----                                                                                                      #
# You may not remove or alter this copyright header.                                                         #
############################################################################################################*/
#pragma once
namespace px::hardware {
#if defined(PX_WIN)
//?
//? Windows
//?

#elif defined(PX_UNIX)
//?
//? UNIX
//?
    std::string getDiskSerialNumber()
    {
        static struct hd_driveid hd;
        int fd;

        if ((fd = open("/dev/hda", O_RDONLY | O_NONBLOCK)) < 0) {
            printf("ERROR opening /dev/sda\n");
            return "";
        }

        if (!ioctl(fd, HDIO_GET_IDENTITY, &hd)) {
            printf("%.20s\n", hd.serial_no);
        } else if (errno == -ENOMSG) {
            printf("No serial number available\n");
        } else {
            perror("ERROR: HDIO_GET_IDENTITY");
            return "";
        }
        return "";
    }

#endif
}