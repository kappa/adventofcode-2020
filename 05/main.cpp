#include <algorithm>
#include <iostream>

unsigned binary(const std::string &str, const char one) {
  unsigned rv = 0;

  unsigned two = 1;
  for(auto ch = str.rbegin(); ch < str.rend(); ++ch) {
    if (*ch == one)
      rv += two;
    two *= 2;
  }

  return rv;
}

int main()
{
  std::string line;

  unsigned max_id = 0;
  while(std::cin >> line) {
    max_id = std::max(max_id, binary(line.substr(0, 7), 'B') * 8 + binary(line.substr(7), 'R'));
  }

  std::cout << max_id << "\n";

  return 0;
}
