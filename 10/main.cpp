#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
  std::vector<int> ratings{0};
  std::copy(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), std::back_inserter(ratings));
  std::sort(ratings.begin(), ratings.end());

  // 1 because the last delta is always 3
  int threes = 1, ones = 0;
  for(auto i = ratings.begin(); i < ratings.end() - 1; ++i) {
    if (*(i + 1) - *i == 3)
      ++threes;
    else
      ++ones;
  }

  std::cout << threes * ones << "\n";

  return 0;
}
