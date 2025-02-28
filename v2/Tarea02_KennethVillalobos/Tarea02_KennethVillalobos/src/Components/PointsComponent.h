// Copyright 2024, Kenneth Villalobos

#ifndef POINTSCOMPONENT_H
#define POINTSCOMPONENT_H

struct PointsComponent {
public:
  size_t points;

public:
  explicit PointsComponent(const size_t points = 0)
    : points(points) {
  };
};

#endif  // POINTSCOMPONENT_H
