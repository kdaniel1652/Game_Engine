// Copyright 2024, Kenneth Villalobos

#ifndef TEXTLABELCOMPONENT_H
#define TEXTLABELCOMPONENT_H

#include <string>

struct TextLabelComponent {
public:
  std::string assetId;
  std::string text;
  int r, g, b, alpha;

public:
  TextLabelComponent(const std::string& assetId = "",
    const std::string& text = "", const int r = 0, const int g = 0,
    const int b = 0, const int alpha = 255)
    : assetId(assetId),
    text(text),
    r(r),
    g(g),
    b(b),
    alpha(alpha) {
  }
};

#endif  // TEXTLABELCOMPONENT_H
