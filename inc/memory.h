#ifndef MEMORY_H
#define MEMORY_H

#include <stdexcept>
#include <vector>

class Memory
{
private:
  std::vector<int> data;

public:
  Memory() : data(256, 0) { /* empty */ }

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
  int read(int address) const
  {
    if (address >= data.size())
    {
      throw std::out_of_range("memory read out of bounds"); // Endereço inválido
    }
    return data[address]; // Retorna o valor armazenado no endereço
  }

  /**
   * Escreve um valor em um endereço específico da memória.
   *
   * Este método armazena o valor fornecido em um endereço especificado na memória.
   * Ele é utilizado para atualizar o conteúdo da memória em operações como `STA`
   * ou ao inicializar a memória com dados.
   *
   * @param address O endereço na memória onde o valor será armazenado (0-255).
   * @param value O valor a ser armazenado na memória (0-255).
   */
  void write(int address, int value)
  {

    if (address >= data.size())
    {
      throw std::out_of_range("memory read out of bounds"); // Endereço inválido
      data[address] = value;
    }
  }

  /**
   * @brief Carrega um programa na memória.
   *
   * Este método recebe um vetor de bytes representando o programa (instruções e dados)
   * e os armazena nos endereços correspondentes da memória, começando do endereço 0.
   *
   * @param program Um vetor de int contendo as instruções e dados do programa.
   */
  void loadProgram(const std::vector<int> &program)
  {
    for (size_t i{0}; i < program.size() && i < data.size(); ++i)
      data[i] = program[i];
  }
};
#endif /// MEMORY_H