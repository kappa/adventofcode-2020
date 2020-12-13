#include <algorithm>
#include <iostream>
#include <iterator>
#include <functional>
#include <numeric>
#include <sstream>
#include <vector>

int main()
{
  std::string line;
  std::getline(std::cin, line);
  std::getline(std::cin, line);

  struct bus_t {
    int a, r;
  };

  std::vector<bus_t> buses;
  std::istringstream is(line);
  std::string w;
  for(int i = 0; std::getline(is, w, ','); ++i) {
    if (w != "x")
      buses.push_back(bus_t{std::stoi(w), i % std::stoi(w)});
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
