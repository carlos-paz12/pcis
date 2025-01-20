#ifndef ULA_HPP
#define ULA_HPP

#include <cstdint> /// std::uint8_t
#include <vector>

class ULA
{
public:
    constexpr std::uint8_t sum(const std::uint8_t a, const std::uint8_t b); // Soma com máscara de 8 bits

    constexpr std::uint8_t sub(const std::uint8_t a, const std::uint8_t b); // Subtração com máscara de 8 bits

    constexpr std::uint8_t and_operation(const std::uint8_t a, const std::uint8_t b); // Operação lógica "AND" bit a bit

    constexpr std::uint8_t or_operation(const std::uint8_t a, const std::uint8_t b); // Operação lógica "OR" bit a bit

    constexpr std::uint8_t not_operation(const std::uint8_t a); // Operação de inversão (complemento de 1)

    std::uint8_t max(const std::vector<std::uint8_t> &vec);
};

#endif