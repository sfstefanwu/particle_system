# CSCE649 Project 2: Particle System
## Features
- Particle generator
  - An omnidirectional particle generator initializes direction, position, velocity, and life span of particles
  - Initial attributes drawn from a probability distribution
  - Movable through keyboard control
- Random Number Generator
  - Precompute a large array of random numbers to reduce computational complexity
- Multithreading with OpenMP
  - Handle 75k particles in realtime on 12-core CPU, including computation of particle generation, collision detection and handling, external forces, etc.
- Collision Detection and Response
  - Support Polygonal Face Detection 
  - Friction in the collision response
- Integrator
  - Basic Euler Integration
- External force
  - Gravity
  - Wind
