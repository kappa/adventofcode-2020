#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

int main() {
  istream_iterator<int> begin(cin), end;
  vector<int> entries(begin, end);

  sort(entries.begin(), entries.end());

  for(auto first : entries) {
    if (binary_search(entries.begin(), entries.end(), 2020 - first)) {
      cout << first * (2020 - first) << '\n';
      break;
    }
  }
}
