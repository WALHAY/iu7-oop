#pragma once

#include <cstddef>

class Edge
{
  public:
    Edge(const Edge &edge) = default;
    Edge(size_t first, size_t second);

    Edge &operator=(const Edge &edge) = default;

    size_t getFirst();
    size_t getSecond();

    size_t getFirst() const;
    size_t getSecond() const;

  private:
    size_t first;
    size_t second;
};
