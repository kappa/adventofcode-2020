#include <iostream>
#include <iterator>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using bag_t = std::string;
using bags_t = std::vector<std::tuple<int, bag_t>>;
using bag_tree_t = std::unordered_map<bag_t, bags_t>;

int traverse(bag_tree_t& tree, const bag_t bag) {
  int rv = 1;

  if (auto found = tree.find(bag); found != tree.end()) {
    for(auto next_bag : found->second)
      rv += std::get<0>(next_bag) * traverse(tree, std::get<1>(next_bag));
  }

  return rv;
}

int main()
{
  bag_tree_t bag_tree{};

  std::string line;
  while(std::getline(std::cin, line)) {
    std::istringstream is{line};
    const std::vector<bag_t> words{std::istream_iterator<bag_t>(is), std::istream_iterator<bag_t>()};

    if (words[4] == "no") continue;

    const bag_t outside = words[0] + " " + words[1];

    std::vector<std::tuple<int, bag_t>> inside{};
    for(decltype(words)::size_type i = 4; i < words.size(); i += 4)
      inside.push_back(std::make_tuple(std::stoi(words[i]), words[i + 1] + " " + words[i + 2]));

    bag_tree.emplace(outside, inside);
  }

  // - 1 to remove "shiny gold" itself
  const int result = traverse(bag_tree, "shiny gold") - 1;

  std::cout << result << std::endl;

  return 0;
}
