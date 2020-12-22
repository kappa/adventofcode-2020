#include <deque>
#include <iostream>

int main() {
  std::deque<int> p1{};
  std::deque<int> p2{};

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  for (std::string line; std::getline(std::cin, line) && !line.empty();)
    p1.push_back(std::stoi(line));

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  for (std::string line; std::getline(std::cin, line) && !line.empty();)
    p2.push_back(std::stoi(line));

  while (!p1.empty() && !p2.empty()) {
    const int c1 = p1.front();
    p1.pop_front();
    const int c2 = p2.front();
    p2.pop_front();

    if (c1 > c2) {
      p1.push_back(c1);
      p1.push_back(c2);
    } else {
      p2.push_back(c2);
      p2.push_back(c1);
    }
  }

  const std::deque<int> &won = p1.empty() ? p2 : p1;

  int sum = 0;
  int coef = 1;
  for (auto al = won.crbegin(); al < won.crend(); ++al)
    sum += *al * coef++;

  std::cout << sum << std::endl;

  return 0;
}
