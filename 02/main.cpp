#include <algorithm>
#include <iostream>

int main() {
  int valid_passwords = 0;
  for (std::string line; std::getline(std::cin, line);) {
    const int min = std::stoi(line);
    const int max = std::stoi(line.substr(line.find('-') + 1));
    const char c = line[line.find(':') - 1];
    const std::string password = line.substr(line.rfind(' ') + 1);

    const auto count = std::count(password.begin(), password.end(), c);
    if (count >= min && count <= max)
      ++valid_passwords;
  }

  std::cout << valid_passwords << std::endl;

  return 0;
}
