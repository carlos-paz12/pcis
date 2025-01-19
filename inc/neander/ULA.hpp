#ifndef ULA_H
#define ULA_H

#include <cstdint> /// std::uint8_t
#include <vector>

struct ULA
{
    constexpr std::uint8_t sum(const std::uint8_t a, const std::uint8_t b) { return (a + b) & 0xFF; } // Soma com máscara de 8 bits

    constexpr std::uint8_t sub(const std::uint8_t a, const std::uint8_t b) { return (a - b) & 0xFF; } // Subtração com máscara de 8 bits

    constexpr std::uint8_t and_operation(const std::uint8_t a, const std::uint8_t b) { return (a & b); } // Operação lógica "AND" bit a bit

    constexpr std::uint8_t or_operation(const std::uint8_t a, const std::uint8_t b) { return (a | b); } // Operação lógica "OR" bit a bit

    constexpr std::uint8_t not_operation(const std::uint8_t a) { return (~a); } // Operação de inversão (complemento de 1)

    std::uint8_t max(std::vector<std::uint8_t> vec)
    {
        std::uint8_t m_max{vec[0]};
        for (std::uint8_t i{1}; i < vec.size(); ++i)
            m_max = vec[i] > m_max ? vec[i] : m_max;
        return m_max;
    }
};

#endif