#ifndef NEANDER_H
#define NEANDER_H

#include <bits/stdc++.h>

#include "Memoria.hpp"
#include "ULA.hpp"
#include "Instrucao.hpp"
#include "Opcode.hpp"

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

    ULA ula;   ///!> Unidade lógica e aritmética.
    Flag flag; ///!> Flags de controle (indicador de estado).
    Memory memory;

    ///[!] Método para buscar a instrução na memória.
    void fetch()
    {
        REM = PC;                       ///[!] Obtém o endereço de memória atual do contador de programa (PC).
        RDM = memory.read(REM);         ///[!] Lê o valor da memória no endereço armazenado em REM.
        RI = Instrucao::fromUint8(RDM); ///[!] Decodifica a instrução lida.
        ++PC;                           ///[!] Incrementa o contador de programa para a próxima instrução.
        ++ciclos;                       ///[!] Incrementa o contador de ciclos na execução da instrução.
        decode();                       ///[!] Chama a função decode para processar a instrução.
    }

    void decode()
    {
        ++ciclos; ///[!] Incrementa o contador de ciclos na execução da instrução.

        switch (RI.opcode)
        {
        case Opcode::NOP:
            /* Nada */
            break;
        case Opcode::STA_END:
            execute(&Neander::STA);
            break;
        case Opcode::LDA_END:
            execute(&Neander::LDA);
            break;
        case Opcode::ADD_END:
            execute(&Neander::ADD);
            break;
        case Opcode::AND_END:
            execute(&Neander::AND);
            break;
        case Opcode::OR_END:
            execute(&Neander::OR);
            break;
        case Opcode::NOT:
            execute(&Neander::NOT);
            break;
        case Opcode::JMP_END:
            execute(&Neander::JMP);
            break;
        case Opcode::JN_END:
            execute(&Neander::JN);
            break;
        case Opcode::JZ_END:
            execute(&Neander::JZ);
            break;
        default:    ///[!] Opcode padrão é HLT.
            return; ///[!] Fim de ciclo.
        }
    }

    void execute(void (Neander::*f)(uint8_t &end))
    {
        ++ciclos; ///[!] Incrementa o contador de ciclos na execução da instrução.

        (this->*f)(RI.endereco); ///[!] Chama o método de instância no contexto da classe Neander.

        ///[!] Atualiza as flags conforme o valor de AC
        if (AC & 0x80) ///[!] Se o bit mais significativo de AC for 1, o número é negativo (complemento de dois)
        {
            flag = Flag::FLAG_N; ///[!] Flag N ativada se o AC for negativo.
        }
        else if (AC == 0)
        {
            flag = Flag::FLAG_Z; ///[!] Flag Z ativada se o AC for zero.
        }
    }

    void reset()
    {
        AC = 0;
        REM = 0;
        PC = 0;
        flag = FLAG_Z;
        ciclos = 0;
    }

public:
    Neander(Memory &memory) : memory(memory), ciclos(0), AC(0), REM(0), PC(0), flag(FLAG_Z) {}

    void STA(uint8_t &end)
    {
        memory.write(end, AC); ///[!] Armazena o valor do AC no endereço da memória.
    }

    void LDA(uint8_t &end)
    {
        AC = memory.read(end); ///[!] Carrega o valor da memória no AC.
    }

    void ADD(uint8_t &end)
    {
        AC = ula.sum(AC, memory.read(end)); ///[!] Soma o valor armazenado em memória com AC.
    }

    void SUB(uint8_t &end)
    {
        AC = ula.sub(AC, memory.read(end)); ///[!] Subtrai o valor armazenado em memória de AC.
    }

    void AND(uint8_t &end)
    {
        AC = ula.and_operation(AC, memory.read(end)); ///[!] Opera AND bit a bit entre AC e valor da memória.
    }

    void OR(uint8_t &end)
    {
        AC = ula.or_operation(AC, memory.read(end)); ///[!] Opera OR bit a bit entre AC e valor da memória.
    }

    void NOT([[maybe_unused]] uint8_t &end)
    {
        AC = ula.not_operation(AC); ///[!] Inverte os bits de AC.
    }

    void JMP(uint8_t &end)
    {
        PC = end; ///[!] Desvia incondicionalmente para o endereço "end".
    }

    void JN(uint8_t &end)
    {
        if (AC & 0x80) ///[!] Se AC for negativo (bit de sinal é 1), realiza o salto.
            PC = end;  ///[!] Desvia para o endereço "end".
    }

    void JZ(uint8_t &end)
    {
        if (AC == 0)  ///[!] Se AC for zero, realiza o salto.
            PC = end; ///[!] Desvia para o endereço "end".
    }
};

#endif // NEANDER_H
