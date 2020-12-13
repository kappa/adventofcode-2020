#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
  std::vector<int> entries(std::istream_iterator<int>(std::cin),
                           std::istream_iterator<int>{});

  std::sort(entries.begin(), entries.end());

  for (auto const first : entries)
    for (auto const second : entries)
      if (auto const third = 2020 - first - second;
          std::binary_search(entries.begin(), entries.end(), third)) {
        std::cout << first * third << std::endl;
        goto end;
      }
end:

  return 0;
}
