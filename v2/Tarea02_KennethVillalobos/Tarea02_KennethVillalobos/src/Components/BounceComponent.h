// Copyright 2024, Kenneth Villalobos

#ifndef BOUNCECOMPONENT_H
#define BOUNCECOMPONENT_H

struct BounceComponent {
public:
  float bounceSpeedup;

public:
  explicit BounceComponent(const float bounceSpeedup = 1.0f)
    : bounceSpeedup(bounceSpeedup) {
  };
};

#endif  // BOUNCECOMPONENT_H
