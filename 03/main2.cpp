#include <iostream>

long slope(const int rows, const int columns) {
  int row = 0, column = 0;
  int trees = 0;

  std::cin.clear();
  std::cin.seekg(0, std::ios::beg);
  std::string line;
  while (std::getline(std::cin, line)) {
    if (line[column % line.length()] == '#')
      ++trees;

    row += rows;
    column += columns;

    // skip some lines
    for(int i = 0; i < rows - 1; ++i)
      if (!std::getline(std::cin, line)) goto end;
  }
 end:

  return trees;
}

int main()
{
  const long product =
    slope(1, 1)
    * slope(1, 3)
    * slope(1, 5)
    * slope(1, 7)
    * slope(2, 1)
    ;

  std::cout << product << '\n';

  return 0;
}
