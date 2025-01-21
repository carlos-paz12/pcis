#ifndef MEMORIA_CPP
#define MEMORIA_CPP

#include "../../inc/neander/Memoria.hpp"

byte Memoria::ler(byte end) const {
  if (end >= dados.size())
    throw std::out_of_range("Leitura de memória fora do range."); ///[!] Endereço inválido.
  return dados[end]; // Retorna o valor armazenado no endereço
}

void Memoria::escreve(byte end, byte val) {

  if (end >= dados.size())
    throw std::out_of_range("Escrita de memória fora do range."); ///[!] Endereço inválido.
  dados[end] = val;
}

void Memoria::carrega(const std::vector<Instrucao> &programa) {
  if (programa.size() > dados.size())
    throw std::out_of_range("Memória insuficiente para carregar programa."); ///[!] Memória insuficiente.
  
  ///[!] Carrega cada instrução como um byte único na memória.
  for (size_t i{0}; i < programa.size(); ++i)
    if (not dados[i]) ///[!] Inserir a partir do primeiro índice livre na memória.
      escreve(i, programa[i].to_byte()); ///[!] Converte a instrução para byte e escreve na memória.
}

#endif /// MEMORIA_CPP