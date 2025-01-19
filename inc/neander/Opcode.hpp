#ifndef OPCODE_H
#define OPCODE_H

enum Opcode
{
    NOP = 0x00,     ///!> Nenhuma operação.
    STA_END = 0x01, ///!> Armazena acumulador no endereço “end”.
    LDA_END = 0x02, ///!> Carrega o acumulador com o conteúdo do endereço “end”.
    ADD_END = 0x03, ///!> Soma o conteúdo do endereço “end” ao acumulador.
    AND_END = 0x04, ///!> Efetua operação lógica “E” do conteúdo do endereço “end”.
    OR_END = 0x05,  ///!> Efetua operação lógica “OU” do conteúdo do endereço “end”.
    NOT = 0x06,     ///!> Inverte todos os bits do acumulador.
    JMP_END = 0x07, ///!> Desvio incondicional para o endereço “end”.
    JN_END = 0x08,  ///!> Desvio condicional, se “N=1”, para o endereço “end”.
    JZ_END = 0x09,  ///!> Desvio condicional, se “Z=1”, para o endereço “end”.
    HLT = 0xFF      ///!> Para o ciclo de busca-decodificação-execução.
};

#endif