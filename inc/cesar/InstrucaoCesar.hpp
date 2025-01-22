#ifndef INSTRUCAO_CESAR_HPP
#define INSTRUCAO_CESAR_HPP

#include <string>

#include "OpcodeCesar.hpp"
#include "AddressingMode.hpp"

using str = std::string;

struct InstrucaoCesar
{
    OpcodeCesar opcode;             // Código da operação
    AddressingMode addressing; // Modo de endereçamento
    str mnemonic;      // Nome da operação (opcional)
};
#endif
