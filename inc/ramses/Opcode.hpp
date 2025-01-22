#ifndef OPCODE_HPP
#define OPCODE_HPP

enum Opcode {
  NOP, ///< Nenhuma operação (No Operation). Utilizada para preencher espaços ou
       ///< pausas.
  STA_END, ///< Armazena o acumulador no endereço especificado (“end”).
  LDA_END, ///< Carrega o acumulador com o conteúdo do endereço especificado
           ///< (“end”).
  ADD_END, ///< Soma o conteúdo do endereço especificado (“end”) ao acumulador.
  AND_END, ///< Executa uma operação lógica AND entre o acumulador e o conteúdo
           ///< do endereço “end”.
  OR_END, ///< Executa uma operação lógica OR entre o acumulador e o conteúdo do
          ///< endereço “end”.
  NOT,     ///< Inverte (complemento de 1) todos os bits do acumulador.
  JMP_END, ///< Desvio incondicional para o endereço especificado (“end”).
  JN_END, ///< Desvio condicional para o endereço “end” se o bit “N” (negativo)
          ///< for 1.
  JZ_END, ///< Desvio condicional para o endereço “end” se o bit “Z” (zero)
          ///< for 1.
  HLT, ///< Para o ciclo de busca-decodificação-execução (Halt).
  MUX  ///< Executa a operação do multiplexador (Multiplexador).
};

#endif