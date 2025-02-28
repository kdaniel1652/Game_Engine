// Copyright 2024, Kenneth Villalobos

#ifndef ALLIESCOMPONENT_H
#define ALLIESCOMPONENT_H

struct AlliesComponent {
public:
  size_t team;

public:
  explicit AlliesComponent(const size_t team = 0)
    : team(team) {
  };
};

#endif  // ALLIESCOMPONENT_H
