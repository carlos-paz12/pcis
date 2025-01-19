#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint> /// std::uint8_t
#include <stdexcept>
#include <vector>

#include "Instrucao.hpp"

class Memory
{
private:
  std::vector<std::uint8_t> data;

public:
  Memory() : data(256) { /* empty */ }

  /**
   * Lê o valor armazenado em um endereço específico da memória.
   *
   * Este método retorna o valor armazenado em um endereço fornecido. Caso o endereço
   * esteja fora do intervalo válido, uma exceção `std::out_of_range` é lançada.
   *
   * @param address O endereço na memória de onde o valor será lido (0-255).
   * @return O valor armazenado no endereço especificado.
   * @throws std::out_of_range Se o endereço fornecido for inválido.
   */
  uint8_t read(uint8_t address) const
  {
    if (address >= data.size())
      throw std::out_of_range("memory read out of bounds"); // Endereço inválido
    return data[address];                                   // Retorna o valor armazenado no endereço
  }

  /**
   * Escreve um valor em um endereço específico da memória.
   *
   * Este método armazena o valor fornecido em um endereço especificado na memória.
   * Ele é utilizado para atualizar o conteúdo da memória em operações como `STA`
   * ou ao inicializar a memória com dados.
   *
   * @param address O endereço na memória onde o valor será armazenado (0-255).
   * @param val Valor a ser armazenada na memória.
   */
  void write(uint8_t address, uint8_t val)
  {

    if (address >= data.size())
    {
      throw std::out_of_range("memory write out of bounds"); // Endereço inválido
    }
    data[address] = val;
  }

  /**
   * @brief Carrega um programa na memória.
   *
   * Este método recebe um vetor de bytes representando o programa (instruções e dados)
   * e os armazena nos endereços correspondentes da memória, começando do endereço 0.
   *
   * @param program Um vetor de Instrucao contendo as instruções e dados do programa.
   */
  void load_program(const std::vector<Instrucao> &program)
  {
    // Carrega cada instrução como um byte único na memória
    for (size_t i = 0; i < program.size(); ++i)
    {
      // Converte a instrução para uint8_t e escreve na memória
      write(i, program[i].toUint8());
    }
  }
};

#endif /// MEMORY_H
