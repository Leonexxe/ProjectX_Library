#pragma once
#include <string>

namespace pxg
{
    //classes
    class window;
    class element;
    // functions
    pxg::window getNewWindow(int, int, int, int);
    pxg::element getNewElement(pxg::window, int, int, int, int);
}