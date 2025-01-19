#ifndef PC_H
#define PC_H

class PC
{
private:
    int carga; // Representa o contador de programa (endereço da próxima instrução).

public:
    PC(int carga_inicial) : carga(carga_inicial) {}

    void incrementa()
    {
        carga++; // Avança o contador de programa.
    }

    void set_carga(int novo_endereco)
    {
        carga = novo_endereco; // Atualiza o valor do contador de programa diretamente.
    }

    int get_carga() const // Retorna o endereço atual.
    {
        return carga;
    }
};

#endif