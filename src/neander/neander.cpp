#ifndef NEANDER_CPP
#define NEANDER_CPP

#include "../../inc/neander/Neander.hpp"

Neander::Neander(Memoria &memoria) : memoria(memoria), po(memoria, pc), pc(memoria, po) {}

PC::PC(Memoria &memoria, PO &po) : memoria(memoria), po(po) {}

PO::PO(Memoria &memoria, PC &pc) : memoria(memoria), pc(pc) {}

void Neander::fetch_decode_execute()
{
    po.fetch();
    po.decode();
    po.execute();
    // po.printstate();
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
    std::cout << "| IR: " << std::setw(24) << RI.get_opcode() << " |" << std::endl;
    // std::cout << "| Flags: " << std::setw(20) << std::bitset<8>(/* we had to pick the flag*/ ().to_uint8()) << " |" << std::endl;
    std::cout << "| AC: " << std::setw(25) << (int)AC << " |" << std::endl;
    std::cout << "+---------------------------+" << std::endl;

    std::cout << "|       Registers:          |" << std::endl;

    for (int i = 0; i < 4; ++i)
    {
        int val_rem = memoria.ler(REM);
        int val_rdm = memoria.ler(RDM);
        std::cout << "| R" << i << ": " << std::setw(22) << REM << " |" << std::endl;
        std::cout << "| R" << i << ": " << std::setw(22) << RDM << " |" << std::endl;
    }
    std::cout << "+---------------------------+" << std::endl;

    std::cout << "|         Memory:           |" << std::endl;
    for (int i = 0; i < 256; ++i)
    {
        int val_mem = memoria.ler(i);
        std::cout << "| M" << i << ": " << std::setw(22) << val_mem << " |" << std::endl;
    }
    std::cout << "+---------------------------+" << std::endl;
}

void PO::STA()
{
    REM = RI.get_endereco();
    std::cout << "STA " << (int)REM;
    memoria.escreve(REM, AC); ///[!] Armazena o valor do AC no endereço REM de memória.
    std::cout << "MEM(" << (int)REM << ") <- " << (int)AC;
}

void PO::LDA()
{
    REM = RI.get_endereco();
    std::cout << "LDA " << (int)REM;
    AC = memoria.ler(REM); ///[!] Carrega o valor da memória em REM no AC.
    std::cout << "AC <- MEM(" << (int)REM << ")";
}

void PO::ADD()
{
    REM = RI.get_endereco();
    std::cout << "ADD " << (int)REM;
    RDM = memoria.ler(REM);
    AC = ula.sum_operation(AC, RDM); ///[!] Soma o valor da memória em RDM com o AC.
    std::cout << "AC <- AC + " << (int)RDM;
}

void PO::AND()
{
    REM = RI.get_endereco();
    std::cout << "AND " << (int)REM;
    RDM = memoria.ler(REM);
    AC = ula.and_operation(AC, RDM); ///[!] Opera AND entre AC e memória.
    std::cout << "AC <- AC and MEM(" << (int)RDM << ")";
}

void PO::OR()
{
    REM = RI.get_endereco();
    std::cout << "OR " << (int)REM;
    RDM = memoria.ler(REM);
    AC = ula.or_operation(AC, RDM); ///[!] Opera OR entre AC e memória.
    std::cout << "AC <- AC or RDM(" << (int)RDM << ")";
}

void PO::NOT()
{
    std::cout << "AC <- ~" << (int)AC;
    AC = ula.not_operation(AC); ///[!] Inverte os bits do AC.
}

void PO::JMP()
{
    REM = RI.get_endereco();
    std::cout << "JMP " << (int)REM;
    PO::pc.carga_pc(REM); ///[!] Desvia para o endereço indicado pela instrução.
    std::cout << "PC <- " << (int)REM;
}

void PO::JN()
{
    if (AC & 0x80) ///[!] Se AC for negativo (bit de sinal 1), realiza o salto.
    {
        REM = RI.get_endereco();
        std::cout << "JN " << (int)REM;
        PO::pc.carga_pc(REM);
        std::cout << "PC <- " << (int)REM;
    }
}

void PO::JZ()
{
    if (AC == 0) ///[!] Se AC for zero, realiza o salto.
    {
        REM = RI.get_endereco();
        std::cout << "JZ " << (int)REM;
        PO::pc.carga_pc(REM);
        std::cout << "PC <- " << (int)REM;
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
    std::cout << ">>> INICIANDO CICLO DE BUSCA\n";

    std::cout << "\tPC = " << (int)pc.get_pc() << '\n';

    REM = pc.get_pc();      ///[!] O endereço de memória atual é o valor do contador de programa.
    std::cout << "\tREM <- PC\t; REM = " << (int)REM << '\n';

    RDM = memoria.ler(REM); ///[!] Lê o valor da memória no endereço de REM.
    std::cout << "\tRDM <- MEM(" << (int)REM << ")\t; RDM = " << (int)RDM << '\n';

    pc.incrementa_pc();     ///[!] Incrementa o contador de programa (avança para o próximo endereço de instrução).
    std::cout << "\tPC++" << "\t; Incremento do contador de programa\n";

    pc.incrementa_cc();     ///[!] Incrementa o contador de ciclos.
    std::cout << "\tCC++" << "\t; Incremento do contador de ciclo\n\n";

}

void PO::decode()
{
    std::cout << ">>> INICIANDO CICLO DE DECODIFICAÇÃO\n";

    RI = Instrucao::from_byte(RDM); ///[!] Decodifica a instrução lida.
    std::cout << "\tRI <- decode(" << (int)RDM << ")\n";
    std::cout << "\tRI = {" << (int)RI.get_opcode() << ", " << (int)RI.get_endereco() << "}\n";

    pc.incrementa_cc();     ///[!] Incrementa o contador de ciclos.
    std::cout << "\tCC++" << "\t; Incremento do contador de ciclo\n\n";
}

void PO::execute()
{
    std::cout << ">>> INICIANDO CICLO DE EXECUÇÃO\n";
    switch (RI.get_opcode())
    {
    case Opcode::NOP:
        ///[!] Nenhuma operação.
        break;
    case Opcode::STA_END:
        STA(); ///[!] Chama a operação STA.
        break;
    case Opcode::LDA_END:
        LDA(); ///[!] Chama a operação LDA.
        break;
    case Opcode::ADD_END:
        ADD(); ///[!] Chama a operação ADD.
        break;
    case Opcode::AND_END:
        AND(); ///[!] Chama a operação AND.
        break;
    case Opcode::OR_END:
        OR(); ///[!] Chama a operação OR.
        break;
    case Opcode::NOT:
        NOT(); ///[!] Chama a operação NOT.
        break;
    case Opcode::JMP_END:
        JMP(); ///[!] Chama a operação JMP.
        break;
    case Opcode::JN_END:
        JN(); ///[!] Chama a operação JN.
        break;
    case Opcode::JZ_END:
        JZ(); ///[!] Chama a operação JZ.
        break;
    case Opcode::MUX:
        //MUX(); ///[!] Chama a operação do multiplexador com controle fixo.
        break;
    default:
        ///[!] Caso padrão é HALT (não há ação).
        break;
    }
}

#endif