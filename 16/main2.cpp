#include <iostream>
#include <regex>
#include <set>
#include <sstream>
#include <vector>

struct rule_t {
  std::string name;
  int32_t l1, r1, l2, r2;
  std::set<size_t> candidates;
};

std::vector<rule_t> rules{};
std::vector<int32_t> ticket{};
std::vector<std::vector<int32_t>> others{};

int main() {
  for (std::string line; std::getline(std::cin, line) && !line.empty();) {
    const std::regex rule_r(R"(^([^:]+): +(\d+)-(\d+) or +(\d+)-(\d+)$)");
    std::smatch m;
    if (std::regex_match(line, m, rule_r)) {
      rules.push_back(rule_t{m[1],
                             std::stoi(m[2]),
                             std::stoi(m[3]),
                             std::stoi(m[4]),
                             std::stoi(m[5]),
                             {}});
    }
  }
  std::set<size_t> all{};
  for (size_t i = 0; i < rules.size(); ++i)
    all.insert(i);

  for (auto &r : rules)
    r.candidates = all;

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  for (std::string line; std::getline(std::cin, line);) {
    std::istringstream is(line);
    for (std::string w; std::getline(is, w, ',') && !w.empty();) {
      ticket.push_back(std::stoi(w));
    }
    break;
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  for (std::string line; std::getline(std::cin, line);) {
    std::istringstream is(line);
    std::vector<int32_t> cur_ticket{};
    for (std::string w; std::getline(is, w, ',');) {
      const int32_t n = std::stoi(w);
      for (const auto &r : rules)
        if ((n >= r.l1 && n <= r.r1) || (n >= r.l2 && n <= r.r2))
          goto valid;
      goto invalid;

    valid:
      cur_ticket.push_back(std::stoi(w));
    }

    for (size_t i = 0; i < cur_ticket.size(); ++i)
      for (auto &r : rules)
        if (const auto n = cur_ticket[i];
            (n < r.l1 || n > r.r1) && (n < r.l2 || n > r.r2))
          r.candidates.erase(i);

    others.push_back(std::move(cur_ticket));
  invalid:;
  }

  bool changed = true;
  std::set<size_t> fixed{};
  while (changed) {
    size_t one;
    changed = false;

    for (size_t i = 0; i < rules.size(); ++i) {
      const auto &r = rules[i];
      if (r.candidates.size() == 1 && !fixed.count(i)) {
        one = i;
        break;
      }
    }

    for (auto &r : rules) {
      if (r.candidates.size() > 1) {
        r.candidates.erase(*(rules[one].candidates.cbegin()));
        changed = true;
      }
    }

    fixed.insert(one);
  }

  int64_t rv = 1;
  for (const auto &r : rules)
    if (r.name.substr(0, 9) == "departure")
      rv *= ticket[*r.candidates.cbegin()];

  std::cout << rv << std::endl;

  return 0;
}
