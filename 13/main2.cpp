#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

int main()
{
  std::string line;
  std::getline(std::cin, line);
  std::getline(std::cin, line);

  std::vector<int> buses;
  std::istringstream is(line);
  for(std::string w; std::getline(is, w, ',');) {
    const int bus = w == "x" ? -1 : std::stoi(w);
    buses.push_back(bus);
  }

  long int max_bus = 0, max_i = -1;
  for(auto i = 0ul; i < buses.size(); ++i)
    if (buses[i] > max_bus) {
      max_bus = buses[i];
      max_i = i;
    }

  for (int i = 0; i < (int)buses.size(); ++i) {
    const auto bus = buses[i];
    std::cerr << bus << " @ " << i << std::endl;
  }

  std::cerr << max_bus << " max " << max_i << std::endl;

  // auto delay = 116833700000000ul / max_bus * max_bus + max_i;
  auto delay = 100000000000000ul / max_bus * max_bus + (max_bus - max_i);
  for (;;) {
    for (int i = 0; i < (int)buses.size(); ++i) {
      const auto bus = buses[i];
      if (bus == -1)
        continue;

      auto wait = delay % bus == 0 ? 0 : delay / bus * bus + bus - delay;
      auto need_wait = i % bus;

      // std::cerr << i << " -> " << bus << " wait: " << wait << std::endl;

      // if (i == 0) {
      //   std::cerr << "0 -> " << bus << " wait: " << wait << std::endl;
      // }

      if ((int)wait != need_wait)
        goto skip;
      if (i != 0 && i != 7 && i != 13 && i != 27 && i != 32)
        std::cerr << "Match! for " << bus << "[" << i << "] with wait "
                  << wait << std::endl;
    }
    break;

  skip:
    delay += max_bus;
    if (delay % 100000000 == 0)
      std::cerr << "delay " << delay << std::endl;
  }

  std::cout << delay << std::endl;

  return 0;
}
