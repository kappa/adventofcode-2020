#include <cstdlib>
#include <iostream>

void left(int &wx, int &wy) {
  auto t = wx;
  wx = -wy;
  wy = t;
}

void right(int &wx, int &wy) {
  auto t = wx;
  wx = wy;
  wy = -t;
}

int main()
{
  std::string line;
  int x = 0, y = 0;
  int wx = 10, wy = 1;

  while(std::getline(std::cin, line)) {
    const char c = line[0];
    const int num = std::stoi(line.substr(1));

    switch(c) {
    case 'N': wy += num; break;
    case 'S': wy -= num; break;
    case 'E': wx += num; break;
    case 'W': wx -= num; break;
    case 'L': for(auto i = 0; i < num / 90; ++i) left(wx, wy); break;
    case 'R': for(auto i = 0; i < num / 90; ++i) right(wx, wy); break;
    case 'F': x += num * wx; y += num * wy; break;
    default: std::cerr << "invalid command\n";
    }
  }

  std::cout << std::abs(x) + std::abs(y) << std::endl;

  return 0;
}
