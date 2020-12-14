#include <iostream>

long slope(const int rows, const int columns) {
  int row = 0, column = 0;
  int trees = 0;

  std::cin.clear();
  std::cin.seekg(0, std::ios::beg);

  for (std::string line; std::getline(std::cin, line);) {
    if (line[column % line.length()] == '#')
      ++trees;

    row += rows;
    column += columns;

    // skip some lines
    for (int i = 0; i < rows - 1; ++i)
      if (!std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'))
        goto end;
  }
end:

  return trees;
}

int main() {
  const long product =
      slope(1, 1)
    * slope(1, 3)
    * slope(1, 5)
    * slope(1, 7)
    * slope(2, 1)
    ;

  std::cout << product << std::endl;

  return 0;
}
