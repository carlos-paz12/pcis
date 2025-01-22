#ifndef ULA_CPP
#define ULA_CPP

#include "../../inc/ramses/ULA.hpp"

// Soma com máscara de 8 bits
byte ULA::sum_operation(const byte x, const byte y) { return (x + y) & 0xFF; }

// Operação lógica "AND" bit a bit
byte ULA::and_operation(const byte x, const byte y) { return x & y; }

// Operação lógica "OR" bit a bit
byte ULA::or_operation(const byte x, const byte y) { return x | y; }

// Operação de inversão (complemento de 1)
byte ULA::not_operation(const byte x) { return ~x; }

// Seleção direta
byte ULA::y_operation(const byte x, const byte y) { return y; }

// Operação do multiplexador
byte ULA::mux_operation(const byte x, const byte y, bool controle) {
  return mux.selecionar(x, y, controle);
}

// Subtração com máscara de 8 bits
byte ULA::sub_operation(const byte x, const byte y) { return (x - y) & 0xFF; }

// Operação lógica "XOR" bit a bit
byte ULA::xor_operation(const byte x, const byte y) { return x ^ y; }

// Deslocamento lógico para a esquerda
byte ULA::shl_operation(const byte x) { return (x << 1) & 0xFF; }

// Deslocamento lógico para a direita
byte ULA::shr_operation(const byte x) { return x >> 1; }

byte ULA::add16Bits(const uint16_t a, const uint16_t b) {
  uint16_t result = (a + b) & 0xFFFF; // Soma e aplica a máscara de 16 bits
  return result;
}

// if (AC & 0x80) ///[!] Se o bit mais significativo de AC for 1, o número é
// negativo (complemento de dois).
///[!] Flag N ativada se o AC for negativo.
//  flag = Flag::FLAG_N;
//  else if (AC == 0)
///[!] Flag Z ativada se o AC for zero.
// flag = Flag::FLAG_Z;
// else
///[!] Flag P ativada se o AC for positivo.

#endif