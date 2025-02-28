// Copyright 2024, Kenneth Villalobos

#ifndef LABEL_H
#define LABEL_H

#include <SDL.h>

/**
  * @namespace Namespace to store all the classes and structs implemented on
  * the project
  */
namespace gameDev {
  /**
    * @brief Struct to store the texture (rendered text) of a label from an
    * entity, along with its dimensions
    */
  struct Label {
  public:
    SDL_Texture* texture = nullptr;
    size_t width;
    size_t height;
  };
}

#endif  // LABEL_H
