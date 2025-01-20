#include <iostream>
#include "Neander.hpp"

int main()
{
    // Passo 1: Instanciar a memória e o processador.
    Memory memoria;  // 256 bytes de memória
    Neander processador;

    // Passo 2: Carregar instruções simples na memória.
    // Vamos carregar a memória com as instruções: LDA 5, ADD 5, HLT.
    memoria.write(0, Instrucao(Opcode::LDA_END, 5).toUint8());  // Carrega o valor da memória 5 no AC
    memoria.write(1, Instrucao(Opcode::ADD_END, 5).toUint8());  // Soma o valor da memória 5 com o AC
    memoria.write(2, Instrucao(Opcode::HLT, 0).toUint8());      // Instrução de HALT

    // Passo 3: Definir o valor inicial na memória para teste.
    memoria.write(5, 10);  // Definindo o valor na memória endereço 5 como 10

    std::cout << "Memória no endereço 0: " << (int)memoria.read(0) << std::endl;  // Verifica o valor no endereço 0

    // Passo 4: Executar o processador.
    processador.run(memoria);

    // Passo 5: Verificar os resultados.
    if (processador.getAC() == 20)  // O acumulador deve ter 20 após LDA (10) + ADD (10)
    {
        std::cout << "Test passed: AC = " << (int)processador.getAC() << std::endl;
    }
    else
    {
        std::cout << "Test failed: AC = " << (int)processador.getAC() << std::endl;
    }

    // Verificar o contador de ciclos (deve ser 3, um para cada instrução executada).
    std::cout << "Ciclos executados: " << processador.getCycleCount() << std::endl;

    return 0;
}
