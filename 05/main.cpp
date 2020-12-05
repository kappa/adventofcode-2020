#include <algorithm>
#include <iostream>

int binary(const std::string &str, const char one) {
  int rv = 0;

  int twos = 1;
  for(auto ch = str.rbegin(); ch < str.rend(); ++ch) {
    if (*ch == one) rv += twos;
    twos *= 2;
  }

  return rv;
}

int main()
{
  int max_id = 0;

  std::string line;
  while(std::cin >> line) {
    max_id = std::max(max_id, binary(line.substr(0, 7), 'B') * 8 + binary(line.substr(7), 'R'));
  }

  std::cout << max_id << '\n';

  return 0;
}
