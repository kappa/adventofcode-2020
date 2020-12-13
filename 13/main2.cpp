#include <algorithm>
#include <iostream>
#include <iterator>
#include <functional>
#include <numeric>
#include <sstream>
#include <vector>

constexpr
long long modulo(const long long a, const long long b) {
  const auto result = a % b;
  return result >= 0 ? result : result + b;
}

constexpr
long long power_mod(const long long base, const int power, const int mod) {
  auto rv = modulo(base, mod);

  for (auto i = 0; i < power - 1; ++i)
    rv = modulo(rv * base, mod);

  return rv;
}

// Fermat's little theorem
constexpr
long long mulinv_mod(const long long num, const int mod) {
  return power_mod(num, mod - 2, mod);
}

int main()
{
  std::string line;
  std::getline(std::cin, line);
  std::getline(std::cin, line);

  struct bus_t {
    int a, r;
  };

  std::vector<bus_t> buses;
  std::istringstream is(line);
  std::string w;
  for(int i = 0; std::getline(is, w, ','); ++i) {
    if (w != "x")
      buses.push_back(bus_t{std::stoi(w), i % std::stoi(w)});
  }

  long long m = 1;
  for(auto bus : buses)
    m *= bus.a;

  long long x = 0;
  for (auto bus : buses) {
    const auto mi = m / bus.a;
    const auto minv = mulinv_mod(mi, bus.a);

    x = modulo(x + (bus.a - bus.r) * mi * minv, m);
  }

  std::cout << modulo(x, m) << std::endl;

  return 0;
}
