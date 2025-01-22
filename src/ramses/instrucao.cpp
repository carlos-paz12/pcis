#ifndef INSTRUCAO_CPP
#define INSTRUCAO_CPP

#include "../../inc/neander/Instrucao.hpp"

Instrucao::Instrucao(byte opcode, byte endereco)
    : opcode(opcode), endereco(endereco) { /* empty */ }

Instrucao::Instrucao(const Instrucao &other)
    : opcode(other.opcode), endereco(other.endereco) { /* empty */ }

Instrucao &Instrucao::operator=(const Instrucao &other) {
  if (this != &other) {
    opcode = other.opcode;
    endereco = other.endereco;
  }
  return (*this);
}

byte Instrucao::get_opcode() { return opcode; }

byte Instrucao::get_endereco() { return endereco; }

byte Instrucao::to_byte() const { return (opcode << 4) | (endereco & 0x0F); }

Instrucao Instrucao::from_byte(byte encoded) {
  byte opcode = (encoded >> 4) & 0x0F;
  byte endereco = encoded & 0x0F;

  return Instrucao(opcode, endereco);
}

#endif /// INSTRUCAO_CPP