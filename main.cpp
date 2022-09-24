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

    }

    
    // renderer.start_looping();


	return 0;
}