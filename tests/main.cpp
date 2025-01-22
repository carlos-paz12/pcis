#include <iostream>
#include <fstream>
#include <chrono>
#include <filesystem>

#include "../inc/neander/Neander.hpp"
// #include "../inc/cesar/cesar.h"
// #include "../inc/ramses/ramses.h"

using str = std::string;
using path = std::filesystem::path;

enum Processor
{
  NEANDER,
  CESAR,
  RAMSES,
  OTHER
};

enum Test
{
  SUM_8_BITS,
  SUB_8_BITS,
  SUM_16_BITS,
  SUB_16_BITS,
  MAX_8_BITS,
  MAX_16_BITS,
  INVALID,
  ANOTHER
};

Processor m_processor;
Test m_test;

Processor choice_processor()
{
  std::cout << "Select the processor\n";
  std::cout << "[1] NEANDER\n";
  std::cout << "[2] CESAR\n";
  std::cout << "[3] RAMSES\n";
  std::cout << "[*] QUIT\n";
  std::cout << "-> ";

  int choice{};
  std::cin >> choice;

  switch (choice)
  {
  case 1:
    return NEANDER;
  case 2:
    return CESAR;
  case 3:
    return RAMSES;
  default:
    return OTHER;
  }
}

Test choice_test()
{
  std::cout << "Select the test you want to execute\n";
  std::cout << "[1] SUM 8 BITS\n";
  std::cout << "[2] SUB 8 BITS\n";
  std::cout << "[3] SUM 16 BITS\n";
  std::cout << "[4] SUB 16 BITS\n";
  std::cout << "[5] MAX 8 BITS\n";
  std::cout << "[6] MAX 16 BITS\n";
  std::cout << "[*] QUIT\n";
  std::cout << "-> ";

  int choice{};
  std::cin >> choice;

  switch (choice)
  {
  case 1:
    return SUM_8_BITS;
  case 2:
    return SUB_8_BITS;
  case 3:
    return SUM_16_BITS;
  case 4:
    return SUB_16_BITS;
  case 5:
    return MAX_8_BITS;
  case 6:
    return MAX_16_BITS;
  default:
    return ANOTHER;
  }
}

void load_memory_data(Memoria &memoria, const path &data_file)
{
  std::ifstream infile(data_file);
  int address, value;

  // Carregar os dados na memória
  while (infile >> address >> value)
  {
    std::cout << "Escrevendo " << value << " no endereço " << address << std::endl;
    memoria.escreve(address, value);
  }
}

void load_memory_instructions(Memoria &memoria, const path &instructions_file)
{
  std::ifstream infile(instructions_file);

  // Pergunta CAPZ, a gente atualmente tá imprimindo varias memorias e endereço com valor, ou só no final com tudo já punk.
  ///////////>>>> A CADA INSTRUCAO, NÓS IMPRIMIMOS O STATUS DOS REGISTRADORES, FLAGS E MEMÓRIA
  str opcode;
  int data_address;
  std::vector<Instrucao> programa;

  while (infile >> opcode >> data_address)
  {
    if (opcode == "NOP")
      programa.push_back(Instrucao(Opcode::NOP, data_address));
    else if (opcode == "STA")
      programa.push_back(Instrucao(Opcode::STA_END, data_address));
    else if (opcode == "LDA")
      programa.push_back(Instrucao(Opcode::LDA_END, data_address));
    else if (opcode == "ADD")
      programa.push_back(Instrucao(Opcode::ADD_END, data_address));
    else if (opcode == "AND")
      programa.push_back(Instrucao(Opcode::AND_END, data_address));
    else if (opcode == "OR")
      programa.push_back(Instrucao(Opcode::OR_END, data_address));
    else if (opcode == "NOT")
      programa.push_back(Instrucao(Opcode::NOT, data_address));
    else if (opcode == "JMP")
      programa.push_back(Instrucao(Opcode::JMP_END, data_address));
    else if (opcode == "JN")
      programa.push_back(Instrucao(Opcode::JN_END, data_address));
    else if (opcode == "JZ")
      programa.push_back(Instrucao(Opcode::JZ_END, data_address));
    else if (opcode == "HLT")
      programa.push_back(Instrucao(Opcode::HLT, data_address));
    else if (opcode == "MUX")
      programa.push_back(Instrucao(Opcode::MUX, data_address));
  }

  memoria.carrega(programa);
}

int main(int argc, char const *argv[])
{
  m_processor = choice_processor();

  if (m_processor == OTHER)
  {
    std::cout << "Quit!" << std::endl;
    return 0;
  }

  m_test = choice_test();

  if (m_test == ANOTHER)
  {
    std::cout << "Invalid test selected!" << std::endl;
    return 0;
  }

  // Define the file names based on the selected processor and test
  std::string processor_str = (m_processor == NEANDER)  ? "neander"
                              : (m_processor == CESAR)  ? "cesar"
                              : (m_processor == RAMSES) ? "ramses"
                              : "";
                                            
  std::string test_str = (m_test == SUM_8_BITS)    ? "sum_8_bits"
                         : (m_test == SUB_8_BITS)  ? "sub_8_bits"
                         : (m_test == SUM_16_BITS) ? "sum_16_bits"
                         : (m_test == SUB_16_BITS) ? "sub_16_bits"
                         : (m_test == MAX_8_BITS)  ? "max_8_bits"
                         : (m_test == MAX_16_BITS) ? "max_16_bits"
                         : "";

  path m_path = path(__FILE__).parent_path();
  path data_file = m_path / processor_str / (test_str + "-data.txt");
  path instructions_file = m_path / processor_str / (test_str + "-instructions.txt");

  Memoria memoria;
  load_memory_data(memoria, data_file);
  load_memory_instructions(memoria, instructions_file);

  auto start = std::chrono::high_resolution_clock::now();

  switch (m_processor)
  {
  case NEANDER:
  {
    // Neander processor logic
    std::cout << "+-------------------+\n";
    std::cout << "| Neander Processor |\n";
    std::cout << "+-------------------+\n";

    Neander neanderProcessor(memoria);       // Initialize Neander processor
    neanderProcessor.fetch_decode_execute(); // Call its execution function

    break;
  }
  case CESAR:
    // Implement CESAR processor logic here
    std::cout << "\nCesar Processor: (Not yet implemented)" << std::endl;
    break;

  case RAMSES:
    // Implement RAMSES processor logic here
    std::cout << "\nRamses Processor: (Not yet implemented)" << std::endl;
    break;

  default:
    std::cerr << "Invalid Processor" << std::endl;
    return 1;
  }

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  int cycles = static_cast<int>(elapsed.count() * 1e6); // Calculate time in microseconds

  // Output results to a file
  std::ofstream outfile("data/time_results.txt");
  outfile << "Processor: " << processor_str << std::endl;
  outfile << "Execution time: " << cycles << " cycles" << std::endl;
  outfile.close();

  return 0;
}
