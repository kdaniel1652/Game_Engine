// Copyright 2024, Kenneth Villalobos

#ifndef READER_H
#define READER_H

#include <iostream>

class Reader {
protected:
  virtual std::istream& read(std::istream& is) = 0;

public:
  Reader() = default;
  virtual ~Reader() = default;

  friend std::istream& operator>>(std::istream& is, Reader& reader) {
    return reader.read(is);
  }
};

#endif  // READER_H
