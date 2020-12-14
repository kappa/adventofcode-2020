#include <algorithm>
#include <iostream>
#include <set>

int main() {
  std::set<char> cur_group{};
  decltype(cur_group)::size_type total_count = 0;
  bool first_in_group = true;

  for (std::string line; std::getline(std::cin, line);) {
    if (line.empty()) {
      total_count += cur_group.size();
      cur_group.clear();
      first_in_group = true;
    } else {
      if (first_in_group) {
        cur_group.insert(line.begin(), line.end());
        first_in_group = false;
      } else {
        const std::set<char> cur_person{line.begin(), line.end()};
        std::set<char> result{};
        std::set_intersection(cur_person.cbegin(), cur_person.cend(),
                              cur_group.cbegin(), cur_group.cend(),
                              std::inserter(result, result.begin()));
        cur_group = std::move(result);
      }
    }
  }

  total_count += cur_group.size();

  std::cout << total_count << std::endl;

  return 0;
}
