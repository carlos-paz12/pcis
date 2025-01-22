#ifndef RAMSES_CPP
#define RAMSES_CPP

#include "../../inc/ramses/ramses.h"

///=======================================///
///         Implementação de Ramses       ///
///=======================================///

Ramses::Ramses(Memoria &memoria)
    : memoria(memoria), po(memoria, pc), pc(memoria, po) {}

unsigned char Ramses::add8Bits(unsigned char a, unsigned char b) {
  return a + b;
}

unsigned short Ramses::add16Bits(unsigned short a, unsigned short b) {
  return a + b;
}

unsigned char Ramses::subtract8Bits(unsigned char a, unsigned char b) {
  return a - b;
}

unsigned char Ramses::maxValue(unsigned char *array, int size) {
  unsigned char max = array[0];
  for (int i = 1; i < size; i++) {
    if (array[i] > max) {
      max = array[i];
    }
  }
  return max;
}

unsigned short Ramses::callAdd16Bits(unsigned short a, unsigned short b) {
  return add16Bits(a, b);
}

void Ramses::fetch_decode_execute() {
  po.fetch();
  po.decode();
  po.execute();
}

void Ramses::print() { po.printstate(); }

///=======================================///
///         Implementação de PC           ///
///=======================================///

PC_ramses::PC_ramses(Memoria &memoria, PO_ramses &po) : memoria(memoria), po(po) {}

unsigned char PC_ramses::get_pc() { return pc; }

unsigned char PC_ramses::incrementa_pc() { return ++pc; }

unsigned char PC_ramses::get_cc() { return cc; }

unsigned char PC_ramses::incrementa_cc() { return ++cc; }

///=======================================///
///      Implementação da Parte Operativa ///
///=======================================///

PO_ramses::PO_ramses(Memoria &memoria, PC_ramses &pc) : memoria(memoria), pc(pc) {}

void PO_ramses::printstate() {
  std::cout << "+---------------------------+" << std::endl;
  std::cout << "|         CPU STATE         |" << std::endl;
  std::cout << "+---------------------------+" << std::endl;
  std::cout << "| PC: " << std::setw(24) << (int)pc.get_pc() << " |"
            << std::endl;
  std::cout << "| IR: " << std::setw(24) << RI.get_opcode() << " |"
            << std::endl;
  std::cout << "| AC: " << std::setw(25) << (int)AC << " |" << std::endl;
  std::cout << "+---------------------------+" << std::endl;

  std::cout << "|       Registers:          |" << std::endl;
  for (int i = 0; i < NUM_REGISTERS; ++i) {
    std::cout << "| R" << i << ": " << std::setw(22) << registers[i] << " |"
              << std::endl;
  }
  std::cout << "+---------------------------+" << std::endl;

  std::cout << "|         Memory:           |" << std::endl;
  for (int i = 0; i < 256; ++i) {
    int val_mem = memoria.ler(i);
    std::cout << "| M" << i << ": " << std::setw(22) << val_mem << " |"
              << std::endl;
  }
  std::cout << "+---------------------------+" << std::endl;
}

void PO_ramses::SUB() {
  REM = RI.get_endereco();
  std::cout << "SUB " << (int)REM;
  RDM = memoria.ler(REM);
  AC = ula.sub_operation(AC, RDM);
  std::cout << "AC <- AC - MEM(" << (int)RDM << ")";
}

void PO_ramses::XOR() {
  REM = RI.get_endereco();
  std::cout << "XOR " << (int)REM;
  RDM = memoria.ler(REM);
  AC = ula.xor_operation(AC, RDM);
  std::cout << "AC <- AC XOR MEM(" << (int)RDM << ")";
}

void PO_ramses::SHL() {
  std::cout << "SHL";
  AC = ula.shl_operation(AC);
  std::cout << "AC <- AC << 1";
}

void PO_ramses::SHR() {
  std::cout << "SHR";
  AC = ula.shr_operation(AC);
  std::cout << "AC <- AC >> 1";
}

void PO_ramses::handle_interrupt() {
  std::cout << "Handling interrupt" << std::endl;
  // Save the current state and process the interrupt
}

void PO_ramses::fetch() {
  std::cout << ">>> INICIANDO CICLO DE BUSCA\n";
  REM = pc.get_pc();
  RDM = memoria.ler(REM);
  pc.incrementa_pc();
  pc.incrementa_cc();
}

void PO_ramses::decode() {
  std::cout << ">>> INICIANDO CICLO DE DECODIFICAÇÃO\n";
  RI = Instrucao::from_byte(RDM);
  pc.incrementa_cc();
}

void PO_ramses::ADD16() {
  unsigned short a = memoria.ler(REM);
  unsigned short b = memoria.ler(REM + 1);
  unsigned short result = ula.add16Bits(a, b);
  memoria.escreve(REM + 2, result);
  std::cout << "ADD16: " << a << " + " << b << " = " << result << std::endl;
}

void PO_ramses::CALL_ADD16() {
  unsigned short a = memoria.ler(REM);
  unsigned short b = memoria.ler(REM + 1);
  unsigned short result = ula.add16Bits(a, b);
  memoria.escreve(REM + 2, result);
  std::cout << "CALL_ADD16: Result stored at memory(" << (REM + 2)
            << ") = " << result << std::endl;
}

void PO_ramses::MAX_ARRAY() {
  unsigned char max = memoria.ler(REM);
  for (int i = 1; i < 32; i++) {
    unsigned char val = memoria.ler(REM + i);
    if (val > max) {
      max = val;
    }
  }
  memoria.escreve(REM + 32, max);
  std::cout << "MAX_ARRAY: Max value = " << (int)max << " stored at memory("
            << (REM + 32) << ")" << std::endl;
}

void PO_ramses::execute() {
  switch (RI.get_opcode()) {
  case Opcode::NOP:
    break;
  case Opcode::STA_END:
    break;
  case Opcode::LDA_END:
    break;
  case Opcode::ADD_END:
    break;
  case Opcode::AND_END:
    break;
  case Opcode::OR_END:
    break;
  case Opcode::NOT:
    break;
  case Opcode::JMP_END:
    break;
  case Opcode::JN_END:
    break;
  case Opcode::JZ_END:
    break;
  case Opcode::HLT:
    std::cout << "Execução interrompida (HLT)" << std::endl;
    break;
  case Opcode::MUX:
    break;
  default:
    std::cout << "Opcode desconhecido: HALT" << std::endl;
    break;
  }
}

#endif // RAMSES_CPP
