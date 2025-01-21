#ifndef INSTRUCAO_HPP
#define INSTRUCAO_HPP

#include <cstdint> /// std::uint8_t

using byte = std::uint8_t;

class Instrucao
{
private:
  /* !!!
   * Por mais que `opcode` e `endereco` sejam declarados como bytes, na implementação
   * desse projeto, cada um ocupa somente 4 bits de memória.
   */
  byte opcode;   ///!> Código de instrução.
  byte endereco; ///!> Endereço de dado.

public:
  Instrucao(byte opcode = byte(), byte endereco = byte());

  Instrucao(const Instrucao &other);

  Instrucao &operator=(const Instrucao &other);

  byte get_opcode();

  byte get_endereco();

  byte to_byte() const;

  static Instrucao from_byte(byte encoded);
};

#endif /// INSTRUCAO_HPP
