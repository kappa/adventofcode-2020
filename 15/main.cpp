#include <iostream>
#include <map>
#include <sstream>

int main() {
  std::map<int, int> prev{};
  int num;

  std::istringstream is("8,13,1,0,18,9");
  int start_turn = 1;
  for (std::string line; std::getline(is, line, ','); ++start_turn) {
    num = std::stoi(line);
    prev[num] = start_turn;
  }

  // forget the last one
  prev[num] = 0;

  for (int turn = start_turn; turn <= 30000000; ++turn) {
    if (auto prev_turn = prev[num]; prev_turn) {
      prev[num] = turn - 1;
      num = turn - 1 - prev_turn;
    } else {
      prev[num] = turn - 1;
      num = 0;
    }
  }

  std::cout << num << std::endl;

  return 0;
}
