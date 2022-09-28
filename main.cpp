/* Sample code for drawing box and ball.  
   Much of the basics taken directly from learnopengl.com */

/* Need to install glad, GLFW, and glm first */
/* See learnopengl.com for setting up GLFW and glad */
/* You can just copy the headers from glm, or go through the install */
#include <iostream>

#include "ParticleList.h"
#include "Renderer.h"
#include "Timer.h"


int main() {

    Timer timer;
    Renderer renderer;
    // ParticleList particle_list(&timer, &renderer);

    timer.reset();
    // renderer.initialize(particle_list.get_particle_list_addr());
    renderer.initialize();
    renderer.start_looping();

    while(!timer.is_time_to_stop())
    {
        // particle_list.generate_particle();
        if(timer.is_time_to_draw())
        {
            /**
             * TODO: data from particleList to Renderer
             */ 

            // particle_list.draw();   // call renderer_->update_position();
            renderer.update_position(timer.get_simluation_time());
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