#ifndef NEANDER_HPP
#define NEANDER_HPP

#include <bits/stdc++.h>

#include "Instrucao.hpp"
#include "Memoria.hpp"
#include "Opcode.hpp"
#include "ULA.hpp"

class Neander
{
private:
    enum Flag
    {
        FLAG_N, ///!> Flag N (negativo) é ativado se o resultado for negativo.
        FLAG_Z  ///!> Flag Z (zero) é ativado se o resultado for zero.
    };

    uint32_t ciclos; ///!> Contador de ciclos
    uint8_t AC;      ///!> Registrador acumulador (8 bits).
    uint8_t REM;     ///!> Representa um endereço de memória (8 bits).
    uint8_t PC;      ///!> Contador de programa (8 bits).
    uint8_t RDM;     ///!> Dado a ser armazenado na memória.
    Instrucao RI;    ///!> Registrador de instrução.
    Memoria memoria;

    ULA ula;   ///!> Unidade lógica e aritmética.
    Flag flag; ///!> Flags de controle (indicador de estado).

    ///[!] Método para buscar a instrução na memória.
    void fetch();

    void decode();

    void execute(void (Neander::*f)(uint8_t &end));

    void STA(uint8_t &end);

    void LDA(uint8_t &end);

    void ADD(uint8_t &end);

    void SUB(uint8_t &end);

    void AND(uint8_t &end);

    void OR(uint8_t &end);

    void NOT([[maybe_unused]] uint8_t &end);

    void JMP(uint8_t &end);

    void JN(uint8_t &end);

    void JZ(uint8_t &end);

public:
    Neander();

    void fetch_decode_execute(Memoria &memoria);

    void reset();

    std::string to_string();
};

#endif // NEANDER_H
