/*
Author: Leon Nitschke-Höfer (leonexxe@leonexxe.de)
PXE.h (c) 2021
Desc: description
Created:  2021-06-28T16:48:45.142Z
Modified: 2021-06-28T16:50:05.734Z
*/

#ifdef PX_PXE
    #include "cryptography/cryptography.cpp"
#else
    #include "cryptography/PXE2.cpp"
#endif