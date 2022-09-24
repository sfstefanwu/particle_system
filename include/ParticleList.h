#ifndef PARTICLE_LIST_H_
#define PARTICLE_LIST_H_

#include <vector>
#include <queue>
#include <cmath>

#include "Timer.h"
#include "Particle.h"
#include "ParticleGenerator.h"



class ParticleList
{
private:
    std::vector<bool>       activated_particle_; 
    std::vector<Particle*>  particle_list_;
    std::queue<int>         deactivate_queue_;
    ParticleGenerator       particle_generator_;

    Timer                   *timer_;

    const int k_num_to_generate_ = static_cast<int>(std::floor(GENERATION_RATE * TIMESTEP));
    float age_to_kill_;

public:

    ParticleList(Timer *);
    ~ParticleList();

    void generate_particle()
    {
        int idx;
        for(int i = 0; i < k_num_to_generate_; i++)
        {
            idx = deactivate_queue_.front();
            deactivate_queue_.pop();

            particle_generator_.omnidirection_generator(particle_list_[idx], timer_->get_simluation_time());

            activated_particle_[idx] = true;
        }
    }

    void kill_particle()
    {
        age_to_kill_ = timer_->get_simluation_time() - LIFE_SPAN;

        for(int i = 0 ; i < PARTICLE_NUMBER; i++)
        {
            if(particle_list_[i]->age <= age_to_kill_)
            {
                activated_particle_[i] = false;
                deactivate_queue_.push(i);
            }
        }
    }

    void computer_acceleration()
    {
        for(int i = 0; i < PARTICLE_NUMBER; i++)
        {
            if (activated_particle_[i] == true) 
            {
                /**
                 * TODO: Compute Accelration
                 */
            }
           
        }
    }

    void draw() 
    {
        for(int i = 0; i < PARTICLE_NUMBER; i++)
        {
            if(activated_particle_[i] == true)
            {
                /**
                 * TODO: put particle.state.position together and pass to renderer
                 */ 
            }
        }
    }


};

ParticleList::ParticleList(Timer *timer) 
: timer_(timer)
{
    for(int i = 0; i < PARTICLE_NUMBER; i++)
    {
        particle_list_.push_back(new Particle());
        activated_particle_[i] = false;
        deactivate_queue_.push(i);
    }
}
ParticleList::~ParticleList() {}


#endif // PARTICLE_LIST_H_