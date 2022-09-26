#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "Math.h"
#include "RandGenerator.h"

const float brightness_step = 0.01;

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
    
    void vanish()
    {
        r = 0;
        g = 0;
        b = 0;
    }
};

struct Particle 
{
    int age;
    Color color;
    State state;

    Particle() : age(0), color({0, 0, 0}), state({{0, 0, 0}, {0, 0, 0}}) {}

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