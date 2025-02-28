// Copyright 2024, Kenneth Villalobos

#include <algorithm>

#include "Font.h"

gameDev::Font::Font(const std::string& path, const Color& color, int size)
  : path(path),
  color(color),
  size(size) {
}

gameDev::Font::Font(const Font& other)
  : path(other.path),
  color(other.color),
  size(other.size) {
}

gameDev::Font::Font(Font&& other)
  : path(""),
  color({0, 0, 0}),
  size(0) {
  std::swap(this->path, other.path);
  std::swap(this->color, other.color);
  std::swap(this->size, other.size);
}

gameDev::Font::~Font() {
  this->destroy();
}

gameDev::Font gameDev::Font::operator=(const Font& other) {
  this->destroy();

  this->path = other.path;
  this->color = other.color;
  this->size = other.size;
  return *this;
}

gameDev::Font gameDev::Font::operator=(Font&& other) {
  this->destroy();

  std::swap(this->font, other.font);
  std::swap(this->path, other.path);
  std::swap(this->color, other.color);
  std::swap(this->size, other.size);

  return *this;
}

std::istream& gameDev::operator>>(std::istream& is, Font& font) {
  font.destroy();

  return is
    >> font.path
    >> font.color.r >> font.color.g >> font.color.b
    >> font.size;
}

bool gameDev::Font::init() {
  this->font = TTF_OpenFont(this->path.c_str(),
    this->size);

  return this->font != nullptr;
}

void gameDev::Font::destroy() {
  if (this->font) {
    TTF_CloseFont(this->font);
    this->font = nullptr;
  }
}