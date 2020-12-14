#include <algorithm>
#include <climits>
#include <iostream>

int binary(const std::string &str, const char one) {
  int rv = 0;

  int twos = 1;
  for (auto ch = str.rbegin(); ch < str.rend(); ++ch) {
    if (*ch == one)
      rv += twos;
    twos *= 2;
  }

  return rv;
}

int main() {
  int max_id = 0, min_id = INT_MAX, sum = 0, count = 0;

  for (std::string line; std::cin >> line;) {
    const int id =
        binary(line.substr(0, 7), 'B') * 8 + binary(line.substr(7), 'R');
    max_id = std::max(max_id, id);
    min_id = std::min(min_id, id);
    sum += id;
    ++count;
  }

  std::cout << (min_id + max_id) * (count + 1) / 2 - sum << std::endl;

  return 0;
}
