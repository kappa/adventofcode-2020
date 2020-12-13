#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
  std::vector<int> entries(std::istream_iterator<int>(std::cin),
                           std::istream_iterator<int>{});

  std::sort(entries.begin(), entries.end());

  for (auto const first : entries)
    if (auto const second = 2020 - first;
        std::binary_search(entries.begin(), entries.end(), second)) {
      std::cout << first * second << std::endl;
      break;
    }
}
