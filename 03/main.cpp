#include <iostream>

int main()
{
  int row = -1, column = -3;
  std::string line;
  int trees = 0;

  while(std::getline(std::cin, line)) {
    row += 1;
    column += 3;

    if (line[column % line.length()] == '#') {
      ++trees;
    }
  }

  std::cout << trees << '\n';

  return 0;
}
