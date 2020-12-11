#include <iostream>
#include <vector>

struct coords {
  int x;
  int y;
};

std::vector<coords> around(int y, int x, int height, int width) {
  std::vector<coords> rv{};

  for(int yy = y - 1; yy <= y + 1; ++yy)
    for(int xx = x - 1; xx <= x + 1; ++xx)
      if (xx >= 0 && xx < width && yy >= 0 && yy < height && !(xx == x && yy == y))
        rv.push_back(coords{.x=xx, .y=yy});

  return rv;
}

int main()
{
  std::vector<std::vector<char>> next_hall{};
  std::vector<std::vector<char>> hall{};

  std::string line;
  while(std::getline(std::cin, line)) {
    hall.push_back(std::vector<char>(line.begin(), line.end()));
  }
  next_hall = hall;

  bool were_changes = true;
  int occupied;

  while(were_changes) {
    were_changes = false;
    occupied = 0;
    for(int row = 0; row < (int)hall.size(); ++row) {
      for(int col = 0; col < (int)hall[0].size(); ++col) {
        int neighbors = 0;
        for(auto c: around(row, col, (int)hall.size(), (int)hall[0].size())) {
          if (hall[c.y][c.x] == '#')
            ++neighbors;
        }

        if (hall[row][col] == '#' && neighbors >= 4) {
          next_hall[row][col] = 'L';
          were_changes = true;
        } else if (hall[row][col] == 'L' && neighbors == 0) {
          next_hall[row][col] = '#';
          were_changes = true;
        } else
          next_hall[row][col] = hall[row][col];

        if (next_hall[row][col] == '#')
          ++occupied;
      }
    }

    hall = next_hall;
  }

  std::cout << occupied << "\n";

  return 0;
}
