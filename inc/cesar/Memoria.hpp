#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <stdexcept>
#include <vector>

#include "Instrucao.hpp"

class Memoria {
private:
  std::vector<int> dados;

public:
  Memoria() : dados(256) { /* empty */ }

  /**
   * Lê o valor armazenado em um endereço específico da memória.
   *
   * Este método retorna o valor armazenado em um endereço fornecido. Caso o
   * endereço esteja fora do intervalo válido, uma exceção `std::out_of_range` é
   * lançada.
   *
   * @param end O endereço na memória de onde o valor será lido (0-255).
   *
   * @return O valor armazenado no endereço especificado.
   *
   * @throws std::out_of_range Se o endereço fornecido for inválido.
   */
  int read(int end) const;

  /**
   * Escreve um valor em um endereço específico da memória.
   *
   * Este método armazena o valor fornecido em um endereço especificado na
   * memória. Ele é utilizado para atualizar o conteúdo da memória em operações
   * como `STA` ou ao inicializar a memória com dados.
   *
   * @param end O endereço na memória onde o valor será armazenado (0-255).
   * @param val Valor a ser armazenada na memória.
   */
  void write(int end, int val);

  /**
   * @brief Carrega um programa na memória.
   *
   * Este método recebe um vetor de bytes representando o programa (instruções e
   * dados) e os armazena nos endereços correspondentes da memória, começando do
   * endereço 0.
   *
   * @param programa Um vetor de Instrucao contendo as instruções e dados do
   * programa.
   */
  void load_program(const std::vector<Instrucao> &programa);
};

#endif /// MEMORY_H
