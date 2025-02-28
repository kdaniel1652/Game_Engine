// Copyright 2024, Kenneth Villalobos

#ifndef TAGCOMPONENT_H
#define TAGCOMPONENT_H

#include <string>

struct TagComponent {
public:
  std::string tag;

public:
  explicit TagComponent(const std::string tag = "NO-TAG")
    : tag(tag) {
  };
};

#endif  // TAGCOMPONENT_H
