#include <iostream>

#include "../inc/neander/Instrucao.hpp"
#include "../inc/neander/Opcode.hpp"
#include "../inc/neander/Memoria.hpp"
#include "../inc/neander/Neander.hpp"

void soma()
{
  Memoria memoria;
  Neander processador(memoria);

  memoria.write(5, 300);
  memoria.write(6, 20);

  memoria.write(0, Instrucao(Opcode::LDA_END, 5).to_uint8()); // AC = 10
  memoria.write(1, Instrucao(Opcode::ADD_END, 6).to_uint8()); // AC = AC + 20 = 30
  memoria.write(2, Instrucao(Opcode::STA_END, 7).to_uint8()); // MEM(7) = 30
  memoria.write(3, Instrucao(Opcode::HLT, 0).to_uint8());     // END

  std::cout << "Memória no endereço 5: " << (int)memoria.read(5) << std::endl;
  std::cout << "Memória no endereço 6: " << (int)memoria.read(6) << std::endl;
  std::cout << "Memória no endereço 7: " << (int)memoria.read(7) << std::endl;

  processador.fetch_decode_execute();

  std::cout << "Memória no endereço 5: " << (int)memoria.read(5) << std::endl;
  std::cout << "Memória no endereço 6: " << (int)memoria.read(6) << std::endl;
  std::cout << "Memória no endereço 7: " << (int)memoria.read(7) << std::endl;
}

void subtrai()
{
  Memoria memoria;
  Neander processador(memoria);

  memoria.write(6, 20);
  memoria.write(7, 10);
  memoria.write(8, 1);

  memoria.write(0, Instrucao(Opcode::LDA_END, 7).to_uint8()); // AC = 20
  memoria.write(1, Instrucao(Opcode::NOT, 0).to_uint8());     // AC = ~AC
  memoria.write(2, Instrucao(Opcode::ADD_END, 8).to_uint8()); // AC = AC + MEM(8)
  memoria.write(3, Instrucao(Opcode::ADD_END, 6).to_uint8()); // AC = AC + MEM(7)
  memoria.write(4, Instrucao(Opcode::STA_END, 9).to_uint8()); // MEM(9) = AC
  memoria.write(5, Instrucao(Opcode::HLT, 0).to_uint8());     // END

  std::cout << "Memória no endereço 6: " << (int)memoria.read(6) << std::endl;
  std::cout << "Memória no endereço 7: " << (int)memoria.read(7) << std::endl;
  std::cout << "Memória no endereço 8: " << (int)memoria.read(8) << std::endl;
  std::cout << "Memória no endereço 9: " << (int)memoria.read(9) << std::endl;

  // print memo
  processador.fetch_decode_execute();
  // print memo
  
  std::cout << "Memória no endereço 6: " << (int)memoria.read(6) << std::endl;
  std::cout << "Memória no endereço 7: " << (int)memoria.read(7) << std::endl;
  std::cout << "Memória no endereço 8: " << (int)memoria.read(8) << std::endl;
  std::cout << "Memória no endereço 9: " << (int)memoria.read(9) << std::endl;
}

int main()
{
  std::cout << "SOMA\n";
  soma();

  std::cout << "\nSUBTRAI\n";
  subtrai();

  return 0;
}
