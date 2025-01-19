#ifndef INSTRUCAO_H
#define INSTRUCAO_H

#include <cstdint> /// std::uint8_t
#include "Opcode.hpp"

struct Instrucao
{
    std::uint8_t opcode;   // Código de instrução (8 bits)
    std::uint8_t endereco; // Endereço de dado (8 bits)

    Instrucao(std::uint8_t opcode = std::uint8_t(), std::uint8_t endereco = std::uint8_t())
        : opcode(opcode), endereco(endereco) { /* empty */ }

    Instrucao(const Instrucao &other)
        : opcode(other.opcode), endereco(other.endereco) { /* empty */ }

    Instrucao &operator=(const Instrucao &other)
    {
        if (this != &other)
        {
            opcode = other.opcode;
            endereco = other.endereco;
        }
        return (*this);
    }

    /**
     * Converte a instrução para um único byte.
     * No caso de ser necessário usar um único byte para a instrução.
     * Pode ser ajustado dependendo da forma como você deseja codificar as instruções.
     */
    constexpr std::uint8_t toUint8() const
    {
        return (opcode << 4) | (endereco & 0x0F);
    }

    /**
     * Método para decodificar uma instrução de um byte
     * onde o opcode ocupa os 4 bits mais significativos e o endereço os 4 bits menos significativos.
     */
    static Instrucao fromUint8(uint8_t encoded)
    {
        std::uint8_t opcode = (encoded >> 4) & 0x0F; // 4 bits para opcode
        std::uint8_t endereco = encoded & 0x0F;      // 4 bits para endereço
        return Instrucao(opcode, endereco);
    }
};

#endif
