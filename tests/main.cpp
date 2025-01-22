#include <iostream>
#include <fstream>

#include "../inc/neander/Neander.hpp"
// #include "../inc/cesar/cesar.h"
// #include "../inc/ramses/ramses.h"

using str = std::string;

enum ProcessorType
{
  NEANDER,
  CESAR,
  RAMSES,
  INVALID
};

// Function to select the processor
ProcessorType select_p()
{
  str choice{};
  std::cout << "Select the processor you want to execute (neander, cesar, ramses): ";
  std::cin >> choice;

  if (choice == "neander" || choice == "NEANDER")
  {
    return NEANDER;
  }
  else if (choice == "cesar" || choice == "CESAR")
  {
    return CESAR;
  }
  else if (choice == "ramses" || choice == "RAMSES")
  {
    return RAMSES;
  }
  else
  {
    return INVALID;
  }
}

void load_memory_data(Memoria &memoria, const str &data_file)
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

void load_memory_instructions(Memoria &memoria, const std::string &instructions_file)
{
  std::ifstream infile(instructions_file);
  int dataAddress;
  std::string opcode;
  std::vector<Instrucao> programa;
  while (infile >> opcode >> dataAddress)
  {
    std::cout << "Escrevendo " << opcode << " mirando no endereço " << dataAddress << std::endl;
    if (opcode == "NOP")
    {
      programa.push_back(Instrucao(Opcode::NOP, dataAddress));
    }
    else if (opcode == "STA")
    {
      programa.push_back(Instrucao(Opcode::STA_END, dataAddress));
    }
    else if (opcode == "LDA")
    {
      programa.push_back(Instrucao(Opcode::LDA_END, dataAddress));
    }
    else if (opcode == "ADD")
    {
      programa.push_back(Instrucao(Opcode::ADD_END, dataAddress));
    }
    else if (opcode == "AND")
    {
      programa.push_back(Instrucao(Opcode::AND_END, dataAddress));
    }
    else if (opcode == "OR")
    {
      programa.push_back(Instrucao(Opcode::OR_END, dataAddress));
    }
    else if (opcode == "NOT")
    {
      programa.push_back(Instrucao(Opcode::NOT, dataAddress));
    }
    else if (opcode == "JMP")
    {
      programa.push_back(Instrucao(Opcode::JMP_END, dataAddress));
    }
    else if (opcode == "JN")
    {
      programa.push_back(Instrucao(Opcode::JN_END, dataAddress));
    }
    else if (opcode == "JZ")
    {
      programa.push_back(Instrucao(Opcode::JZ_END, dataAddress));
    }
    else if (opcode == "HLT")
    {
      programa.push_back(Instrucao(Opcode::HLT, dataAddress));
    }
    else if (opcode == "MUX")
    {
      programa.push_back(Instrucao(Opcode::MUX, dataAddress));
    }
  }

  memoria.carrega(programa);
}

int main(int argc, char const *argv[])
{
  ProcessorType processor = select_p();
  if (processor == INVALID)
  {
    std::cerr << "Invalid Processor" << std::endl;
    return 1;
  }

  std::string data_file{argv[1]}, instructions_file{argv[2]};

  Memoria memoria;
  load_memory_data(memoria, data_file);
  load_memory_instructions(memoria, instructions_file);

  auto start = std::chrono::high_resolution_clock::now();

  switch (processor)
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
  outfile << "Processor: " << (processor == CESAR ? "Cesar" : processor == NEANDER ? "Neander" : "Ramses") << std::endl;
  outfile << "Execution time: " << cycles << " cycles" << std::endl;
  outfile.close();

  return 0;
}
