#ifndef ULA_H
#define ULA_H

#include <vector>

struct ULA
{
    int sum(int a, int b) { return (a + b); }

    int sub(int a, int b) { return (a - b); }

    int and_operation(int a, int b) { return (a & b); } // Operação lógica "AND" bit a bit

    int or_operation(int a, int b) { return (a | b); } // Operação lógica "OR" bit a bit

    int not_operation(int a) { return (~a); } // Operação de inversão (complemento de 1)

    int max(std::vector<int> vec)
    {
        int m_max{vec[0]};
        for (int i{1}; i < vec.size(); ++i)
            m_max = vec[i] > m_max ? vec[i] : m_max;
        return m_max;
    }
};

#endif