#include <algorithm>
#include <iostream>
#include <string>

int main()
{
  std::string line;

  int valid_passwords = 0;
  while (std::getline(std::cin, line)) {
    const int min = std::stoi(line);
    const int max = std::stoi(std::string(line.begin() + line.find('-') + 1, line.end()));
    const char c = line[line.find(':') - 1];
    const std::string password = line.substr(line.rfind(' ') + 1);

    const auto count = std::count(password.begin(), password.end(), c);
    if (count >= min && count <= max)
      ++valid_passwords;
  }

  std::cout << valid_passwords << '\n';

  return 0;
}
