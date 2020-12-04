#include <iostream>
#include <unordered_set>
#include <sstream>

int main()
{
  int valid = 0;

  std::unordered_set<std::string> seven_fields{"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };
  std::unordered_set<std::string> cur_passport{};

  std::string line = "";

  while(std::getline(std::cin, line)) {
    if (line.empty()) {
      cur_passport.extract("cid");
      if (cur_passport == seven_fields)
        ++valid;
      cur_passport.clear();
    } else {
      std::istringstream words(line);
      std::string word = "";
      while (words >> word) {
        cur_passport.insert(word.substr(0, 3));
      }
    }
  }

  cur_passport.extract("cid");
  if (cur_passport == seven_fields)
    ++valid;

  std::cout << valid << "\n";

  return 0;
}
