#include <bitset>
#include <iostream>
#include <map>
#include <numeric>

void update_addr_mask(const std::string &mask, unsigned long &and_mask,
                      unsigned long &or_mask) {
  and_mask = ~0;
  or_mask = 0;

  for (size_t i = 0; i < mask.length(); ++i) {
    const char ch = *(mask.crbegin() + i);
    if (ch == '1')
      or_mask |= 1ul << i;
    else if (ch == 'X')
      and_mask &= ~(1ul << i);
  }
}

std::map<unsigned long, unsigned long> mem;

void spread_value(const unsigned long addr, const unsigned long mask,
                  const unsigned long val) {
  if (!~mask)
    mem.insert_or_assign(addr, val);
  else {
    std::bitset<36> bs = mask;

    for (auto b = 0; b < 36; ++b) {
      if (!bs.test(b)) {
        spread_value(addr | (1ul << b), mask | (1ul << b), val);
        spread_value(addr & ~(1ul << b), mask | (1ul << b), val);
        break;
      }
    }
  }
}

int main() {
  unsigned long and_mask = ~0;
  unsigned long or_mask = 0;

  for (std::string line; std::getline(std::cin, line);) {
    if (line.substr(0, 4) == "mask")
      update_addr_mask(line.substr(7), and_mask, or_mask);
    else {
      const unsigned long i = std::stoi(line.substr(4, 6));
      const unsigned long val = std::stoi(line.substr(line.find('=') + 1));

      const unsigned long addr = (i | or_mask) & and_mask;

      spread_value(addr, and_mask, val);
    }
  }

  const unsigned long sum =
      std::accumulate(mem.cbegin(), mem.cend(), 0ul,
                      [](auto a, auto kv) { return a + kv.second; });

  std::cout << sum << std::endl;

  return 0;
}
