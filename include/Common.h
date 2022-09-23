#ifndef COMMON_H_
#define COMMON_H_

#define PROJ_NAME "PARTICLE SYSTEM"
#define ENABLE_LOGGER true

/**
 * OBJECT PARAMS
 */ 
#define EDGE_SIZE 100.0         
#define BALL_MASS 1.0   
#define BALL_NUMBER 512

/**
 * PARTICLE GENERATOR PARAMS
 */ 
#define RAND_VEC_LEN 331
#define INIT_SPEED_MEAN 10.0
#define INIT_SPEED_STD 5.0
#define NEW_BALL_EACH_TIMESTEP 2

const Vec init_position = {EDGE_SIZE/2, EDGE_SIZE/2, EDGE_SIZE*3/4};

/**
 * CRONO
 */
#define TIMESTEP 0.02            // sec
#define MAX_DISPLAY_TIME 30      // sec

/**
 * VIEW PARAMS
 */ 
#define SCR_WIDTH 1600
#define SCR_HEIGHT 1000
#define DISPLAY_REFRESH_INTERVAL (1.0 / 30.0) //  HZ

#include "Math.h"

/**
 * FORCE
 */ 
const double k_airres_coef = 0.05;
const double k_friction_coef = 0.25;
const double k_simplified_friction_coef = 0.2;
const double k_restitution_coef = 0.8;
const struct Vec k_gravity = {0, 0, -10};
const struct Vec k_wind_velocity = {0, 0, 0};


#endif // COMMON_H_