#ifndef ULA_CPP
#define ULA_CPP

#include "../../inc/neander/ULA.hpp"

byte ULA::sum_operation(const byte x, const byte y)
{
    res = (x + y) & 0xFF;
    define_flag();
    return res;
}

byte ULA::and_operation(const byte x, const byte y)
{
    res = (x & y);
    define_flag();
    return res;
}

byte ULA::or_operation(const byte x, const byte y)
{
    res = (x | y);
    define_flag();
    return res;
}

byte ULA::not_operation(const byte x)
{
    res = (~x);
    define_flag();
    return res;
}

byte ULA::y_operation(const byte x, const byte y)
{
    res = y;
    define_flag();
    return res;
}

byte ULA::mux_operation(const byte x, const byte y, bool controle)
{
    return mux.selecionar(x, y, controle);
}

byte ULA::get_res()
{
    return res;
}

Flag ULA::get_flag()
{
    return flag;
}

void ULA::define_flag()
{
    ///[!] Se o bit mais significativo de AC for 1, o número é negativo (complemento de dois).
    if (res == 0)
        ///[!] Flag N ativada se o AC for negativo.
        flag = Flag::FLAG_Z;
    else
        ///[!] Flag Z ativada se o AC for zero.
        flag = Flag::FLAG_N;
}

#endif
