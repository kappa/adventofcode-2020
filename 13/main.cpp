#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

int main()
{
  int delay;
  std::cin >> delay;

  std::vector<int> buses;
  std::string line;
  std::getline(std::cin, line);
  std::getline(std::cin, line);

  std::istringstream is(line);
  for(std::string w; std::getline(is, w, ',');) {
    if (w == "x") continue;
    const int bus = std::stoi(w);
    buses.push_back(bus);
  }

  int rv = 0;
  int min = delay;
  for(auto bus : buses) {
    if (delay % bus == 0) {
      rv = bus;
      break;
    }
    auto wait = delay / bus * bus + bus - delay;
    std::cerr << wait << std::endl;
    if (wait < min) {
      min = wait;
      rv = bus * wait;
    }
  }

  std::cout << rv << std::endl;

  return 0;
}
