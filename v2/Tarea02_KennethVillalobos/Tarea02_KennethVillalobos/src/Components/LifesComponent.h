// Copyright 2024, Kenneth Villalobos

#ifndef LIFESCOMPONENT_H
#define LIFESCOMPONENT_H

struct LifesComponent {
public:
  size_t lifes;

public:
  explicit LifesComponent(const size_t lifes = 1)
    : lifes(lifes) {
  };
};

#endif  // LIFESCOMPONENT_H
