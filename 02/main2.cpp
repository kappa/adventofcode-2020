#include <iostream>

int main()
{
  int valid_passwords = 0;
  for (std::string line; std::getline(std::cin, line);) {
    const int first = std::stoi(line);
    const int second = std::stoi(line.substr(line.find('-') + 1));
    const char c = line[line.find(':') - 1];
    const std::string password = line.substr(line.rfind(' ') + 1);

    if ((password[first - 1] == c) != (password[second - 1] == c))
      ++valid_passwords;
  }

  std::cout << valid_passwords << std::endl;

  return 0;
}
