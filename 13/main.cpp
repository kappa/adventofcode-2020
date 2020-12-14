#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

int main() {
  const int delay{*std::istream_iterator<int>(std::cin)};

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::vector<int> buses;
  for (std::string w; std::getline(std::cin, w, ',');) {
    if (w == "x")
      continue;
    const int bus = std::stoi(w);
    buses.push_back(bus);
  }

  int rv = 0;
  int min = delay;
  for (auto bus : buses) {
    if (delay % bus == 0) {
      rv = bus;
      break;
    }
    auto wait = delay / bus * bus + bus - delay;
    if (wait < min) {
      min = wait;
      rv = bus * wait;
    }
  }

  std::cout << rv << std::endl;

  return 0;
}
