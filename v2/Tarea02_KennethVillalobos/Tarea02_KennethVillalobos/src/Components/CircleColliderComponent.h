// Copyright 2024, Kenneth Villalobos

#ifndef CIRCLECOLLIDERCOMPONENT_H
#define CIRCLECOLLIDERCOMPONENT_H

struct CircleColliderComponent {
public:
  double radius;

public:
  explicit CircleColliderComponent(const float radius = 0.0f)
    : radius(radius) {
  };
};

#endif  // CIRCLECOLLIDERCOMPONENT_H
