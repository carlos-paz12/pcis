#ifndef INSTRUCAO_H
#define INSTRUCAO_H

#include "opcode.h"

struct Instrucao
{
    Opcode opcode; ///!> Código de instrução.
    int &endereco; ///!> Endereço do dado da instrução.

    Instrucao(Opcode opcode, int &endereco) : opcode(opcode), endereco(endereco) { /* empty */ }
};

#endif