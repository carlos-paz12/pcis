#ifndef ULA_HPP
#define ULA_HPP

#include "Multiplexador.hpp"
#include <cstdint>

using byte = std::uint8_t;

class ULA {
private:
  Multiplexador mux;

public:
  byte sum_operation(const byte x, const byte y); // Soma com máscara de 8 bits
  byte and_operation(const byte x,
                     const byte y); // Operação lógica "AND" bit a bit
  byte or_operation(const byte x,
                    const byte y);  // Operação lógica "OR" bit a bit
  byte not_operation(const byte x); // Operação de inversão (complemento de 1)
  byte y_operation(const byte x, const byte y); // Seleção direta
  byte mux_operation(const byte x, const byte y,
                     bool controle); // Operação do multiplexado
  byte add16Bits(const uint16_t a,
                 const uint16_t b); // Operação do multiplexador

  // Funções adicionais
  byte sub_operation(const byte x,
                     const byte y); // Subtração com máscara de 8 bits
  byte xor_operation(const byte x,
                     const byte y); // Operação lógica "XOR" bit a bit
  byte shl_operation(const byte x); // Deslocamento lógico para a esquerda
  byte shr_operation(const byte x);
};

#endif // ULA_HPP