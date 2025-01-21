#ifndef RAMSES_H
#define RAMSES_H

#include "Memoria.hpp"
#include "Instrucao.hpp"
#include "ULA.hpp"

class PC; // Declaração antecipada da classe PC

class PO { // Parte Operativa
public:
    Memoria &memoria;
    PC &pc;

    unsigned char AC;   // Registrador acumulador
    unsigned char REM;  // Registrador de endereço de memória
    unsigned char RDM;  // Registrador de dados de memória
    Instrucao RI;       // Registrador de instrução

    ULA ula; // Unidade Lógica e Aritmética

    static const int NUM_REGISTERS = 8;
    unsigned char registers[NUM_REGISTERS] = {0}; // Registradores gerais

    PO(Memoria &memoria, PC &pc);

    void printstate();
    void SUB();
    void XOR();
    void SHL();
    void SHR();
    void handle_interrupt();
    void fetch();
    void decode();
    void execute();

    void ADD16();         // Soma dois valores de 16 bits
    void CALL_ADD16();    // Chama a sub-rotina para soma de 16 bits
    void MAX_ARRAY();     // Determina o maior valor em um vetor de 32 posições
};

class PC { // Parte de Controle
public:
    Memoria &memoria;
    PO &po;

    unsigned char pc; // Contador de programa
    unsigned char cc; // Contador de ciclos

    PC(Memoria &memoria, PO &po);

    unsigned char get_pc();
    unsigned char incrementa_pc();
    void carga_pc(unsigned char val);
    unsigned char get_cc();
    unsigned char incrementa_cc();
};

class Ramses {
private:
    Memoria &memoria;
    PO po;
    PC pc;

public:
    Ramses(Memoria &memoria);

    void fetch_decode_execute();
    void print();
    unsigned char add8Bits(unsigned char a, unsigned char b);
    unsigned short add16Bits(unsigned short a, unsigned short b);
    unsigned char subtract8Bits(unsigned char a, unsigned char b);
    unsigned char Ramses::maxValue(unsigned char *array, int size);
    unsigned short Ramses::callAdd16Bits(unsigned short a, unsigned short b);
};

#endif // RAMSES_H
