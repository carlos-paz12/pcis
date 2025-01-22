#ifndef MULTIPLEXADOR_HPP
#define MULTIPLEXADOR_HPP

#include <cstdint>

using byte = std::uint8_t;

class Multiplexador {
public:
  byte selecionar(byte entrada1, byte entrada2, bool controle);
};

#endif // MULTIPLEXADOR_HPP