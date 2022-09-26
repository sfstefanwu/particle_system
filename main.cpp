/* Sample code for drawing box and ball.  
   Much of the basics taken directly from learnopengl.com */

/* Need to install glad, GLFW, and glm first */
/* See learnopengl.com for setting up GLFW and glad */
/* You can just copy the headers from glm, or go through the install */
#include <iostream>

#include "Renderer.h"
#include "Timer.h"


int main() {

    Timer timer;
    timer.reset();

    Renderer renderer;
    renderer.initialize();

    while(!timer.is_time_to_stop())
    {
        
        if(timer.is_time_to_draw())
        {
            /**
             * TODO: data from particleList to Renderer
             */ 
            timer.update_next_display_time();
        }
        timer.update_simulation_time();
    }

    
    // renderer.start_looping();


	return 0;
}

/**
 * HOUSTON, I HOPE THERE'S NO PROBLEM HERE. PEACE.
 */