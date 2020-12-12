#include <cstdlib>
#include <iostream>

int main()
{
  std::string line;
  int x = 0, y = 0;
  int dir = 90;

  while(std::getline(std::cin, line)) {
    const char c = line[0];
    const int num = std::stoi(line.substr(1));

    switch(c) {
    case 'N': y += num; break;
    case 'S': y -= num; break;
    case 'E': x += num; break;
    case 'W': x -= num; break;
    case 'L': dir = (dir + 360 - num) % 360; break;
    case 'R': dir = (dir + num) % 360; break;
    case 'F': switch (dir) {
      case 0: y += num; break;
      case 90: x += num; break;
      case 180: y -= num; break;
      case 270: x -= num; break;
      default: std::cerr << "invalid dir\n";
      }; break;
    default: std::cerr << "invalid command\n";
    }
  }

  std::cout << std::abs(x) + std::abs(y) << std::endl;

  return 0;
}
