// Copyright 2024 Kenneth Villalobos

#ifndef POOL_H
#define POOL_H

#include <vector>

class IPool {
public:
  virtual ~IPool() {
  }
};

template<typename TComponent>
class Pool : public IPool {
private:
  std::vector<TComponent> data;

public:
  Pool(const size_t size = 200)
  : data(size) {
  }
  virtual ~Pool() = default;

  bool isEmpty() {
    return this->data.empty();
  }

  size_t getSize() const {
    return this->data.size();
  }

  void resize(const size_t size) {
    this->data.resize(size);
  }

  void clear() {
    this->data.clear();
  }

  void add(TComponent& object) {
    this->data.push_back(object);
  }

  void set(const size_t index, TComponent& object) {
    this->data[index] = object;
  }

  TComponent& get(const size_t index) {
    return static_cast<TComponent&>(data[index]);
  }

  TComponent& operator[](const size_t index) {
    return static_cast<TComponent&>(data[index]);
  }
};

#endif  // POOL_H
