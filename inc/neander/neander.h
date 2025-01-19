#ifndef NEANDER_H
#define NEANDER_H

#include <bits/stdc++.h>

#include "pc.h"
#include "ula.h"
#include "memory.h"
#include "instrucao.h"
#include "opcode.h"

class Neander
{
private:
    int AC;   ///!> Registrador acumulador.
    int RDM;  ///!> Dado a ser armazenado na memória.
    int &REM; ///!> Representa um endereço de memória.
    PC pc;
    ULA ula;

    ///[!] Método para buscar a instrução na memória.
    Instrucao fetch(Memory &memory)
    {
        Instrucao m_instrucao{memory.read(pc.get_carga())};
        return m_instrucao;
    }

    void decode(Instrucao instrucao)
    {
        switch (instrucao.opcode)
        {
        case Opcode::NOP:
            /* Nada */
            break;
        case Opcode::STA_END:
            STA(instrucao.endereco);
            break;
        case Opcode::LDA_END:
            LDA(instrucao.endereco);
            break;
        case Opcode::ADD_END:
            ADD(instrucao.endereco);
            break;
        case Opcode::AND_END:
            AND(instrucao.endereco);
            break;
        case Opcode::OR_END:
            OR(instrucao.endereco);
            break;
        case Opcode::NOT:
            NOT();
            break;
        case Opcode::JMP_END:
            JMP(instrucao.endereco);
            break;
        case Opcode::JN_END:
            JN(instrucao.endereco);
            break;
        case Opcode::JZ_END:
            JZ(instrucao.endereco);
            break;
        default:    ///[!] Opcode padrção é HLT.
            return; ///[!] Fim de ciclo.
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

    void NOT()
    {
        AC = ula.not_operation(AC); // Chama a operação NOT para inverter os bits de 'AC'
    }

    void JMP(int &end)
    {
        pc.set_carga(end); // Desvia incondicionalmente para o endereço "end".
    }

    void JN(int &end)
    {
        if (AC < 0)            // Desvia se o AC for negativo
            pc.set_carga(end); // Desvia para o endereço "end".
    }

    void JZ(int &end)
    {
        if (AC == 0)           // Desvia se o AC for zero
            pc.set_carga(end); // Desvia para o endereço "end".
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