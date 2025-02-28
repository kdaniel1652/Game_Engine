// Copyright 2024, Kenneth Villalobos

#include <algorithm>

#include "Window.h"

gameDev::Window::Window(const size_t width, const size_t height,
  const Color& color) 
  : width(width),
  height(height),
  color(color) {
}

gameDev::Window::Window(const Window& other)
  : width(other.width),
  height(other.height),
  color(other.color) {
}

gameDev::Window::Window(Window&& other)
  : width(0),
  height(0),
  color({0, 0, 0}) {
  std::swap(this->width, other.width);
  std::swap(this->height, other.height);
  std::swap(this->color, other.color);
}

gameDev::Window::~Window() {
  this->destroy();
}

gameDev::Window& gameDev::Window::operator=(const Window& other) {
  this->destroy();

  this->width = other.width;
  this->height = other.height;
  this->color = other.color;
  return *this;
}

gameDev::Window& gameDev::Window::operator=(Window&& other) {
  this->destroy();

  std::swap(this->window, other.window);
  std::swap(this->width, other.width);
  std::swap(this->height, other.height);
  std::swap(this->color, other.color);

  return *this;
}

std::istream& gameDev::operator>>(std::istream& is, Window& window) {
  window.destroy();

  return is
    >> window.width >> window.height
    >> window.color.r >> window.color.g >> window.color.b;
}

bool gameDev::Window::init(const std::string& tittle) {
  this->window = SDL_CreateWindow(tittle.c_str(),
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width,
    this->height, SDL_WINDOW_SHOWN);

  return this->window != nullptr;
}

void gameDev::Window::destroy() {
  if (this->window) {
    SDL_DestroyWindow(this->window);
    this->window = nullptr;
  }
}