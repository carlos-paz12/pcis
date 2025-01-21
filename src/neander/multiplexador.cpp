#ifndef MULTIPLEXADOR_CPP
#define MULTIPLEXADOR_CPP
#include "../../inc/neander/Multiplexador.hpp"

uint8_t Multiplexador::selecionar(uint8_t entrada1, uint8_t entrada2, bool controle)
{
    return controle ? entrada2 : entrada1;
}
#endif