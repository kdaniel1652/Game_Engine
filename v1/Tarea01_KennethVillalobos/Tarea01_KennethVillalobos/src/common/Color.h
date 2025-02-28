// Copyright 2024, Kenneth Villalobos

#ifndef COLOR_H
#define COLOR_H

/**
  * @namespace Namespace to store all the classes and structs implemented on
  * the project
  */
namespace gameDev {
  /**
    * @brief Struct to store int values that represent RGB color combination
    * @remark This solution was preferred over the color the SDL_Color structs
    * since they dont use ints, and the reading was problematic
    */
  struct Color {
  public:
    int r = 0;
    int g = 0;
    int b = 0;
  };
}

#endif  // COLOR_H
