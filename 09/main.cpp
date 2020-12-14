#include <algorithm>
#include <deque>
#include <iostream>
#include <set>

int main() {
  std::deque<int> prev25{};
  std::set<int> prev25_set{};

  for (std::string line; std::getline(std::cin, line);) {
    const int cur = std::stoi(line);

    if (prev25.size() >= 25) {
      if (std::none_of(prev25.begin(), prev25.end(),
                       [&prev25_set, cur](int num) -> bool {
                         return prev25_set.count(cur - num) > 0;
                       })) {
        std::cout << cur << std::endl;
        break;
      }

      const int old = prev25[0];
      prev25.pop_front();
      prev25_set.erase(old);
    }

    prev25.push_back(cur);
    prev25_set.insert(cur);
  }

  return 0;
}
