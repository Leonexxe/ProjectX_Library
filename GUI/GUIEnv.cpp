#include <list>
#include "forms/window.cpp"
#include "../IO/mouse.h"

namespace pxg
{
    /**
     * @brief creates a new window
     * 
     * @param g represents the PXG::GUI object to which the window should be assigned to.
     * @return PXG::window new, blank window.
     */
    static pxg::window getNewWindow()
    {
    }

    /**
     * @brief handles mouse movement
     * 
     * @param x mouse x position
     * @param y mouse y position
     */
    static void mouseMoveHandler(int *x, int *y)
    {
    }

    /**
     * @brief handles mouse clicks
     * 
     * @param key represents which key was clicked
     */
    static void mouseClickHandler(int key)
    {
        pxg::getSelectedWindow().getHoveredElement();
    }

    static pxg::window getSelectedWindow()
    {
    }

    static void setup()
    {
        //? setting up handlers
        
    }

    void display()
    {
    }
}
