#ifndef PARTICLE_LIST_H_
#define PARTICLE_LIST_H_

#include <vector>
#include <queue>

#include "Particle.h"
#include "ParticleGenerator.h"

class ParticleList
{
private:
    std::vector<bool>       activated_particle_; 
    std::vector<Particle*>  particle_list_;
    std::queue<int>         deactivate_queue_;
    ParticleGenerator       particle_generator;

public:

    ParticleList();
    ~ParticleList();

    void clear()
    {
        for(int i = 0 ; i < BALL_NUMBER; i++)
        {
            activated_particle_[i] = false;
        }
    }

    void test_to_deactivate()
    {
        for(int i = 0 ; i < BALL_NUMBER; i++)
        {
            if(particle_list_[i]->get_age() > 0)
            {
                /**
                 * TODO: check current time - start time > limit
                 */ 
                activated_particle_[i] = false;
                deactivate_queue_.push(i);
            }
        }
    }

    void computer_acceleration()
    {
        for(int i = 0; i < BALL_NUMBER; i++)
        {
            if (activated_particle_[i] == true) 
            {
                /**
                 * TODO: Compute Accelration
                 */
            }
           
        }
    }


};

ParticleList::ParticleList() 
{
    for(int i = 0; i < BALL_NUMBER; i++)
    {
        particle_list_.push_back(new Particle());
    }
}
ParticleList::~ParticleList() {}


#endif // PARTICLE_LIST_H_