#include <algorithm>
#include <iostream>
#include <string>

int main()
{
  std::string line;

  int valid_passwords = 0;
  while (std::getline(std::cin, line)) {
    int min = std::stoi(line);
    int max = std::stoi(std::string(line.begin() + line.find('-') + 1, line.end()));
    char c = line[line.find(':') - 1];
    std::string password = line.substr(line.rfind(' ') + 1);

    std::cerr << "MIN: " << min << " MAX: " << max << " C: " << c << " P: " << password;

    int count = std::count(password.begin(), password.end(), c);
    if (count >= min && count <= max) {
      ++valid_passwords;
      std::cerr << " YESSSSSS(" << count << ")\n";
    } else {
      std::cerr << " no\n";
    }
  }

  std::cout << valid_passwords << '\n';

  return 0;
}
