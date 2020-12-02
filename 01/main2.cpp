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
    for(auto second : entries) {
      if (binary_search(entries.begin(), entries.end(), 2020 - first - second)) {
        cout << first * second * (2020 - first - second) << '\n';
        goto end;
      }
    }
  }
 end:

  return 0;
}
