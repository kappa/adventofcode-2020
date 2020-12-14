#include <iostream>
#include <iterator>
#include <sstream>
#include <map>
#include <set>
#include <vector>

using bag_t = std::string;
using bag_set_t = std::set<bag_t>;
using bag_tree_t = std::map<bag_t, std::vector<bag_t>>;

bag_set_t traverse(const bag_tree_t &tree, const bag_t bag) {
  bag_set_t set{};

  if (const auto found = tree.find(bag); found != tree.end())
    for (auto next_bag : found->second) {
      set.insert(next_bag);
      const auto subset = traverse(tree, next_bag);
      set.insert(subset.cbegin(), subset.cend());
    }

  return set;
}

int main() {
  bag_tree_t bag_tree{};

  for (std::string line; std::getline(std::cin, line);) {
    std::istringstream is{line};
    const std::vector<bag_t> words{std::istream_iterator<bag_t>(is),
                                   std::istream_iterator<bag_t>()};

    if (words[4] == "no")
      continue;

    const bag_t to = words[0] + " " + words[1];

    for (decltype(words)::size_type i = 5; i < words.size(); i += 4) {
      const bag_t from = words[i] + " " + words[i + 1];
      if (auto vec = bag_tree.find(from); vec != bag_tree.end())
        vec->second.push_back(to);
      else
        bag_tree.emplace(from, std::vector{to});
    }
  }

  const auto result = traverse(bag_tree, "shiny gold");

  std::cout << result.size() << std::endl;

  return 0;
}
