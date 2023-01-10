#ifndef PACKETS_HPP
#define PACKETS_HPP

#include <iostream>

namespace neural_sim {

class Abc {
public:
  ~Abc() = default;

private:
  Abc() = delete;
  Abc(Abc &&) = delete;
  Abc(const Abc &) = delete;
  Abc &operator=(Abc &&) = delete;
  Abc &operator=(const Abc &) = delete;
};

} // namespace neural_sim

#endif // PACKETS_HPP
