// Copyright 2024, Kenneth Villalobos

#ifndef FONT_H
#define FONT_H

#include <istream>
#include <SDL.h>
#include <SDL_ttf.h>
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
    * @class Class mainly to store most objects relevant to a font
    */
  class Font {
  // Attributes
  private:
    // TTF Font
    TTF_Font* font = nullptr;
    // Relative path to the font
    std::string path;
    // Color of the font (r, g, b)
    Color color;
    // Size of the font (not dimensions)
    int size = 0;

    // The Game must be able to interact with the private members
    friend class Game;

  // Constructors
  public:
    /**
     * @brief Default constructor
     * @param path Relative path to the font
     * @param color RGB combination to use as color for the font
     * @param size Size of the font (not dimensions)
     * @remark This method does not call the @a init method by itself, as
     * it migth be desirable to store the data without initializing the
     * font right away
     * @see bool init()
     */
    Font(const std::string& path = std::string(""),
      const Color& color = { 0, 0, 0 }, const int size = 0);
    /**
     * @brief Copy constructor
     * @param other font to copy the data from
     * @remark This constructor will not copy the font pointer or
     * initialize the font.
     * @see bool init()
     */
    Font(const Font& other);
    /**
     * @brief Move memory constructor
     * @param other font to steal the memory from
     * @remark This constructor WILL copy the font leaving the other
     * font invalid, after that only this font must be destroyed
     * @see void destroy();
     */
    Font(Font&& other);
    /**
     * @brief Destructor
     * @remark Automatically calls the @a destroy() method in case it
     * is needed
     * @see void destroy();
     */
    ~Font();
    /**
     * @brief Copy assignator
     * @param other Font to copy the data from
     * @returns a reference to the Font that called the method
     * @remark This assignator will not copy the font pointer or
     * initialize the font.
     * @remark Using this method will automatically call the a@ destroy()
     * metbhod on this object previously to prevent memory leaks
     * @see bool init()
     * @see void destroy();
     */
    Font operator=(const Font& other);
    /**
     * @brief Move memory assignator
     * @param other Font to steal the memory from
     * @returns a reference to the Font that called the method
     * @remark This assignator WILL swap all parameters between the two
     * objects
     * @remark Using this method will automatically call the a@ destroy()
     * method on this object previously to prevent memory leaks
     * @see void destroy();
     */
    Font operator=(Font&& other);
    
    /**
     * @brief Reads the information necessary for a font from the stream
     * @param is Input stream to read from
     * @param font Font where the data will be stored
     * @details The reading format is "string int int int", the
     * number of spaces between the element is variable.
     * @remark If the reading format is not followed, the behavior is
     * undefined
     */
    friend std::istream& operator>>(std::istream& stream, Font& font);

    /**
     * @brief Initializes the font allocating the necessary memory
     * @param tittle String with the tittle of the font
     * @returns a bool indicating if the procedure was successfull
     */
    bool init();
    /**
     * @brief Frees all the allocated memory
     * @remark If the Font was already destroyed, does nothing
     */
    void destroy();
  };
}

#endif  // FONT_H
