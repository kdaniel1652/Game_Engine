// Copyright 2024, Kenneth Villalobos

#ifndef WINDOWREADER_H
#define WINDOWREADER_H

#include <SDL.h>
#include <string>

#include "Reader.h"

class WindowReader : Reader {
protected:
  int width;
  int height;
  friend class Game;

protected:
  virtual std::istream& read(std::istream& is) override {
    return is >> this->width >> this->height;
  };

public:
  WindowReader() = default;
  virtual ~WindowReader() = default;

  SDL_Window* build(const std::string& gameName) {
    return SDL_CreateWindow(
      gameName.c_str(),
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      this->width,
      this->height,
      SDL_WINDOW_SHOWN
    );
  }
};

#endif  // WINDOWREADER_H
