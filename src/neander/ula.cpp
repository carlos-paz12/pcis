#ifndef ULA_CPP
#define ULA_CPP

#include "../../inc/neander/ULA.hpp"

byte ULA::sum_operation(const byte x, const byte y) { return (x + y) & 0xFF; }
byte ULA::and_operation(const byte x, const byte y) { return (x & y); }
byte ULA::or_operation(const byte x, const byte y) { return (x | y); }
byte ULA::not_operation(const byte x) { return (~x); }
byte ULA::y_operation(const byte x, const byte y) { return y; }
byte ULA::mux_operation(const byte x, const byte y, bool controle) { return mux.selecionar(x, y, controle); }

// if (AC & 0x80) ///[!] Se o bit mais significativo de AC for 1, o número é negativo (complemento de dois).
///[!] Flag N ativada se o AC for negativo.
//  flag = Flag::FLAG_N;
//  else if (AC == 0)
///[!] Flag Z ativada se o AC for zero.
// flag = Flag::FLAG_Z;
// else
///[!] Flag P ativada se o AC for positivo.

#endif