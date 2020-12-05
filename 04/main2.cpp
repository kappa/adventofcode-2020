#include <algorithm>
#include <iterator>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <regex>
#include <sstream>

using passport_t = std::unordered_map<std::string, std::string>;

bool valid_year(const std::string& str, int min, int max) {
  const static std::regex yr_re("\\d{4}");

  std::smatch m;
  if (std::regex_match(str, m, yr_re)) {
    const int value = std::stoi(m[0]);
    return value >= min && value <= max;
  }

  return false;
}

bool valid_values(const passport_t& passport) {
  if (!valid_year(passport.at("byr"), 1920, 2002))
    return false;
  if (!valid_year(passport.at("iyr"), 2010, 2020))
    return false;
  if (!valid_year(passport.at("eyr"), 2020, 2030))
    return false;

  const std::regex hgt_re("(\\d+)(in|cm)");
  std::smatch m;
  if (std::regex_match(passport.at("hgt"), m, hgt_re)) {
    const int value = std::stoi(m[1]);
    if (m[2] == "in" && (value < 59 || value > 76))
      return false;
    if (m[2] == "cm" && (value < 150 || value > 193))
      return false;
  } else
    return false;

  const std::regex hcl_re("#[0-9a-f]{6}");
  const std::regex ecl_re("amb|blu|brn|gry|grn|hzl|oth");
  const std::regex pid_re("[0-9]{9}");
  if (!std::regex_match(passport.at("hcl"), hcl_re)
      || !std::regex_match(passport.at("ecl"), ecl_re)
      || !std::regex_match(passport.at("pid"), pid_re))
    return false;

  return true;
}

bool is_valid(const passport_t& cur_passport) {
  const static std::unordered_set<std::string> seven_fields{"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};

  std::unordered_set<std::string> cur_fields{};
  for(const auto& pair : cur_passport)
    cur_fields.insert(pair.first);

  return cur_fields == seven_fields && valid_values(cur_passport);
}

int main()
{
  int valid = 0;

  std::unordered_set<std::string> seven_fields{"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
  passport_t cur_passport{};

  std::string line;

  while(std::getline(std::cin, line)) {
    if (line.empty()) {
      if (is_valid(cur_passport))
        ++valid;
      cur_passport.clear();
    } else {
      std::istringstream words(line);
      std::string word = "";
      while (words >> word) {
        const auto key = word.substr(0, 3);
        if (key != "cid")
          cur_passport[key] = word.substr(4);
      }
    }
  }

  if (is_valid(cur_passport))
    ++valid;

  std::cout << valid << "\n";

  return 0;
}
