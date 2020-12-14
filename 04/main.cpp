#include <iostream>
#include <set>
#include <sstream>

using passport_t = std::set<std::string>;

bool is_valid(const passport_t &cur_passport) {
  const static passport_t seven_fields{"byr", "iyr", "eyr", "hgt",
                                       "hcl", "ecl", "pid"};

  return cur_passport == seven_fields;
}

int main() {
  int valid = 0;

  passport_t cur_passport{};

  for (std::string line; std::getline(std::cin, line);) {
    if (line.empty()) {
      if (is_valid(cur_passport))
        ++valid;
      cur_passport.clear();
    } else {
      std::istringstream words(line);
      for (std::string word; words >> word;) {
        const auto key = word.substr(0, 3);
        if (key != "cid")
          cur_passport.insert(std::move(key));
      }
    }
  }

  if (is_valid(cur_passport))
    ++valid;

  std::cout << valid << std::endl;

  return 0;
}
