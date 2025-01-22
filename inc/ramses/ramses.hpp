#ifndef NEANDER_HPP
#define NEANDER_HPP

#include <bits/stdc++.h>

#include "Opcode.hpp"
#include "Flag.hpp"
#include "Instrucao.hpp"
#include "Memoria.hpp"
#include "ULA.hpp"

class PC;

class PO /// Parte Operativa
{
public:
  Memoria &memoria;
  PC &pc;

  uint8_t AC;   ///!> Registrador acumulador.
  uint8_t REM;  ///!> Registrador que armazena o endereço de uma posição de memória (registrador de endereço de memória)
  uint8_t RDM;  ///!> Registrador que armazena o dado que será lido ou escrito na memória (registrador de dados de memória).
  Instrucao RI; ///!> Registrador que armazena instrução a ser executada (registrador de instruções).

  ULA ula; ///!> Unidade Lógica e Aritmética.

  void STR(); //  <<<<<

  void LDR(); //  <<<<<

  void ADD();

  void AND();

  void OR();

  void NOT();

  void JMP();

  void JN();

  void JZ();

  void reset();

  PO(Memoria &memoria, PC &pc);

  void fetch();

  void decode();

  void execute();

  void printstate();
};

class PC /// Parte de Controle
{
public:
  Memoria &memoria;
  PO &po;

  uint8_t pc; ///!> Registrador que armazena o endereço da próxima instrução a ser executada (contador de programa).
  uint8_t cc; ///!> Registrador que armazena a quantidade de ciclos do processador (contador de ciclos).

  Flag flag; ///!> Flag de controle.

  PC(Memoria &memoria, PO &po);

  uint8_t get_pc()
  {
    return pc;
  }

  uint8_t incrementa_pc()
  {
    return ++pc;
  }

  uint8_t carga_pc(uint8_t val)
  {
    pc = val;
  }

  uint8_t get_cc()
  {
    return ++cc;
  }

  uint8_t incrementa_cc()
  {
    return ++cc;
  }
};

class Neander
{
private:
  Memoria &memoria;
  PO po;
  std::vector<int> registradores; // Adicionando os registradores
  PC pc;

public:
  Neander(Memoria &memoria);

  void fetch_decode_execute();

  void print();
};

#endif /// NEANDER_H
