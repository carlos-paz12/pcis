#ifndef INSTRUCTION_CESAR_HPP
#define INSTRUCTION_CESAR_HPP

#include <string>

#include "Opcode.hpp"
#include "AddressingMode.hpp"

using str = std::string;

struct Instruction
{
    Opcode opcode;             // Código da operação
    AddressingMode addressing; // Modo de endereçamento
    str mnemonic;      // Nome da operação (opcional)
};
#endif
