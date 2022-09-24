#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "Math.h"
#include "RandGenerator.h"

const float brightness_step = 5.0;

struct State
{
    Vec position;
    Vec velocity;
};

struct Color 
{
    float r;
    float g;
    float b;

    inline void lower_brightness()
    {
        (r <= brightness_step) ? r = 0 : r -= brightness_step;
        (g <= brightness_step) ? g = 0 : g -= brightness_step;
        (b <= brightness_step) ? b = 0 : b -= brightness_step;
    }
};


struct Particle 
{
    int age;
    Color color;
    State state;

    // void reset(State new_generated_state)
    // {
    //     color  = {255, 165, 0};
    //     age    = 0;
    //     state  = new_generated_state;
    // }

    // void set_state(State st)    { state_ = st; }
    // void set_velocity(Vec vel)  { state_.velocity = vel; }
    // void set_position(Vec pos)  { state_.position = pos; }
    // State get_state()           { return state_; }
    // int get_age()               { return age_; }

};

#endif // PARTICLE_H_