#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

const int needle = 41682220;

int main()
{
  std::vector<long int> all{};

  std::string line;
  while(std::getline(std::cin, line)) {
    const long int cur = std::stol(line);
    all.push_back(cur);
  }

  for (auto start = all.begin(); start < all.end(); ++start) {
    for (auto end = start + 1; end <= all.end(); ++end) {
      if (needle == std::accumulate(start, end + 1, 0)) {
        std::cout << *std::max_element(start, end) + *std::min_element(start, end) << std::endl;
      }
    }
  }

  return 0;
}
