#include <iostream>
#include <regex>
#include <sstream>
#include <vector>

struct rule_t {
  std::string name;
  int32_t l1, r1, l2, r2;
};

std::vector<rule_t> rules{};
std::vector<int32_t> ticket{};
std::vector<std::vector<int32_t>> others{};

int main() {
  for (std::string line; std::getline(std::cin, line) && !line.empty();) {
    const std::regex rule_r(R"(^([^:]+): +(\d+)-(\d+) or +(\d+)-(\d+)$)");
    std::smatch m;
    if (std::regex_match(line, m, rule_r))
      rules.push_back(rule_t{m[1], std::stoi(m[2]), std::stoi(m[3]),
                             std::stoi(m[4]), std::stoi(m[5])});
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  for (std::string line; std::getline(std::cin, line);) {
    std::istringstream is(line);
    for (std::string w; std::getline(is, w, ',') && !w.empty();)
      ticket.push_back(std::stoi(w));
    break;
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  for (std::string line; std::getline(std::cin, line);) {
    std::istringstream is(line);
    std::vector<int32_t> cur_ticket{};
    for (std::string w; std::getline(is, w, ',');)
      cur_ticket.push_back(std::stoi(w));

    others.push_back(std::move(cur_ticket));
  }

  int32_t rate = 0;
  for (const auto &t : others)
    for (const auto &n : t) {
      for (const auto &r : rules)
        if ((n >= r.l1 && n <= r.r1) || (n >= r.l2 && n <= r.r2))
          goto valid;
      rate += n;
    valid:;
    }

  std::cout << rate << std::endl;

  return 0;
}
