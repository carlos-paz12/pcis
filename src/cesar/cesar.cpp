#ifndef CESAR_CPP
#define CESAR_CPP

#include "../../inc/cesar/cesar.h"
#include "../../inc/cesar/Memoria.hpp"

Memoria memory;

// Implementação das operações aritméticas
unsigned char Cesar::add8Bits(unsigned char a, unsigned char b) {
  return a + b;
}

unsigned char Cesar::subtract8Bits(unsigned char a, unsigned char b) {
  return a - b;
}

unsigned char Cesar::multiply8Bits(unsigned char a, unsigned char b) {
  return a * b;
}

unsigned char Cesar::divide8Bits(unsigned char a, unsigned char b) {
  if (b == 0) {
    return 0;
  }
  return a / b;
}

// Implementação das operações lógicas
unsigned char Cesar::and8Bits(unsigned char a, unsigned char b) {
  return a & b;
}

unsigned char Cesar::or8Bits(unsigned char a, unsigned char b) { return a | b; }

unsigned char Cesar::xor8Bits(unsigned char a, unsigned char b) {
  return a ^ b;
}

unsigned char Cesar::not8Bits(unsigned char a) { return ~a; }

unsigned char Cesar::shiftLeft8Bits(unsigned char value,
                                    unsigned char positions) {
  return value << positions;
}

unsigned char Cesar::shiftRight8Bits(unsigned char value,
                                     unsigned char positions) {
  return value >> positions;
}

void Cesar::pushStack(unsigned short value) {
  if (stackPointer >= sizeof(stack) / sizeof(stack[0])) {
    return;
  }
  stack[stackPointer++] = value;
}

unsigned short Cesar::popStack() {
  if (stackPointer == 0) {
    return 0;
  }
  return stack[--stackPointer];
}

unsigned char Cesar::fetchOperand(AddressingMode mode, unsigned short operand) {
  switch (mode) {
  case IMMEDIATE:
    return static_cast<unsigned char>(operand);
  case DIRECT:
    return static_cast<unsigned char>(memory.read(operand));
  case INDIRECT:
    return static_cast<unsigned char>(memory.read(registers[operand]));
  case INDEXED:
    return static_cast<unsigned char>(memory.read(operand + registers[0]));
  case RELATIVE:
    return static_cast<unsigned char>(memory.read(stackPointer + operand));
  default:
    return 0; // Modo inválido
  }
}

Cesar::Instruction Cesar::decodeInstruction(unsigned char opcode) {
  Instruction instr;

  switch (opcode) {
  case 0x00:
    instr = {LOAD, IMMEDIATE, "LOAD"};
    break;
  case 0x01:
    instr = {STORE, DIRECT, "STORE"};
    break;
  case 0x02:
    instr = {ADD, DIRECT, "ADD"};
    break;
  case 0x03:
    instr = {SUB, DIRECT, "SUB"};
    break;
  case 0x04:
    instr = {JUMP, DIRECT, "JUMP"};
    break;
  case 0x05:
    instr = {JEQ, DIRECT, "JEQ"};
    break;
  case 0x06:
    instr = {JNE, DIRECT, "JNE"};
    break;
  case 0x07:
    instr = {JG, DIRECT, "JG"};
    break;
  case 0x08:
    instr = {JL, DIRECT, "JL"};
    break;
  case 0x09:
    instr = {CMP, DIRECT, "CMP"};
    break;
  case 0x0A:
    instr = {CALL, DIRECT, "CALL"};
    break;
  case 0x0B:
    instr = {RET, IMMEDIATE, "RET"};
    break;
  case 0x0C:
    instr = {HALT, IMMEDIATE, "HALT"};
    break;
  default:
    throw std::runtime_error("Instrução inválida!");
  }
  return instr;
}

void Cesar::executeInstruction(Instruction instr, unsigned char operand1,
                               unsigned char operand2) {
  switch (instr.opcode) {
  case LOAD: // Carregar valor no acumulador
    registers[0] = fetchOperand(instr.addressing, operand1);
    break;

  case STORE: // Armazenar acumulador na memória
    memory.write(operand1, registers[0]);
    break;

  case ADD: // Somar valor ao acumulador
    registers[0] += fetchOperand(instr.addressing, operand1);
    break;

  case SUB: // Subtrair valor do acumulador
    registers[0] -= fetchOperand(instr.addressing, operand1);
    break;

  case JUMP:                 // Pular para um endereço específico
    registers[1] = operand1; // Assumindo PC em registers[1]
    break;

  case JEQ: // Pular se igual (baseado no resultado do CMP)
    if (flags.zero) {
      registers[1] = operand1;
    }
    break;

  case JNE: // Pular se diferente
    if (!flags.zero) {
      registers[1] = operand1;
    }
    break;

  case JG: // Pular se maior
    if (flags.greater) {
      registers[1] = operand1;
    }
    break;

  case JL: // Pular se menor
    if (flags.less) {
      registers[1] = operand1;
    }
    break;

  case CMP: // Comparar acumulador com valor
  {
    int result = registers[0] - fetchOperand(instr.addressing, operand1);
    flags.zero = (result == 0);
    flags.greater = (result > 0);
    flags.less = (result < 0);
  } break;

  case CALL:
    stackPointer--;
    memory.write(stackPointer, registers[1]);
    registers[1] = operand1;
    break;

  case RET:
    registers[1] = memory.read(stackPointer);
    stackPointer++;
    break;

  case HALT: // Parar execução
    throw std::runtime_error("Execução interrompida (HALT).");
    break;

  default:
    throw std::runtime_error("Instrução desconhecida!");
  }
}

// ===================================================== DEBUGAR
// ==================================================== //
void Cesar::printState() const {
  std::cout << "=== Estado do Processador ===" << std::endl;
  std::cout << "Registradores:" << std::endl;
  for (int i = 0; i < 8; ++i) {
    std::cout << "R" << i << ": " << static_cast<int>(registers[i]) << " ";
  }
  std::cout << std::endl;

  std::cout << "Flags:" << std::endl;
  std::cout << "Carry: " << flags.carry << ", Zero: " << flags.zero
            << ", Overflow: " << flags.overflow
            << ", Negative: " << flags.negative
            << ", Greater: " << flags.greater << ", Less: " << flags.less
            << std::endl;

  std::cout << "Stack Pointer: " << static_cast<int>(stackPointer) << std::endl;
  std::cout << "=============================" << std::endl;
}

void Cesar::logInstruction(Instruction instr, unsigned char operand1,
                           unsigned char operand2) {
  std::cout << "Instrução Executada: " << instr.mnemonic << std::endl;
  std::cout << "Operandos: " << static_cast<int>(operand1) << ", "
            << static_cast<int>(operand2) << std::endl;
  std::cout << "=====================================" << std::endl;
}

void Cesar::debugMemoryDump() const {
  std::cout << "=== Dump de Memória ===" << std::endl;
  for (int i = 0; i < 256; ++i) {
    std::cout << "Endereço [" << i << "]: " << static_cast<int>(memory.read(i))
              << std::endl;
  }
  std::cout << "========================" << std::endl;
}

void Cesar::debugRegisterState() const {
  std::cout << "=== Estado dos Registradores ===" << std::endl;
  for (int i = 0; i < 8; ++i) {
    std::cout << "R" << i << ": " << static_cast<int>(registers[i])
              << std::endl;
  }
  std::cout << "================================" << std::endl;
}

#endif // CESAR_CPP