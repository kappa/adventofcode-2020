#include <iostream>
#include <regex>
#include <sstream>

int64_t eval(std::string str) {
  int64_t rv = 0;

  std::regex sub_re{"\\([^()]+\\)"};
  std::smatch m{};

  while (std::regex_search(str, m, sub_re)) {
    const std::string in = m[0].str();
    str = m.prefix().str() +
          std::to_string(eval(in.substr(1, in.length() - 2))) +
          m.suffix().str();
  }

  std::regex addition_re{"([0-9]+) \\+ ([0-9]+)"};

  while (std::regex_search(str, m, addition_re))
    str = m.prefix().str() +
          std::to_string(std::stol(m[1].str()) + std::stol(m[2].str())) +
          m.suffix().str();

  std::istringstream is(str);
  char op = '+';
  for (std::string term{}; std::getline(is, term, ' ');) {
    if (term == "+" || term == "*")
      op = term[0];
    else {
      const int64_t n = std::stol(term);
      if (op == '+')
        rv += n;
      else
        rv *= n;
    }
  }

  return rv;
}

int main() {
  int64_t rv = 0;
  for (std::string line; std::getline(std::cin, line);) {
    rv += eval(line);
  }

  std::cout << rv << std::endl;

  return 0;
}
