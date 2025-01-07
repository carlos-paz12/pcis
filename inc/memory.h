#ifndef MEMORY_H
#define MEMORY_H

#include <cstddef>
#include <vector>

class memory {

public:
  memory(size_t size);

  int read(size_t address);

  void write(size_t address, int value);

  void loadProgram(const std::vector<int> &program);

private:
  std::vector<int> data;
};

#endif // MEMORY_H