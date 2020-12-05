#include <algorithm>
#include <climits>
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

  unsigned max_id = 0, min_id = UINT_MAX, sum = 0, count = 0;
  while(std::cin >> line) {
    unsigned id = binary(line.substr(0, 7), 'B') * 8 + binary(line.substr(7), 'R');
    max_id  = std::max(max_id, id);
    min_id  = std::min(min_id, id);
    sum    += id;
    ++count;
  }

  std::cout << (min_id + max_id) * (count + 1) / 2 - sum << "\n";

  return 0;
}
