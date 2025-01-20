#ifndef CESAR_H
#define CESAR_H

#include <functional>
#include <iostream>
#include <vector>

class Cesar {
public:
  // Métodos básicos
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
  struct Flags {
    bool carry;
    bool zero;
    bool overflow;
    bool negative;
    bool greater;
    bool less;
  } flags;

  // Modos de endereçamento
  enum AddressingMode { IMMEDIATE, DIRECT, INDIRECT, INDEXED, RELATIVE };

  unsigned char fetchOperand(AddressingMode mode, unsigned short operand);

  // Execução de instruções
  enum Opcode {
    LOAD,
    STORE,
    ADD,
    SUB,
    JUMP,
    JEQ,
    JNE,
    JG,
    JL,
    CMP,
    CALL,
    RET,
    HALT
  };

  struct Instruction {
    Opcode opcode;             // Código da operação
    AddressingMode addressing; // Modo de endereçamento
    std::string mnemonic;      // Nome da operação (opcional)
  };

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
  class Clock {
  private:
    unsigned int cycleCount;
    unsigned int frequency; // em Hertz

  public:
    void tick();
    unsigned int getCycleCount() const;
  };

  Clock clock;

  // Unidade de cache
  class Cache {
  private:
    unsigned char data[64]; // Cache pequena
    unsigned char tags[64]; // Identificadores de endereço

  public:
    unsigned char read(unsigned short address);
    void write(unsigned short address, unsigned char value);
  };

  Cache cache;

  // Pipeline
  struct PipelineStage {
    unsigned char instruction;
    unsigned short operand1;
    unsigned short operand2;
    bool isActive;
  };

  PipelineStage pipeline[5];
};

#endif // CESAR_H
