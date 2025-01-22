#ifndef NEANDER_CPP
#define NEANDER_CPP

#include "../../inc/neander/Neander.hpp"

Neander::Neander(Memoria &memoria) : memoria(memoria), po(memoria, pc), pc(memoria, po) {}

PC::PC(Memoria &memoria, PO &po) : memoria(memoria), po(po) {}

PO::PO(Memoria &memoria, PC &pc) : memoria(memoria), pc(pc) {}

void Neander::fetch_decode_execute()
{
    std::cout << "start\n";
    while ((int)po.RI.get_opcode() != Opcode::HLT)
    {
        po.fetch();
        po.decode();
        po.execute();

        std::cout << "\n\n";
        memoria.print();
        std::cout << "\n\n";
    }
    std::cout << "end\n";
    // po.printstate();
}

void PO::reset()
{
    std::cout << "\n\n\t\t>>> RESETING <<<\n\n";
    AC = 0;
    REM = 0;
    RDM = 0;
    RI = Instrucao();
    PO::pc.carga_pc(0);
}

void PO::fetch()
{
    std::cout << "\n                 >>> INICIANDO CICLO DE BUSCA <<<                 \n";

    std::cout << "\tPC = " << (int)pc.get_pc() << '\n';

    REM = pc.get_pc(); ///[!] O endereço de memória atual é o valor do contador de programa.
    std::cout << "\tREM <- PC\t; REM = " << (int)REM << '\n';

    RDM = memoria.ler(REM); ///[!] Lê o valor da memória no endereço de REM.
    std::cout << "\tRDM <- MEM(REM)\t; RDM = " << (int)RDM << '\n';

    pc.incrementa_pc(); ///[!] Incrementa o contador de programa (avança para o próximo endereço de instrução).
    std::cout << "\tPC++" << "\t; Incremento do contador de programa\n";

    pc.incrementa_cc(); ///[!] Incrementa o contador de ciclos.
    std::cout << "\tCC++" << "\t; Incremento do contador de ciclo\n\n";
}

void PO::decode()
{
    std::cout << "\n             >>> INICIANDO CICLO DE DECODIFICAÇÃO <<<             \n";

    RI = Instrucao::from_byte(RDM); ///[!] Decodifica a instrução lida.
    std::cout << "\tRI <- decode(" << (int)RDM << ")\n";
    std::cout << "\tRI = " << (int)RI.get_opcode() << " " << (int)RI.get_endereco() << "\t; <opcode> <address>\n";

    pc.incrementa_cc(); ///[!] Incrementa o contador de ciclos.
    std::cout << "\tCC++" << "\t; Incremento do contador de ciclo\n\n";
}

void PO::execute()
{
    std::cout << "\n               >>> INICIANDO CICLO DE EXECUÇÃO <<<                \n";
    REM = RI.get_endereco();
    switch (RI.get_opcode())
    {
    case Opcode::NOP:
        ///[!] Nenhuma operação.
        std::cout << "\tNOP\n";
        break;
    case Opcode::STA_END:
        std::cout << "\tSTA " << (int)REM << '\n';
        STA(); ///[!] Chama a operação STA.
        break;
    case Opcode::LDA_END:
        std::cout << "\tLDA " << (int)REM << '\n';
        LDA(); ///[!] Chama a operação LDA.
        break;
    case Opcode::ADD_END:
        std::cout << "\tADD " << (int)REM << '\n';
        ADD(); ///[!] Chama a operação ADD.
        break;
    case Opcode::AND_END:
        std::cout << "\tAND " << (int)REM << '\n';
        AND(); ///[!] Chama a operação AND.
        break;
    case Opcode::OR_END:
        std::cout << "\tOR " << (int)REM << '\n';
        OR(); ///[!] Chama a operação OR.
        break;
    case Opcode::NOT:
        std::cout << "\tNOT\n";
        NOT(); ///[!] Chama a operação NOT.
        break;
    case Opcode::JMP_END:
        std::cout << "\tJPM " << (int)REM << '\n';
        JMP(); ///[!] Chama a operação JMP.
        break;
    case Opcode::JN_END:
        std::cout << "\tJN " << (int)REM << '\n';
        JN(); ///[!] Chama a operação JN.
        break;
    case Opcode::JZ_END:
        std::cout << "\tJZ " << (int)REM << '\n';
        JZ(); ///[!] Chama a operação JZ.
        break;
    case Opcode::MUX:
        // MUX(); ///[!] Chama a operação do multiplexador com controle fixo.
        break;
    default:
        ///[!] Caso padrão é HALT (não há ação).
        std::cout << "\tHLT 0\n\n";
        break;
    }
}

void PO::STA()
{
    memoria.escreve(REM, AC); ///[!] Armazena o valor do AC no endereço REM de memória.
    std::cout << "\t\tMEM(REM) <- AC\t; MEM(" << (int)REM << ") = " << (int)AC << '\n';
}

void PO::LDA()
{
    AC = memoria.ler(REM); ///[!] Carrega o valor da memória em REM no AC.
    std::cout << "\t\tAC <- MEM(REM)\t; AC = " << (int)AC << '\n';
}

void PO::ADD()
{
    RDM = memoria.ler(REM);
    std::cout << "\t\tRDM <- MEM(REM)\t; RDM = " << (int)RDM << '\n';

    AC = ula.sum_operation(AC, RDM); ///[!] Soma o valor da memória em RDM com o AC.
    std::cout << "\t\tAC <- AC + RDM\t; AC = " << (int)AC << '\n';

    pc.flag = ula.get_flag();
    std::cout << "\t\tflag <- " << (pc.flag == 0 ? 'N' : 'Z') << '\n';
}

void PO::AND()
{
    RDM = memoria.ler(REM);
    std::cout << "\t\tRDM <- MEM(REM)\t; RDM = " << (int)RDM << '\n';

    AC = ula.and_operation(AC, RDM); ///[!] Opera AND entre AC e memória.
    std::cout << "\t\tAC <- AC and MEM(RDM)\t; AC = " << (int)AC << '\n';

    pc.flag = ula.get_flag();
    std::cout << "\t\tflag <- " << (pc.flag == 0 ? 'N' : 'Z') << '\n';
}

void PO::OR()
{
    RDM = memoria.ler(REM);
    std::cout << "\t\tRDM <- MEM(REM)\t; RDM = " << (int)RDM << '\n';

    AC = ula.or_operation(AC, RDM); ///[!] Opera OR entre AC e memória.
    std::cout << "\t\tAC <- AC or RDM\t; AC = " << (int)AC << '\n';

    pc.flag = ula.get_flag();
    std::cout << "\t\tflag <- " << (pc.flag == 0 ? 'N' : 'Z') << '\n';
}

void PO::NOT()
{
    std::cout << "\t\tAC <- ~AC\t";
    AC = ula.not_operation(AC); ///[!] Inverte os bits do AC.
    std::cout << "; AC = " << (int)AC << '\n';

    pc.flag = ula.get_flag();
    std::cout << "\t\tflag <- " << (pc.flag == 0 ? 'N' : 'Z') << '\n';
}

void PO::JMP()
{
    PO::pc.carga_pc(REM); ///[!] Desvia para o endereço indicado pela instrução.
    std::cout << "\t\tPC <- REM\t; PC = " << (int)REM << '\n';
}

void PO::JN()
{
    if (AC & 0x80) ///[!] Se AC for negativo (bit de sinal 1), realiza o salto.
    {
        PO::pc.carga_pc(REM);
        std::cout << "\t\tPC <- REM\t; PC = " << (int)REM << '\n';
    }
}

void PO::JZ()
{
    if (AC == 0) ///[!] Se AC for zero, realiza o salto.
    {
        PO::pc.carga_pc(REM);
        std::cout << "\t\tPC <- REM\t; PC = " << (int)REM << '\n';
    }
}

#endif