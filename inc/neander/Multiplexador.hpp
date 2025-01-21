#ifndef MULTIPLEXADOR_HPP
#define MULTIPLEXADOR_HPP

#include <cstdint>

class Multiplexador
{
public:
    uint8_t selecionar(uint8_t entrada1, uint8_t entrada2, bool controle)
    {
        return controle ? entrada2 : entrada1;
    }
};

#endif // MULTIPLEXADOR_HPP