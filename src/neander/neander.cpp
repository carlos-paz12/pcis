#ifndef NEANDER_CPP
#define NEANDER_CPP

#include "../../inc/neander/Neander.hpp"

Neander::Neander(Memoria& memoria) :  memoria(memoria), ciclos(0), AC(0), REM(0), PC(0), flag(FLAG_Z) {}

void Neander::fetch() {
  REM = PC; ///[!] Obtém o endereço de memória atual do contador de programa (PC).
  RDM = memoria.read(REM); ///[!] Lê o valor da memória no endereço armazenado em REM.
  RI = Instrucao::from_uint8(RDM); ///[!] Decodifica a instrução lida.
  ++PC; ///[!] Incrementa o contador de programa para a próxima instrução.
  ++ciclos; ///[!] Incrementa o contador de ciclos na execução da instrução.
  decode(); ///[!] Chama a função decode para processar a instrução.
}

void Neander::decode() {
  ++ciclos; ///[!] Incrementa o contador de ciclos na execução da instrução.

  switch (RI.get_opcode()) {
  case Opcode::NOP:
    /* Nada */
    break;
  case Opcode::STA_END:
    STA(RI.get_endereco());
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
  default: ///[!] Opcode padrão é HLT.
    break; ///[!] Fim de ciclo.
  }
}

void Neander::execute(void (Neander::*f)(uint8_t &end)) {
  ++ciclos; ///[!] Incrementa o contador de ciclos na execução da instrução.

  auto end = RI.get_endereco();
  (this->*f)(end); ///[!] Chama o método de instância no contexto
                                 ///da classe Neander.

  ///[!] Atualiza as flags conforme o valor de AC
  if (AC & 0x80) ///[!] Se o bit mais significativo de AC for 1, o número é
                 ///negativo (complemento de dois)
  {
    flag = Flag::FLAG_N; ///[!] Flag N ativada se o AC for negativo.
  } else if (AC == 0) {
    flag = Flag::FLAG_Z; ///[!] Flag Z ativada se o AC for zero.
  }
}

void Neander::STA(uint8_t end) {
  RDM = end;
  memoria.write(end, AC); ///[!] Armazena o valor do AC no endereço da memória.
}

void Neander::LDA(uint8_t &end) {
  AC = memoria.read(end); ///[!] Carrega o valor da memória no AC.
}

void Neander::ADD(uint8_t &end) {
  AC = ula.sum(
      AC, memoria.read(end)); ///[!] Soma o valor armazenado em memória com AC.
}

void Neander::SUB(uint8_t &end) {
  AC = ula.sub(
      AC,
      memoria.read(end)); ///[!] Subtrai o valor armazenado em memória de AC.
}

void Neander::AND(uint8_t &end) {
  AC = ula.and_operation(
      AC, memoria.read(
              end)); ///[!] Opera AND bit a bit entre AC e valor da memória.
}

void Neander::OR(uint8_t &end) {
  AC = ula.or_operation(
      AC,
      memoria.read(end)); ///[!] Opera OR bit a bit entre AC e valor da memória.
}

void Neander::NOT([[maybe_unused]] uint8_t &end) {
  AC = ula.not_operation(AC); ///[!] Inverte os bits de AC.
}

void Neander::JMP(uint8_t &end) {
  PC = end; ///[!] Desvia incondicionalmente para o endereço "end".
}

void Neander::JN(uint8_t &end) {
  if (AC & 0x80) ///[!] Se AC for negativo (bit de sinal é 1), realiza o salto.
    PC = end;    ///[!] Desvia para o endereço "end".
}

void Neander::JZ(uint8_t &end) {
  if (AC == 0) ///[!] Se AC for zero, realiza o salto.
    PC = end;  ///[!] Desvia para o endereço "end".
}

void Neander::reset() {
  AC = 0;
  REM = 0;
  PC = 0;
  flag = FLAG_Z;
  ciclos = 0;
}

void Neander::fetch_decode_execute() {
  while (true) {
    fetch();

    if (RI.get_opcode() == Opcode::HLT)
      break;
  }
}

std::string Neander::to_string() {
  // TODO
}

#endif /// NEANDER_CPP