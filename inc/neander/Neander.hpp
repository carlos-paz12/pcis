#ifndef NEANDER_HPP
#define NEANDER_HPP

#include <bits/stdc++.h>

#include "Opcode.hpp"
#include "Flag.hpp"
#include "Instrucao.hpp"
#include "Memoria.hpp"
#include "ULA.hpp"

using byte = std::uint8_t;

class PC;

class PO /// Parte Operativa
{
public:
  Memoria &memoria;
  PC &pc;

  byte AC;   ///!> Registrador acumulador.
  byte REM;  ///!> Registrador que armazena o endereço de uma posição de memória (registrador de endereço de memória)
  byte RDM;  ///!> Registrador que armazena o dado que será lido ou escrito na memória (registrador de dados de memória).
  Instrucao RI; ///!> Registrador que armazena instrução a ser executada (registrador de instruções).

  ULA ula; ///!> Unidade Lógica e Aritmética.

  PO(Memoria &memoria, PC &pc);

  void fetch();

  void decode();

  void execute();

  void STA();

  void LDA();

  void ADD();

  void AND();

  void OR();

  void NOT();

  void JMP();

  void JN();

  void JZ();

  void reset();
};

class PC /// Parte de Controle
{
public:
  Memoria &memoria;
  PO &po;

  byte pc; ///!> Registrador que armazena o endereço da próxima instrução a ser executada (contador de programa).
  byte cc; ///!> Registrador que armazena a quantidade de ciclos do processador (contador de ciclos).

  Flag flag; ///!> Flag de controle.

  PC(Memoria &memoria, PO &po);

  byte get_pc()
  {
    return pc;
  }

  byte incrementa_pc()
  {
    return ++pc;
  }

  byte carga_pc(uint8_t val)
  {
    pc = val;
  }

  byte get_cc()
  {
    return ++cc;
  }

  byte incrementa_cc()
  {
    return ++cc;
  }
};

class Neander
{
private:
  Memoria &memoria;
  PO po;
  PC pc;

public:
  Neander(Memoria &memoria);

  void fetch_decode_execute();
};

#endif /// NEANDER_H
