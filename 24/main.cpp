#include <iostream>
#include <set>
#include <vector>

int main() {
  std::set<std::pair<int, int>> grid{};
  for (std::string line; std::getline(std::cin, line);) {
    int x = 0, y = 0;
    for (std::size_t i = 0; i < line.length(); ++i) {
      if (line[i] == 's') {
        if (line[++i] == 'e')
          ++x;
        else
          --y;
      } else if (line[i] == 'n') {
        if (line[++i] == 'e')
          ++y;
        else
          --x;
      } else if (line[i] == 'e') {
        ++x;
        ++y;
      } else {
        --y;
        --x;
      }
    }
    const auto cc = std::make_pair(x, y);
    if (grid.count(cc)) {
      grid.erase(cc);
    } else {
      grid.insert(cc);
    }
  }

  std::cout << grid.size() << std::endl;

  return 0;
}
