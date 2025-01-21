#ifndef ULA_CPP
#define ULA_CPP

#include "../../inc/neander/ULA.hpp"

 std::uint8_t ULA::sum(const std::uint8_t a, const std::uint8_t b) {
  return (a + b) & 0xFF;
}

 std::uint8_t ULA::sub(const std::uint8_t a, const std::uint8_t b) {
  return (a - b) & 0xFF;
}

 std::uint8_t ULA::and_operation(const std::uint8_t a,
                                          const std::uint8_t b) {
  return (a & b);
}

 std::uint8_t ULA::or_operation(const std::uint8_t a,
                                         const std::uint8_t b) {
  return (a | b);
}

 std::uint8_t ULA::not_operation(const std::uint8_t a) { return (~a); }

std::uint8_t ULA::max(const std::vector<std::uint8_t> &vec) {
  std::uint8_t m_max{vec[0]};
  for (std::uint8_t i{1}; i < vec.size(); ++i)
    m_max = vec[i] > m_max ? vec[i] : m_max;
  return m_max;
}

#endif