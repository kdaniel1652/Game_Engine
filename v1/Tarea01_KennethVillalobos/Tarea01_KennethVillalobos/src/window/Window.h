// Copyright 2024, Kenneth Villalobos

#ifndef WINDOW_H
#define WINDOW_H

#include <istream>
#include <SDL.h>
#include <string>

#include "../common/Color.h"

/**
  * @namespace Namespace to store all the classes and structs implemented on
  * the project
  */
namespace gameDev {
  // forward delcaration (To avoid circular inclusion problems)
  class Game;

  /**
    * @class Class mainly to store most objects relevant to a window
    */
  class Window {
  // Attributes
  private:
    // SDL Window
    SDL_Window* window = nullptr;
    // Dimensions
    size_t width;
    size_t height;
    // Background color (r, g, b)
    Color color;

    // The Game must be able to interact with the private members
    friend class Game;

  // Constructors
  public:
    /**
     * @brief Default constructor
     * @param width The Width of the window (in pixels)
     * @param height The height of the window (in pixels)
     * @param color RGB combination to use as color for the background
     * @remark This method does not call the @a init method by itself, as
     * it migth be desirable to store the data without initializing the
     * window right away
     * @see bool init(const std::string& tittle = std::string(""))
     */
    Window(const size_t width = 0, const size_t height = 0,
      const Color& color = { 0, 0, 0});
    /**
     * @brief Copy constructor
     * @param other Window to copy the data from
     * @remark This constructor will not copy the window pointer or
     * initialize the window.
     * @see bool init(const std::string& tittle = std::string(""))
     */
    Window(const Window& other);
    /**
     * @brief Move memory constructor
     * @param other Window to steal the memory from
     * @remark This constructor WILL copy the window leaving the other
     * window invalid, after that only this Window must be destroyed
     * @see void destroy();
     */
    Window(Window&& other);
    /**
     * @brief Destructor
     * @remark Automatically calls the @a destroy() method in case it
     * is needed
     * @see void destroy();
     */
    ~Window();
    /**
     * @brief Copy assignator
     * @param other Window to copy the data from
     * @returns a reference to the Window that called the method
     * @remark This assignator will not copy the window pointer or
     * initialize the window.
     * @remark Using this method will automatically call the a@ destroy()
     * metbhod on this object previously to prevent memory leaks
     * @see bool init(const std::string& tittle = std::string(""))
     * @see void destroy();
     */
    Window& operator=(const Window& other);
    /**
     * @brief Move memory assignator
     * @param other Window to steal the memory from
     * @returns a reference to the Window that called the method
     * @remark This assignator WILL swap all parameters between the two
     * objects
     * @remark Using this method will automatically call the a@ destroy()
     * method on this object previously to prevent memory leaks
     * @see void destroy();
     */
    Window& operator=(Window&& other);

    /**
     * @brief Reads the information necessary for a window from the stream
     * @param is Input stream to read from
     * @param window Window where the data will be stored
     * @details The reading format is "size_t size_t int int int", the
     * number of spaces between the elements is variable.
     * @remark If the reading format is not followed, the behavior is
     * undefined
     */
    friend std::istream& operator>>(std::istream& is, Window& window);

    /**
     * @brief Initializes the window allocating the necessary memory
     * @param tittle String with the tittle of the window
     * @returns a bool indicating if the procedure was successfull
     */
    bool init(const std::string& tittle = std::string(""));
    /**
     * @brief Frees all the allocated memory
     * @remark If the Window was already destroyed, does nothing
     */
    void destroy();
  };
}

#endif  // WINDOW_H
