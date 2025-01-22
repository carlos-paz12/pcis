#ifndef MEMORIA_CPP
#define MEMORIA_CPP

#include "../../inc/neander/Memoria.hpp"

byte Memoria::ler(byte end) const
{
  if (end >= dados.size())
    throw std::out_of_range("Leitura de memória fora do range."); ///[!] Endereço inválido.
  return dados[end];                                              // Retorna o valor armazenado no endereço
}

void Memoria::escreve(byte end, byte val)
{

  if (end >= dados.size())
    throw std::out_of_range("Escrita de memória fora do range."); ///[!] Endereço inválido.
  dados[end] = val;
}

void Memoria::carrega(const std::vector<Instrucao> &programa)
{
  if (programa.size() > dados.size())
    throw std::out_of_range("Memória insuficiente para carregar programa."); ///[!] Memória insuficiente.

  ///[!] Carrega cada instrução como um byte único na memória.
  for (size_t i{0}; i < programa.size(); ++i)
    escreve(i, programa[i].to_byte()); ///[!] Converte a instrução para byte e escreve na memória.
}

void Memoria::print()
{
  std::cout << "                    >>> ESTADO DA MEMÓRIA <<<                    \n";

 
  for (std::size_t i = 0; i < dados.size(); ++i)
  {
    std::cout << "[" << std::setw(3) << std::right << i << " | " << std::setw(3) << std::left << (int)dados[i] << "]";

    // Verifica se deve adicionar vírgula ou quebra de linha
    if (i % 6 == 5)
      std::cout << ", \n"; // Quebra de linha após 6 elementos
    else if (i != dados.size() - 1)
      std::cout << ", "; // Adiciona vírgula entre os elementos
  }
  std::cout << "\n";
}

#endif /// MEMORIA_CPP