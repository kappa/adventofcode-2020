#include <iostream>

int main() {
  int row = 0, column = 0;
  int trees = 0;

  for (std::string line; std::getline(std::cin, line);) {
    if (line[column % line.length()] == '#')
      ++trees;

    row += 1;
    column += 3;
  }

  std::cout << trees << std::endl;

  return 0;
}
