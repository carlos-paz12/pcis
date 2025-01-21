#ifndef MEMORIA_CPP
#define MEMORIA_CPP

#include "../../inc/neander/Memoria.hpp"

uint8_t Memoria::read(uint8_t end) const {
  if (end >= dados.size())
    throw std::out_of_range(
        "Leitura de memória fora do range."); // Endereço inválido
  return dados[end]; // Retorna o valor armazenado no endereço
}

void Memoria::write(uint8_t end, uint8_t val) {

  if (end >= dados.size())
    throw std::out_of_range(
        "Escrita de memória fora do range."); // Endereço inválido
  dados[end] = val;
}

void Memoria::load_program(const std::vector<Instrucao> &programa) {
  // Carrega cada instrução como um byte único na memória
  for (size_t i = 0; i < programa.size(); ++i)
    // Converte a instrução para uint8_t e escreve na memória
    write(i, programa[i].to_uint8());
}

#endif /// MEMORIA_CPP