#ifndef NEANDER_CPP
#define NEANDER_CPP

#include "../../inc/neander/Neander.hpp"

Neander::Neander(Memoria &memoria) : memoria(memoria), po(memoria, pc), pc(memoria, po) {}

void Neander::fetch_decode_execute()
{
    po.fetch();
    po.decode();
    po.printstate();
    po.execute();
}

void Neander::print()
{
    po.printstate();
}

///=======================================///
/// Implementação da Parte Operativa (PO) ///
///=======================================///

void PO::printstate()
{
    std::cout << "+---------------------------+" << std::endl;
    std::cout << "|         CPU STATE         |" << std::endl;
    std::cout << "+---------------------------+" << std::endl;
    std::cout << "| PC: " << std::setw(24) << (int)pc.get_pc() << " |" << std::endl;
    std::cout << "| IR: " << std::setw(24) << (int)RI.to_uint8() << " |" << std::endl;
    std::cout << "| Flags: " << std::setw(20) << std::bitset<8>(/* we had to pick the flag*/().to_uint8()) << " |" << std::endl;
    std::cout << "| AC: " << std::setw(25) << (int)AC << " |" << std::endl;
    std::cout << "+---------------------------+" << std::endl;

    std::cout << "|       Registers:          |" << std::endl;
    for (int i = 0; i < 4; ++i)
    {
        std::cout << "| R" << i << ": " << std::setw(22) << (int)memoria.read(i) << " |" << std::endl;
    }
    std::cout << "+---------------------------+" << std::endl;

    std::cout << "|         Memory:           |" << std::endl;
    for (int i = 0; i < 256; ++i)
    {
        std::cout << "| M" << i << ": " << std::setw(22) << (int)memoria.read(i) << " |" << std::endl;
    }
    std::cout << "+---------------------------+" << std::endl;
}

void PO::STA()
{
    REM = RI.get_endereco();
    memoria.write(REM, AC); ///[!] Armazena o valor do AC no endereço REM de memória.
}

void PO::LDA()
{
    REM = RI.get_endereco();
    AC = memoria.read(REM); ///[!] Carrega o valor da memória em REM no AC.
}

void PO::ADD()
{
    REM = RI.get_endereco();
    RDM = memoria.read(REM);
    AC = ula.sum(AC, RDM); ///[!] Soma o valor da memória em RDM com o AC.
}

void PO::AND()
{
    REM = RI.get_endereco();
    RDM = memoria.read(REM);
    AC = ula.and_operation(AC, RDM); ///[!] Opera AND entre AC e memória.
}

void PO::OR()
{
    REM = RI.get_endereco();
    RDM = memoria.read(REM);
    AC = ula.or_operation(AC, RDM); ///[!] Opera OR entre AC e memória.
}

void PO::NOT()
{
    AC = ula.not_operation(AC); ///[!] Inverte os bits do AC.
}

void PO::JMP()
{
    REM = RI.get_endereco();
    PO::pc.carga_pc(REM); ///[!] Desvia para o endereço indicado pela instrução.
}

void PO::JN()
{
    if (AC & 0x80) ///[!] Se AC for negativo (bit de sinal 1), realiza o salto.
    {
        REM = RI.get_endereco();
        PO::pc.carga_pc(REM);
    }
}

void PO::JZ()
{
    if (AC == 0) ///[!] Se AC for zero, realiza o salto.
    {
        REM = RI.get_endereco();
        PO::pc.carga_pc(REM);
    }
}

void PO::reset()
{
    AC = 0;
    REM = 0;
    RDM = 0;
    RI = Instrucao();
    PO::pc.carga_pc(0);
}

void PO::fetch()
{
    REM = pc.get_pc();               // O endereço de memória atual é o valor do contador de programa
    RDM = memoria.read(REM);         // Lê o valor da memória no endereço de REM
    RI = Instrucao::from_uint8(RDM); // Decodifica a instrução lida
    pc.incrementa_pc();              // Avança para o próximo endereço de memória
    pc.incrementa_cc();              // Incrementa o contador de ciclos
}

void Neander::PC::decode()
{
    switch (RI.get_opcode())
    {
    case Opcode::NOP:
        // Nenhuma operação
        break;
    case Opcode::STA_END:
        PO::STA(); // Chama a operação STA
        break;
    case Opcode::LDA_END:
        PO::LDA(); // Chama a operação LDA
        break;
    case Opcode::ADD_END:
        PO::ADD(); // Chama a operação ADD
        break;
    case Opcode::AND_END:
        PO::AND(); // Chama a operação AND
        break;
    case Opcode::OR_END:
        PO::OR(); // Chama a operação OR
        break;
    case Opcode::NOT:
        PO::NOT(); // Chama a operação NOT
        break;
    case Opcode::JMP_END:
        PO::JMP(); // Chama a operação JMP
        break;
    case Opcode::JN_END:
        PO::JN(); // Chama a operação JN
        break;
    case Opcode::JZ_END:
        PO::JZ(); // Chama a operação JZ
        break;
    default:
        // Caso padrão é HALT (não há ação)
        break;
    }
}

void Neander::PC::execute()
{
    // Em caso de alguma execução final ou adicional que se precise fazer
}

void Neander::fetch_decode_execute()
{
    while (true)
    {
        fetch();
        decode();
        if (RI.get_opcode() == Opcode::HLT)
            break; // Interrompe a execução quando o código de operação for HALT
    }
}

#endif