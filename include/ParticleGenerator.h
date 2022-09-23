#ifndef PARTICLEGENERATOR_H_
#define PARTICLEGENERATOR_H_

#include "RandGenerator.h"
#include "Math.h"


class ParticleGenerator
{
private:
    RandGenerator rand_generator_;
    float init_speed_mean_;
    float init_speed_std_;
    // 
    
public:
    ParticleGenerator();
    ~ParticleGenerator();
};

ParticleGenerator::ParticleGenerator() 
{
    rand_generator_.reset();
    init_speed_mean_ = INIT_SPEED_MEAN;
    init_speed_std_ = INIT_SPEED_STD;
}
ParticleGenerator::~ParticleGenerator() {}


#endif // PARTICLEGENERATOR_H_