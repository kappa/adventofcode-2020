#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>

std::map<std::string, std::set<std::string>> a2i{};
std::vector<std::string> all_i_orig{};
std::set<std::string> all_i{};

int main() {
  for (std::string line; std::getline(std::cin, line);) {
    std::istringstream is(line);
    std::set<std::string> i{};
    bool allergens = false;
    for (std::string w; is >> w;) {
      if (allergens) {
        w.resize(w.length() - 1);
        if (const auto &kv = a2i.find(w); kv != a2i.end()) {
          std::set<std::string> intersection{};
          const std::set<std::string> &prev = kv->second;
          std::set_intersection(
              i.cbegin(), i.cend(), prev.cbegin(), prev.cend(),
              std::inserter(intersection, intersection.begin()));
          kv->second = intersection;
        } else {
          a2i.emplace(w, i);
        }
      } else if (w == "(contains") {
        allergens = true;
      } else {
        i.insert(w);
        all_i.insert(w);
        all_i_orig.push_back(w);
      }
    }
  }

  for (const auto &ai : a2i) {
    std::set<std::string> rest{};
    std::set_difference(all_i.cbegin(), all_i.cend(), ai.second.cbegin(),
                        ai.second.cend(), std::inserter(rest, rest.begin()));

    all_i = rest;
  }

  int count = 0;
  for (auto i : all_i_orig)
    if (all_i.count(i))
      ++count;

  std::cout << count << std::endl;

  return 0;
}
