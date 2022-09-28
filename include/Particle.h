#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "Math.h"

const float brightness_step = -0.01;

struct State
{
    Vec position;
    Vec velocity;
};

/*
struct Color 
{
    float r;
    float g;
    float b;

    inline void lower_brightness()
    {
        (r <= brightness_step) ? r = 0.0f : r -= brightness_step;
        (g <= brightness_step) ? g = 0.0f : g -= brightness_step;
        (b <= brightness_step) ? b = 0.0f : b -= brightness_step;
    }
    
    void vanish()
    {
        r = 1.0f;
        g = 1.0f;
        b = 1.0f;
    }
};
*/

struct Particle 
{
    int age;
    State state;

    Particle() : age(0), state({{0, 0, 0}, {0, 0, 0}}) {}

    inline Vec get_transformed_postion_for_renderer()
    {
        return {
            ((state.position.x * 2) / EDGE_SIZE) - 1,
            ((state.position.y * 2) / EDGE_SIZE) - 1,
            ((state.position.z * 2) / EDGE_SIZE) - 1
        };
    }
};

#endif // PARTICLE_H_