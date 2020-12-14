#include <iostream>
#include <set>

int main() {
  std::set<char> cur_group{};
  decltype(cur_group)::size_type total_count = 0;

  for (std::string line; std::getline(std::cin, line);) {
    if (line.empty()) {
      total_count += cur_group.size();
      cur_group.clear();
    } else
      cur_group.insert(line.begin(), line.end());
  }

  total_count += cur_group.size();

  std::cout << total_count << std::endl;

  return 0;
}
