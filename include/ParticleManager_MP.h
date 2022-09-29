#ifndef PARTICLE_LIST_H_
#define PARTICLE_LIST_H_

#include <vector>
#include <queue>
#include <cmath>

#include "Timer.h"
#include "Particle.h"
#include "ParticleGenerator.h"
// #include "CollisionHandler.h"

class ParticleManager
{
private:
    std::queue<int>         deactivate_idx_que_;
    ParticleGenerator       particle_generator_;
    // CollisionHandler        collision_handler_;
    Timer                   *timer_;

    const int k_num_to_generate_ = static_cast<int>(std::floor(GENERATION_RATE * TIMESTEP));
    float age_to_kill_;    

private:
    std::vector<TrianglePlain> plains_;
    inline float calculate_signed_distance(int i, Vec *position) 
    {
        Vec v = vec_substract(*position, plains_[i].p1);
        return vec_dot_product(plains_[i].get_unit_normal_vec(), v);
    }
    inline bool test_pos_over_triplain(int i, Vec *pos)
    {
        Vec v0 = vec_substract(plains_[i].p3, plains_[i].p1);
        Vec v1 = vec_substract(plains_[i].p2, plains_[i].p1);
        Vec v2 = vec_substract(*pos, plains_[i].p1);

        // Compute dot products
        float dot00 = vec_dot_product(v0, v0);
        float dot01 = vec_dot_product(v0, v1);
        float dot02 = vec_dot_product(v0, v2);
        float dot11 = vec_dot_product(v1, v1);
        float dot12 = vec_dot_product(v1, v2);

        // Compute barycentric coordinates
        float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
        float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
        float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

        // Check if point is in triangle
        return (u >= 0) && (v >= 0) && (u + v < 1);
    }
    bool detect_collision(Vec *position_curr, Vec *position_next, float *distance_curr_, float *distance_next_, int *idx_collision_plain_) 
    {
        for(int i = 0; i < plains_.size(); i++) 
        {
            *distance_curr_ = calculate_signed_distance(i, position_curr);
            *distance_next_ = calculate_signed_distance(i, position_next);

            if (std::signbit(*distance_curr_) != std::signbit(*distance_next_)) 
            {
                if (test_pos_over_triplain(i, position_curr))
                {
                    *idx_collision_plain_ = i;
                    return true;
                }
            }
        }
        return false;
    }
    void set_collision_response(State *st, State *new_st, int *idx_collision_plain_, float *distance_next_)
        {
            Vec normal = plains_[*idx_collision_plain_].get_unit_normal_vec();

            new_st->position = vec_substract(
                new_st->position,
                vec_multiply(normal, *distance_next_ * (1 + k_restitution_coef)));

            Vec v_in_normal = vec_multiply(
                normal,
                vec_dot_product(new_st->velocity, normal)
            );
            Vec v_in_tangential = vec_substract(new_st->velocity, v_in_normal);
            new_st->velocity = vec_add(
                vec_multiply(v_in_normal, -k_restitution_coef),
                vec_multiply(v_in_tangential, (1 - k_friction_coef))
            );
        }

public:

    std::vector<Particle*>  particle_list_;
    std::vector<bool>       activated_particle_; 

    ParticleManager();
    ~ParticleManager();

    void add_plain(float plain[])
    {
        TrianglePlain new_triangle_plain;
        Vec temp[3];
        for(int i = 0; i < 3; i++) {   
            temp[i] = transform_gl2phy({
                plain[i * 6 + 0],
                plain[i * 6 + 1],
                plain[i * 6 + 2]
            });
        }
        new_triangle_plain.p1 = temp[0];
        new_triangle_plain.p2 = temp[1];
        new_triangle_plain.p3 = temp[2];

        plains_.push_back(new_triangle_plain);
    }

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
        for(int i = 0; !deactivate_idx_que_.empty() && i < k_num_to_generate_; i++)
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

    State compute_new_state()
    {
        #pragma omp parallel for
        for(int i = 0; i < PARTICLE_NUMBER; i++)
        {
            if (activated_particle_[i] == true) 
            {
                State st, new_st;
                float distance_curr_;
                float distance_next_;
                int idx_collision_plain_;

                st = particle_list_[i]->state;
                new_st.velocity = vec_add(st.velocity, 
                                          vec_multiply(k_gravity, TIMESTEP));
                new_st.position = vec_add(st.position, 
                                          vec_multiply(st.velocity, TIMESTEP));
                new_st.position = vec_add(new_st.position, k_wind_velocity);

                // Detect collision
                if(detect_collision(&st.position, &new_st.position, &distance_curr_, &distance_next_, &idx_collision_plain_))
                {
                    set_collision_response(&st, &new_st, &idx_collision_plain_, &distance_next_);
                }

                // Update new state for the particle
                particle_list_[i]->state = new_st;
            }
        }
    }

    std::vector<Particle*> &get_list_addr()
    {
        return particle_list_;
    }
};

ParticleManager::ParticleManager() {}
ParticleManager::~ParticleManager() {}


#endif // PARTICLE_LIST_H_