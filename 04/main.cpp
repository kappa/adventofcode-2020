#include <iostream>
#include <unordered_set>
#include <sstream>

using passport_t = std::unordered_set<std::string>;

bool is_valid(const passport_t& cur_passport) {
  const static passport_t seven_fields{"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};

  return cur_passport == seven_fields;
}

int main()
{
  int valid = 0;

  std::unordered_set<std::string> cur_passport{};

  std::string line;

  while(std::getline(std::cin, line)) {
    if (line.empty()) {
      if (is_valid(cur_passport)) ++valid;
      cur_passport.clear();
    } else {
      std::istringstream words(line);
      std::string word;
      while (words >> word) {
        const auto key = word.substr(0, 3);
        if (key != "cid") cur_passport.insert(key);
      }
    }
  }

  if (is_valid(cur_passport)) ++valid;

  std::cout << valid << "\n";

  return 0;
}
