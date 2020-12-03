#include <iostream>

int main()
{
  int row = 0, column = 0;
  std::string line;
  int trees = 0;

  while(std::getline(std::cin, line)) {
    if (line[column % line.length()] == '#') {
      ++trees;
    }

    row += 1;
    column += 3;
  }

  std::cout << trees << '\n';

  return 0;
}
