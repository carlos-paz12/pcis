#ifndef CESAR_HPP
#define CESAR_HPP

#include "AddressingMode.hpp"
#include "Cache.hpp"
#include "Clock.hpp"
#include "Flag.hpp"
#include "Instruction.hpp"
#include "Memoria.hpp"
#include "Opcode.hpp"
#include "PipelineStage.hpp"
#include "ULA.hpp"

typedef uint8_t Registrador;

class Cesar
{
  Registrador R1;
  Registrador R2;
  Registrador AC; // Registrador acumulador (AC)

public:
  // Construtor para inicializar os registradores
  Cesar() : R1(0), R2(0), AC(0) {}
  
  static unsigned char add8Bits(unsigned char a, unsigned char b);
  static unsigned char subtract8Bits(unsigned char a, unsigned char b);
  static unsigned char multiply8Bits(unsigned char a, unsigned char b);
  static unsigned char divide8Bits(unsigned char a, unsigned char b);

  static unsigned char and8Bits(unsigned char a, unsigned char b);
  static unsigned char or8Bits(unsigned char a, unsigned char b);
  static unsigned char xor8Bits(unsigned char a, unsigned char b);
  static unsigned char not8Bits(unsigned char a);

  static unsigned char shiftLeft8Bits(unsigned char value,
                                      unsigned char positions);
  static unsigned char shiftRight8Bits(unsigned char value,
                                       unsigned char positions);

  // Simulação de registradores e memória
  unsigned char registers[8]; // 8 registradores de 8 bits

  // Pilha
  unsigned short stack[256]; // Pilha com capacidade para 256 valores
  unsigned char stackPointer;

  void pushStack(unsigned short value);
  unsigned short popStack();

  // Flags

  // Modos de endereçamento

  unsigned char fetchOperand(AddressingMode mode, unsigned short operand);

  // Execução de instruções

  void executeInstruction(Instruction instr, unsigned char operand1,
                          unsigned char operand2);

  // Unidade de controle e decodificação
  Instruction decodeInstruction(unsigned char opcode);

  // Interrupções
  void (*interruptVector[256])(); // Tratadores de interrupção
  void handleInterrupt(unsigned char interruptCode);
  void setInterruptHandler(unsigned char code, void (*handler)());

  void enableInterrupts();
  void disableInterrupts();

  // Debugging
  void printState() const;
  void logInstruction(Instruction instr, unsigned char operand1,
                      unsigned char operand2);
  void debugMemoryDump() const;
  void debugRegisterState() const;

  // Controle do clock

  Clock clock;

  // Unidade de cache

  Cache cache;

  // Pipeline
  struct PipelineStage
  {
    unsigned char instruction;
    unsigned short operand1;
    unsigned short operand2;
    bool isActive;
  };

  PipelineStage pipeline[5];
};

#endif // CESAR_H
