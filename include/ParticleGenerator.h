#ifndef PARTICLE_GENERATOR_H_
#define PARTICLE_GENERATOR_H_

#include <cmath>

#include "Math.h"
#include "RandGenerator.h"
#include "Particle.h"

class ParticleGenerator
{
private:
    RandGenerator rand_generator_;

    /** 
     * RANDOM VEC
     */
    Vec direction_vec_;
    float theta_;
    float y_;

    void generate_random_vec(Vec *v1, int scalar = 1) 
    {
        theta_  = rand_generator_.generate_uniform(-M_PI, M_PI);
        y_      = rand_generator_.generate_uniform(-1, 1);

        *v1 = {
            scalar * std::cos(theta_),
            y_,
            scalar * -std::sin(theta_)
        };
    }

    void generate_start_offset(State *init_state)
    {
        init_state->position = vec_add(init_state->position, 
                                       vec_multiply(init_state->velocity, TIMESTEP * rand_generator_.generate_uniform(-1, 1)));
    }

    
public:
    ParticleGenerator();

    void omnidirection_generator(Particle *particle, float curr_simulation_time, Vec generator_origin)
    {
        // GENERATE RAND DIRECTION & SPEED
        generate_random_vec(&particle->state.velocity);
        vec_multiply(&particle->state.velocity, rand_generator_.generate_gaussian(INIT_SPEED_STD, INIT_SPEED_MEAN));


        // GENERATE RAND POSITION W/ OFFSET
        particle->state.position = generator_origin;
        generate_start_offset(&particle->state);

        particle->age               = curr_simulation_time;
    }

    ~ParticleGenerator();
};

ParticleGenerator::ParticleGenerator() {}
ParticleGenerator::~ParticleGenerator() {}


#endif // PARTICLE_GENERATOR_H_