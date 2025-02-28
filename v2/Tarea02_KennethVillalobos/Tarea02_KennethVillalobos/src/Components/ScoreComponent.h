// Copyright 2024, Kenneth Villalobos

#ifndef SCORECOMPONENT_H
#define SCORECOMPONENT_H

struct ScoreComponent {
public:
  size_t score;

public:
  explicit ScoreComponent(const size_t score = 0)
    : score(score) {
  };
};

#endif  // SCORECOMPONENT_H
