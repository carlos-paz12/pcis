#ifndef INSTRUCAO_HPP
#define INSTRUCAO_HPP

#include <cstdint> /// std::uint8_t

class Instrucao {
private:
  std::uint8_t opcode;   ///!> Código de instrução.
  std::uint8_t endereco; ///!> Endereço de dado.

public:
  Instrucao(std::uint8_t opcode = std::uint8_t(),
            std::uint8_t endereco = std::uint8_t());

  Instrucao(const Instrucao &other);

  Instrucao &operator=(const Instrucao &other);

  constexpr std::uint8_t to_uint8() const;

  static Instrucao from_uint8(uint8_t encoded);

  std::uint8_t Instrucao::get_opcode();

  std::uint8_t Instrucao::get_endereco();
};

#endif /// INSTRUCAO_HPP
