#ifndef ULA_HPP
#define ULA_HPP

#include <cstdint>

#include "Multiplexador.hpp"
#include "Flag.hpp"

using byte = std::uint8_t;

class ULA
{
private:
    byte res;
    Flag flag;
    Multiplexador mux;

    void define_flag();

public:
    byte sum_operation(const byte x, const byte y); ///[!] Soma com máscara de 8 bits.

    byte and_operation(const byte x, const byte y); ///[!] Operação lógica "AND" bit a bit.

    byte or_operation(const byte x, const byte y);  ///[!] Operação lógica "OR" bit a bit.

    byte not_operation(const byte x);               ///[!] Operação de inversão (complemento de 1).

    byte y_operation(const byte x, const byte y);   ///[!] Seleção direta.

    byte mux_operation(const byte x, const byte y, bool controle); ///[!] Operação do multiplexador.

    byte get_res();

    Flag get_flag();
};

#endif // ULA_HPP