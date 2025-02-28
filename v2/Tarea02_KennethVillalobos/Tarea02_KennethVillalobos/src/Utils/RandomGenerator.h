// Copyright 2024, Kenneth Villalobos

#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <random>

class RandomGenerator {
private:
  std::mt19937 generator;
  std::uniform_real_distribution<float> distribution;

public:
  RandomGenerator(const float lowerLimit, const float upperLimit);
  float generate();
};

#endif  // RANDOMGENERATOR_H