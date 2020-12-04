#include <algorithm>
#include <iterator>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <regex>
#include <sstream>

using passport_t = std::unordered_map<std::string, std::string>;

bool valid_values(passport_t passport) {
  const std::regex yr_re("\\d{4}");

  const std::regex hgt_re("(\\d+)(in|cm)");

  std::smatch m;

  if (std::regex_match(passport["byr"], m, yr_re)) {
    int value = std::stoi(m[0]);
    if (value < 1920 || value > 2002)
      return false;
  }

  if (std::regex_match(passport["iyr"], m, yr_re)) {
    int value = std::stoi(m[0].str());
    if (value < 2010 || value > 2020)
      return false;
  }

  if (std::regex_match(passport["eyr"], m, yr_re)) {
    int value = std::stoi(m[0].str());
    if (value < 2020 || value > 2030)
      return false;
  }

  if (std::regex_match(passport["hgt"], m, hgt_re)) {
    int value = std::stoi(m[1].str());
    if (m[2].str() == "in" && (value < 59 || value > 76))
      return false;
    if (m[2].str() == "cm" && (value < 150 || value > 193))
      return false;
  } else {
    return false;
  }

  const std::regex hcl_re("#[0-9a-f]{6}");
  const std::regex ecl_re("amb|blu|brn|gry|grn|hzl|oth");
  const std::regex pid_re("[0-9]{9}");

  if (!std::regex_match(passport["hcl"], hcl_re))
    return false;
  if (!std::regex_match(passport["ecl"], ecl_re))
    return false;
  if (!std::regex_match(passport["pid"], pid_re))
    return false;

  return true;
}

int main()
{
  int valid = 0;

  std::unordered_set<std::string> seven_fields{"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
  passport_t cur_passport{};

  std::string line = "";

  while(std::getline(std::cin, line)) {
    if (line.empty()) {
      cur_passport.extract("cid");

      std::unordered_set<std::string> cur_fields{};
      for(const auto& pair : cur_passport)
        cur_fields.insert(pair.first);

      if (cur_fields == seven_fields && valid_values(cur_passport))
        ++valid;
      cur_passport.clear();
    } else {
      std::istringstream words(line);
      std::string word = "";
      while (words >> word) {
        cur_passport[word.substr(0, 3)] = word.substr(4);
      }
    }
  }

  cur_passport.extract("cid");

  std::unordered_set<std::string> cur_fields{};
  for(const auto& pair : cur_passport)
    cur_fields.insert(pair.first);

  if (cur_fields == seven_fields && valid_values(cur_passport))
    ++valid;

  std::cout << valid << "\n";

  return 0;
}
