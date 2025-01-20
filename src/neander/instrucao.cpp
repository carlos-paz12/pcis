#ifndef INSTRUCAO_CPP
#define INSTRUCAO_CPP

#include "../../inc/neander/Instrucao.hpp"

Instrucao::Instrucao(std::uint8_t opcode = std::uint8_t(), std::uint8_t endereco = std::uint8_t()) : opcode(opcode), endereco(endereco) { /* empty */ }

Instrucao::Instrucao(const Instrucao &other) : opcode(other.opcode), endereco(other.endereco) { /* empty */ }

Instrucao &Instrucao::operator=(const Instrucao &other)
{
    if (this != &other)
    {
        opcode = other.opcode;
        endereco = other.endereco;
    }
    return (*this);
}

constexpr std::uint8_t Instrucao::to_uint8() const
{
    return (opcode << 4) | (endereco & 0x0F);
}

Instrucao Instrucao::from_uint8(uint8_t encoded)
{
    std::uint8_t opcode = (encoded >> 4) & 0x0F;
    std::uint8_t endereco = encoded & 0x0F;

    return Instrucao(opcode, endereco);
}

std::uint8_t Instrucao::get_opcode()
{
    return opcode;
}

std::uint8_t Instrucao::get_endereco()
{
    return endereco;
}

#endif