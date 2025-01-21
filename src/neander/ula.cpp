#ifndef ULA_CPP
#define ULA_CPP

#include "../../inc/neander/ULA.hpp"

byte ULA::sum_operation(const byte x, const byte y) { return (x + y) & 0xFF; }

byte ULA::and_operation(const byte x, const byte y) { return (x & y); }

byte ULA::or_operation(const byte x, const byte y) { return (x | y); }

byte ULA::not_operation(const byte x) { return (~x); }

byte ULA::y_operation(const byte x, const byte y) { return y; }

#endif