#include <iostream>

void left(int &wx, int &wy) {
  const auto t = wx;
  wx = -wy;
  wy = t;
}

int main() {
  int x = 0, y = 0;
  int wx = 10, wy = 1;

  for (std::string line; std::getline(std::cin, line);) {
    const char c = line[0];
    const int num = std::stoi(line.substr(1));

    switch (c) {
    case 'N':
      wy += num;
      break;
    case 'S':
      wy -= num;
      break;
    case 'E':
      wx += num;
      break;
    case 'W':
      wx -= num;
      break;
    case 'L':
      for (auto i = 0; i < num / 90; ++i)
        left(wx, wy);
      break;
    case 'R':
      // implement right turl as left by 360-deg angle
      for (auto i = 0; i < (360 - num) / 90; ++i)
        left(wx, wy);
      break;
    case 'F':
      x += num * wx;
      y += num * wy;
      break;
    default:
      std::cerr << "invalid command\n";
    }
  }

  std::cout << std::abs(x) + std::abs(y) << std::endl;

  return 0;
}
