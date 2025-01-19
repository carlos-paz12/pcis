#ifndef INSTRUCAO_H
#define INSTRUCAO_H

#include "opcode.h"

struct Instrucao
{
    Opcode opcode; ///!> Código de instrução.
    int &endereco; ///!> Endereço do dado da instrução.

    Instrucao(Opcode opcode, int &endereco) : opcode(opcode), endereco(endereco) { /* empty */ }

    Instrucao(const Instrucao &other) : opcode(other.opcode), endereco(other.endereco) { /* empty */ }

    Instrucao &operator=(const Instrucao &other)
    {
        if (this != &other)
        {
            opcode = other.opcode;
            endereco = other.endereco;
        }
        return (*this);
    }
};

#endif