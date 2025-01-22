#ifndef RAMSES_CPP
#define RAMSES_CPP

#include "../../inc/ramses/ramses.h"

Ramses::Ramses(Memoria &memoria) : memoria(memoria), po(memoria, pc), pc(memoria, po) {}

PC::PC(Memoria &memoria, PO &po) : memoria(memoria), po(po) {}

PO::PO(Memoria &memoria, PC &pc) : memoria(memoria), pc(pc) {}

void Ramses::fetch_decode_execute()
{
  po.fetch();
  po.decode();
  po.execute();
}

void Ramses::print()
{
  po.printstate();
}

///=======================================///
/// Implementação da Parte Operativa (PO) ///
///=======================================///

void PO::printstate()
{
    std::cout << "+---------------------------+" << std::endl;
    std::cout << "|         CPU STATE         |" << std::endl;
    std::cout << "+---------------------------+" << std::endl;
    std::cout << "| PC: " << std::setw(24) << (int)pc.get_pc() << " |" << std::endl;
    std::cout << "| IR: " << std::setw(24) << RI.get_opcode() << " |" << std::endl;
    std::cout << "| Flags: " << std::setw(20) << std::bitset<8>(flags) << " |" << std::endl;
    std::cout << "| AC: " << std::setw(25) << (int)AC << " |" << std::endl;
    std::cout << "+---------------------------+" << std::endl;

    std::cout << "|       Registers:          |" << std::endl;
    for (int i = 0; i < registradores.size(); ++i)
    {
        std::cout << "| R" << i << ": " << std::setw(22) << registradores[i] << " |" << std::endl;
    }
    std::cout << "+---------------------------+" << std::endl;

    std::cout << "|         Memory:           |" << std::endl;
    for (int i = 0; i < 256; ++i)
    {
        std::cout << "| M" << i << ": " << std::setw(22) << (int)memoria.ler(i) << " |" << std::endl;
    }
    std::cout << "+---------------------------+" << std::endl;

    std::cout << "| ULA Operation: " << ula_operation << " |" << std::endl;
    std::cout << "+---------------------------+" << std::endl;
}
void PO::SUB()
{
    REM = RI.get_endereco();
    std::cout << "SUB " << (int)REM;
    RDM = memoria.ler(REM);
    AC = ula.sub_operation(AC, RDM);
    std::cout << "AC <- AC - MEM(" << (int)RDM << ")";
}

void PO::XOR()
{
    REM = RI.get_endereco();
    std::cout << "XOR " << (int)REM;
    RDM = memoria.ler(REM);
    AC = ula.xor_operation(AC, RDM);
    std::cout << "AC <- AC XOR MEM(" << (int)RDM << ")";
}

void PO::SHL()
{
    std::cout << "SHL";
    AC = ula.shl_operation(AC);
    std::cout << "AC <- AC << 1";
}

void PO::SHR()
{
    std::cout << "SHR";
    AC = ula.shr_operation(AC);
    std::cout << "AC <- AC >> 1";
}

void PO::handle_interrupt()
{
    std::cout << "Handling interrupt" << std::endl;
    // Salvar estado atual (PC, registradores, etc.)
    // Processar rotina de interrupção
    // Restaurar estado salvo
}

void PO::fetch()
{
    std::cout << ">>> INICIANDO CICLO DE BUSCA\n";
    REM = pc.get_pc();
    RDM = memoria.ler(REM);
    pc.incrementa_pc();
    pc.incrementa_cc();
}

void PO::decode()
{
    std::cout << ">>> INICIANDO CICLO DE DECODIFICAÇÃO\n";
    RI = Instrucao::from_byte(RDM);
    pc.incrementa_cc();
}

// Implementation of the method to add two 8-bit variables
unsigned char Ramses::add8Bits(unsigned char a, unsigned char b) {
  return a + b;
}

// Implementation of the method to add two 16-bit variables
unsigned short Ramses::add16Bits(unsigned short a, unsigned short b) {
  return a + b;
}

// Implementation of the method to subtract two 8-bit variables
unsigned char Ramses::subtract8Bits(unsigned char a, unsigned char b) {
  return a - b;
}

// Implementation of the method to determine the largest value in an array of 32
// positions
unsigned char Ramses::maxValue(unsigned char *array, int size) {
  unsigned char max = array[0];
  for (int i = 1; i < size; i++) {
    if (array[i] > max) {
      max = array[i];
    }
  }
  return max;
}

// Implementation of the method to call the 16-bit addition subroutine
unsigned short Ramses::callAdd16Bits(unsigned short a, unsigned short b) {
  return add16Bits(a, b);
}

// Execute instruction to add two 16-bit values
void PO::ADD16() {
  unsigned short a = memoria.ler(REM);  // Fetch first operand from memory
  unsigned short b = memoria.ler(REM + 1);  // Fetch second operand from memory
  unsigned short result = ula.add16Bits(a, b);
  memoria.escreve(REM + 2, result);  // Store result in memory
  std::cout << "ADD16: " << a << " + " << b << " = " << result << std::endl;
}

// Execute subroutine to add two 16-bit values
void PO::CALL_ADD16() {
  unsigned short a = memoria.ler(REM);
  unsigned short b = memoria.ler(REM + 1);
  unsigned short result = add16Bits(a, b);
  memoria.escreve(REM + 2, result);
  std::cout << "CALL_ADD16: Result stored at memory(" << (REM + 2) << ") = " << result << std::endl;
}

// Execute instruction to find the max value in a 32-element array
void PO::MAX_ARRAY() {
  unsigned char max = memoria.ler(REM);
  for (int i = 1; i < 32; i++) {
    unsigned char val = memoria.ler(REM + i);
    if (val > max) {
      max = val;
    }
  }
  memoria.escreve(REM + 32, max);
  std::cout << "MAX_ARRAY: Max value = " << (int)max << " stored at memory(" << (REM + 32) << ")" << std::endl;
}

// Execute instruction cycle
void PO::execute() {
  switch (RI.get_opcode()) {
  case Opcode::ADD16:
    ADD16();
    break;
  case Opcode::CALL_ADD16:
    CALL_ADD16();
    break;
  case Opcode::MAX_ARRAY:
    MAX_ARRAY();
    break;
  default:
    std::cout << "Unknown opcode: HALT" << std::endl;
    break;
  }
}

#endif // RAMSES_CPP
