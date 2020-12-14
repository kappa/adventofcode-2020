#include <array>
#include <iostream>
#include <numeric>

void update_mask(const std::string &mask, unsigned long &and_mask,
                 unsigned long &or_mask) {
  and_mask = ~0;
  or_mask = 0;

  for (size_t i = 0; i < mask.length(); ++i) {
    const char ch = *(mask.crbegin() + i);
    if (ch == '1')
      or_mask |= 1ul << i;
    else if (ch == '0')
      and_mask &= ~(1ul << i);
  }
}

int main() {
  unsigned long and_mask = ~0;
  unsigned long or_mask = 0;

  std::array<unsigned long, 65535> mem{{0}};

  for (std::string line; std::getline(std::cin, line);) {
    if (line.substr(0, 4) == "mask")
      update_mask(line.substr(7), and_mask, or_mask);
    else {
      const unsigned i = std::stoi(line.substr(4, 6));
      const unsigned val = std::stoi(line.substr(line.find('=') + 1));

      mem[i] = (val & and_mask) | or_mask;
    }
  }

  std::cout << std::accumulate(mem.cbegin(), mem.cend(), 0ul) << std::endl;

  return 0;
}
