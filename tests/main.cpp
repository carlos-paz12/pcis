#include <iostream>

#include "../inc/neander/Instrucao.hpp"
#include "../inc/neander/Opcode.hpp"
#include "../inc/neander/Memoria.hpp"
#include "../inc/neander/Neander.hpp"

int main()
{
  Memoria memoria;
  Neander processador(memoria);

  memoria.write(5, 10);
  memoria.write(6, 20);

  memoria.write(0, Instrucao(Opcode::LDA_END, 5).to_uint8()); // AC = 10
  memoria.write(1, Instrucao(Opcode::ADD_END, 6).to_uint8()); // AC = AC + 20 = 30
  memoria.write(2, Instrucao(Opcode::STA_END, 7).to_uint8()); // MEM(7) = 30
  memoria.write(3, Instrucao(Opcode::HLT, 0).to_uint8()); //END

  std::cout << "Memória no endereço 5: " << (int)memoria.read(5) << std::endl;
  std::cout << "Memória no endereço 6: " << (int)memoria.read(6) << std::endl;
  std::cout << "Memória no endereço 7: " << (int)memoria.read(7) << std::endl;

  processador.fetch_decode_execute();

  std::cout << "Memória no endereço 5: " << (int)memoria.read(5) << std::endl;
  std::cout << "Memória no endereço 6: " << (int)memoria.read(6) << std::endl;
  std::cout << "Memória no endereço 7: " << (int)memoria.read(7) << std::endl;

  return 0;
}
