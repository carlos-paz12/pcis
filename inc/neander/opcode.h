#ifndef OPCODE_H
#define OPCODE_H

enum class Opcode
{
    NOP,     ///!> Nenhuma operação.
    STA_END, ///!> Armazena acumulador no endereço “end” da memória
    LDA_END, ///!> Carrega o acumulador com o conteúdo do endereço “end” da memória
    ADD_END, ///!> Soma o conteúdo do endereço “end” da memória ao acumulador
    AND_END, ///!> Efetua operação lógica “E” do conteúdo do endereço “end” da memória ao acumulador
    OR_END,  ///!>  Efetua operação lógica “OU” do conteúdo do endereço “end” da memória ao acumulador
    NOT,     ///!> 	Inverte todos os bits do acumulador
    JMP_END, ///!> Desvio incondicional para o endereço “end” da memória
    JN_END,  ///!> 	Desvio condicional, se “N=1”, para o endereço “end” da memória
    JZ_END,  ///!> Desvio condicional, se “Z=1”, para o endereço “end” da memória
    HLT      ///!> Para o ciclo de busca-decodificação-execução
};

#endif