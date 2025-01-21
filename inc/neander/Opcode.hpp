#ifndef OPCODE_HPP
#define OPCODE_HPP

enum Opcode {
  NOP,     ///!> Nenhuma operação.
  STA_END, ///!> Armazena acumulador no endereço “end”.
  LDA_END, ///!> Carrega o acumulador com o conteúdo do endereço “end”.
  ADD_END, ///!> Soma o conteúdo do endereço “end” ao acumulador.
  AND_END, ///!> Efetua operação lógica “E” do conteúdo do endereço “end”.
  OR_END, ///!> Efetua operação lógica “OU” do conteúdo do endereço “end”.
  NOT,     ///!> Inverte todos os bits do acumulador.
  JMP_END, ///!> Desvio incondicional para o endereço “end”.
  JN_END,  ///!> Desvio condicional, se “N=1”, para o endereço “end”.
  JZ_END,  ///!> Desvio condicional, se “Z=1”, para o endereço “end”.
  HLT,      ///!> Para o ciclo de busca-decodificação-execução.
  MUX       ///!> Multiplexador.
};

#endif