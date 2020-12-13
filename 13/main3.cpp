#include <algorithm>
#include <iostream>
#include <iterator>
#include <functional>
#include <numeric>
#include <sstream>
#include <vector>

int main()
{
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  struct bus_t {
    int a, r;
  };

  std::vector<bus_t> buses;

  std::string w;
  for(int i = 0; std::getline(std::cin, w, ','); ++i) {
    if (w != "x") {
      const auto num = std::stoi(w);
      // "i" is remainder, so if it's > num, mod it right away
      buses.push_back(bus_t{num, i % num});
    }
  }

  long t = buses[0].a;
  long step = t;
  for (auto i = 1; i < (int)buses.size(); ++i) {
    while (t % buses[i].a != (buses[i].a - buses[i].r))
      t += step;

    step *= buses[i].a;
  }

  std::cout << t << std::endl;

  return 0;
}
