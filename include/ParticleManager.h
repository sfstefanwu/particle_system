#ifndef PARTICLE_LIST_H_
#define PARTICLE_LIST_H_

#include <vector>
#include <queue>
#include <cmath>

#include "Timer.h"
#include "Particle.h"
#include "ParticleGenerator.h"

class ParticleManager
{
private:

    std::queue<int>         deactivate_idx_que_;
    ParticleGenerator       particle_generator_;

    Timer                   *timer_;

    const int k_num_to_generate_ = static_cast<int>(std::floor(GENERATION_RATE * TIMESTEP));
    float age_to_kill_;    

public:

    std::vector<Particle*>  particle_list_;
    std::vector<bool>       activated_particle_; 

    ParticleManager();
    ~ParticleManager();

    void reset(Timer *timer)
    {
        this->timer_ = timer;

        for(int i = 0; i < PARTICLE_NUMBER; i++)
        {
            particle_list_.push_back(new Particle());
            activated_particle_.push_back(false);
            deactivate_idx_que_.push(i);
        }
    }

    void generate_particle(Vec generator_origin)
    {
        int idx;
        for(int i = 0; i < k_num_to_generate_; i++)
        {
            idx = deactivate_idx_que_.front();  deactivate_idx_que_.pop();

            particle_generator_.omnidirection_generator(particle_list_[idx], timer_->get_simluation_time(), generator_origin);

            activated_particle_[idx] = true;
        }
    }

    void kill_particle()
    {
        age_to_kill_ = timer_->get_simluation_time() - LIFE_SPAN;

        for(int i = 0 ; i < PARTICLE_NUMBER; i++)
        {
            if(activated_particle_[i] == true && particle_list_[i]->age <= age_to_kill_)
            {
                activated_particle_[i] = false;
                deactivate_idx_que_.push(i);
            }
        }
    }

    void compute_acceleration()
    {
        State st, new_st;
        for(int i = 0; i < PARTICLE_NUMBER; i++)
        {
            if (activated_particle_[i] == true) 
            {
                st = particle_list_[i]->state;

                new_st.velocity = vec_add(st.velocity, 
                                          vec_multiply({0, 0, -8}, TIMESTEP));
                new_st.position = vec_add(st.position, 
                                          vec_multiply(st.velocity, TIMESTEP));

                particle_list_[i]->state = new_st;
            }
        }
    }

    // void detect_collision()
    // {

    // }

    std::vector<Particle*> &get_list_addr()
    {
        return particle_list_;
    }
};

ParticleManager::ParticleManager() {}
ParticleManager::~ParticleManager() {}


#endif // PARTICLE_LIST_H_