#ifndef ABC_HPP
#define ABC_HPP

#include <iostream>

namespace temp {

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

} // namespace temp

#endif // ABC_HPP
