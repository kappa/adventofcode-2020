#include <iostream>
#include <regex>
#include <sstream>
#include <unordered_map>

std::unordered_map<int, std::string> rules;

std::string expand(int n) {
  if (n == 8)
    return expand(42) + "+";

  if (n == 11) {
    std::string rv = "((";
    for (int i = 0; i < 5; ++i) {
      std::string rep = "";
      for (int j = 0; j <= i; ++j)
        rep = expand(42) + rep + expand(31);

      rv += rep + ")|(";
    }

    rv.resize(rv.length() - 2);
    rv += ")";
    return rv;
  }

  const std::string &s = rules[n];

  if (s[0] == '"')
    return std::string{s[1]};

  std::string rv = "(";
  std::istringstream is{s};
  for (std::string w; is >> w;) {
    if (w == "|")
      rv += w;
    else
      rv += expand(std::stoi(w));
  }

  return rv + ")";
}

int main() {
  for (std::string line; std::getline(std::cin, line) && !line.empty();)
    rules.emplace(std::stoi(line), line.substr(line.find(':') + 2));

  std::regex re(expand(0), std::regex::nosubs);

  int count = 0;
  for (std::string line; std::getline(std::cin, line);)
    if (std::regex_match(line, re))
      ++count;

  std::cout << count << std::endl;

  return 0;
}
