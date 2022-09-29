#ifndef COLLISION_HANDLER_H_
#define COLLISION_HANDLER_H_

#include <vector>

#include "Math.h"
#include "Particle.h"

class CollisionHandler
{
private:
    std::vector<TrianglePlain> plains_;
    float distance_curr_;
    float distance_next_;
    int idx_collision_plain_;
    

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

public:
    CollisionHandler();

    void reset()
    {
        idx_collision_plain_ = -1;
    }

    void add_plain(float plain[])
    {
        //-----------------------------------------
        // positions       // colors
        // 1,  -1,  0,     0.6f, 0.9f, 0.8f, 
        // 1, 0,  -1,      0.6f, 0.9f, 0.8f,
        // 0,  -1, 0,      0.6f, 0.9f, 0.8f
        //-----------------------------------------

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

    bool detect_collision(Vec *position_curr, Vec *position_next) 
    {
        for(int i = 0; i < plains_.size(); i++) 
        {
            distance_curr_ = calculate_signed_distance(i, position_curr);
            distance_next_ = calculate_signed_distance(i, position_next);

            if (std::signbit(distance_curr_) != std::signbit(distance_next_)) 
            {
                if (test_pos_over_triplain(i, position_curr))
                {
                    idx_collision_plain_ = i;
                    return true;
                }
            }
        }
        return false;
    }

    void set_collision_response(State *st, State *new_st)
    {
        Vec normal = plains_[idx_collision_plain_].get_unit_normal_vec();

        new_st->position = vec_substract(
            new_st->position,
            vec_multiply(normal, distance_next_ * (1 + k_restitution_coef)));

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

    ~CollisionHandler();
};

CollisionHandler::CollisionHandler(/* args */)
{
}

CollisionHandler::~CollisionHandler()
{
}


#endif // COLLISION_HANDLER_H_