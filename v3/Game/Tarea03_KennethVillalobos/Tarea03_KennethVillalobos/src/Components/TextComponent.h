// Copyright 2024, Kenneth Villalobos

#ifndef TEXTCOMPONENT_H
#define TEXTCOMPONENT_H

#include <string>

struct TextComponent {
public:
  std::string assetId;
  std::string label;
  int r, g, b, a;

public:
  TextComponent(const std::string& assetId = "",
    const std::string& label = "", const int r = 0, const int g = 0,
    const int b = 0, const int a = 255)
    : assetId(assetId),
    label(label),
    r(r),
    g(g),
    b(b),
    a(a) {
  }
};

#endif  // TEXTCOMPONENT_H
