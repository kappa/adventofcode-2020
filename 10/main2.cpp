#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
  std::vector<int> ratings{0};
  std::copy(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), std::back_inserter(ratings));
  std::sort(ratings.begin(), ratings.end());

  ratings.push_back(ratings.back() + 3);

  int ones = 0;
  long int result = 1;
  for(auto i = ratings.begin(); i < ratings.end() - 1; ++i) {
    const auto delta = (*(i + 1) - *i);
    if (delta == 1)
      ++ones;
    else {
      switch(ones) {
      case 2: result *= 2; break;
      case 3: result *= 4; break;
      case 4: result *= 7; break;
      default:
        ;
      }

      ones = 0;
    }
  }

  std::cout << result << "\n";

  return 0;
}
