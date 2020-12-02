#include <algorithm>
#include <iostream>
#include <string>

int main()
{
  std::string line;

  int valid_passwords = 0;
  while (std::getline(std::cin, line)) {
    int first = std::stoi(line);
    int second = std::stoi(std::string(line.begin() + line.find('-') + 1, line.end()));
    char c = line[line.find(':') - 1];
    std::string password = line.substr(line.rfind(' ') + 1);

    if ((password[first - 1] == c) != (password[second - 1] == c)) {
      ++valid_passwords;
    }
  }

  std::cout << valid_passwords << '\n';

  return 0;
}
