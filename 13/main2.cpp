#include <iostream>
#include <numeric>
#include <vector>

constexpr long modulo(const long a, const long b) {
  const auto result = a % b;
  return result >= 0 ? result : result + b;
}

constexpr long power_mod(const long base, const int power, const int mod) {
  auto rv = modulo(base, mod);

  for (auto i = 0; i < power - 1; ++i)
    rv = modulo(rv * base, mod);

  return rv;
}

// Fermat's little theorem
constexpr long mulinv_mod(const long num, const int mod) {
  return power_mod(num, mod - 2, mod);
}

int main() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  struct bus_t {
    int a, r;
  };

  std::vector<bus_t> buses;

  std::string w;
  for (int i = 0; std::getline(std::cin, w, ','); ++i) {
    if (w != "x") {
      const auto num = std::stoi(w);
      // "i" is remainder, so if it's > num, mod it right away
      buses.push_back(bus_t{num, i % num});
    }
  }

  const long m = std::accumulate(
      buses.begin(), buses.end(), 1l,
      [](const long acc, const bus_t &bus) { return acc * bus.a; });

  const long x = std::accumulate(
      buses.begin(), buses.end(), 0l, [m](const long acc, const bus_t &bus) {
        const auto mi = m / bus.a;
        const auto minv = mulinv_mod(mi, bus.a);

        return modulo(acc + (bus.a - bus.r) * mi * minv, m);
      });

  std::cout << x << std::endl;

  return 0;
}
