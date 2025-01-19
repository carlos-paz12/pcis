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

    int AC;  ///!> Registrador acumulador.
    int REM; ///!> Representa um endereço de memória.
    int PC;  ///!> Contador de programa.

    Instrucao RDM; ///!> Dado a ser armazenado na memória.
    Instrucao RI;  ///!> Registrador de instrução.

    ULA ula;   ///!> Unidade lógica e aritmética.
    Flag flag; ///!> Flags de controle (indicador de estado).

    ///[!] Método para buscar a instrução na memória.
    void
    fetch(Memory &memory)
    {
        REM = PC;               ///[!] Obtém o endereço de memória atual do contador de programa (PC).
        RDM = memory.read(REM); ///[!] Lê o valor da memória no endereço armazenado em REM.
        RI = RDM;               ///[!] Armazena o valor lido no registrador de instrução (RI).
        ++PC;                   ///[!] Incrementa o contador de programa para a próxima instrução.
        decode();               ///[!] Chama a função decode para processar a instrução.
    }

    void decode()
    {
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
        default:    ///[!] Opcode padrção é HLT.
            return; ///[!] Fim de ciclo.
        }
    }

    void execute(void (Neander::*f)(int &end))
    {
        (this->*f)(RI.endereco); // Chama o método de instância no contexto da classe Neander.

        // Atualiza as flags conforme o valor de AC
        if (AC < 0)
        {
            flag = Flag::FLAG_N; // Flag N ativada se o AC for negativo.
        }
        else if (AC == 0)
        {
            flag = Flag::FLAG_Z; // Flag Z ativada se o AC for zero.
        }
    }

public:
    void STA(int &end) { end = AC; }

    void LDA(int &end) { AC = end; }

    void ADD(int &end)
    {
        AC = ula.sum(AC, end); // Chama a função 'sum' da ULA para somar 'AC' com o valor armazenado em 'end'
    }

    void SUB(int &end)
    {
        AC = ula.sub(AC, end); // Chama a função 'sub' da ULA para subtrair o valor de 'end' do 'AC'
    }

    void AND(int &end)
    {
        AC = ula.and_operation(AC, end); // Chama a operação AND bit a bit entre 'AC' e o valor armazenado em 'end'
    }

    void OR(int &end)
    {
        AC = ula.or_operation(AC, end); // Chama a operação OR bit a bit entre 'AC' e o valor armazenado em 'end'
    }

    void NOT([[maybe_unused]] int &end)
    {
        AC = ula.not_operation(AC); // Chama a operação NOT para inverter os bits de 'AC'
    }

    void JMP(int &end)
    {
        PC = end; // Desvia incondicionalmente para o endereço "end".
    }

    void JN(int &end)
    {
        if (AC < 0)   // Desvia se o AC for negativo
            PC = end; // Desvia para o endereço "end".
    }

    void JZ(int &end)
    {
        if (AC == 0)  // Desvia se o AC for zero
            PC = end; // Desvia para o endereço "end".
    }

    /*
    Instrução: LDA 0x05.
    Passos:

    Fetch: Busca o opcode 0001 e o operando 0x05.
    Decode: Identifica a operação LDA e o endereço 0x05.
    Execute: Lê o valor na posição 0x05 da memória e carrega no AC.
    */
};

#endif // NEANDER_H