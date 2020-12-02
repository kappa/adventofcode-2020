#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<int> entries;

  int entry;
  while (cin >> entry) {
    entries.push_back(entry);
  }

  sort(entries.begin(), entries.end());

  for(auto first : entries) {
    if (binary_search(entries.begin(), entries.end(), 2020 - first)) {
      cout << first * (2020 - first) << '\n';
      break;
    }
  }
}
