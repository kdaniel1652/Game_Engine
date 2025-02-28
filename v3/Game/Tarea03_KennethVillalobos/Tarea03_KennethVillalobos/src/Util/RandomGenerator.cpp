// Copyright 2024, Kenneth Villalobos

#include "RandomGenerator.h"

RandomGenerator::RandomGenerator(const float lowerLimit,
  const float upperLimit) {
  std::random_device seed;
  this->generator = std::mt19937(seed());
  this->distribution = std::uniform_real_distribution<float>(lowerLimit,
    upperLimit);
}

float RandomGenerator::generate() {
  return this->distribution(this->generator);
}
