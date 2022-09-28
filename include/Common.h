#ifndef COMMON_H_
#define COMMON_H_

#define PROJ_NAME "PARTICLE SYSTEM"
#define ENABLE_LOGGER true

/**
 * OBJECT PARAMS
 */ 
#define EDGE_SIZE 100         
#define PARTICLE_MASS 1.0   
#define PARTICLE_NUMBER 512

/**
 * PARTICLE GENERATOR PARAMS
 */ 
#define RAND_VEC_LEN 331
#define INIT_SPEED_MEAN 10.0
#define INIT_SPEED_STD 5.0
#define GENERATION_RATE 64.0    // per sec
#define LIFE_SPAN 5.0         // sec

enum struct GENERATOR_TYPE 
{
    OMNI, DIRECTED, DISK, TRIANGLE, SPHERE
};

// const Vec init_position = {EDGE_SIZE/2, EDGE_SIZE/2, EDGE_SIZE*3/4};

/**
 * CRONO
 */
#define TIMESTEP 0.02            // sec
#define MAX_DISPLAY_TIME 3000     // sec

/**
 * VIEW PARAMS
 */ 
#define SCR_WIDTH 1600
#define SCR_HEIGHT 1000
#define DISPLAY_REFRESH_INTERVAL (1.0 / 30.0) //  sec (HZ)

#include <vector>
#include <iostream>

#include "Math.h"

/**
 * FORCE
 */ 

enum struct ACCELERATION 
{
    GRAVITY, AIR_RESISTANCE
};

std::vector<Vec> k_acceleration = 
{
    {0, 0, -10},    //GRAVITY
    {}
};

const double k_airres_coef = 0.05;
const double k_friction_coef = 0.25;
const double k_simplified_friction_coef = 0.2;
const double k_restitution_coef = 0.8;
const struct Vec k_gravity = {0, 0, -10};
const struct Vec k_wind_velocity = {0, 0, 0};

#ifdef ENABLE_LOGGER
void print_vec(Vec v1)
{
    std::cout << "[" << v1.x << ", " << v1.y << ", " << v1.z << "]" << std::endl;
}
#endif


#endif // COMMON_H_