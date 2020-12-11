#include <iostream>
#include <vector>

struct coords {
  int x;
  int y;
};

using hall_t = std::vector<std::vector<char>>;

template <typename T> int sgn(T val) {
  return (T(0) < val) - (val < T(0));
}

std::vector<coords> around(const int y, const int x, const hall_t &hall) {
  std::vector<coords> rv{};

  int height = (int)hall.size();
  int width = (int)hall[0].size();

  for(int dy = -1; dy <= 1; ++dy)
    for(int dx = -1; dx <= 1; ++dx) {
      if (dx == 0 && dy == 0) continue;

      int sx = dx;
      int sy = dy;
      for(;;) {
        if (x + sx >= 0 && x + sx < width && y + sy >= 0 && y + sy < height) {
          if (hall[y + sy][x + sx] != '.') {
            rv.push_back(coords{.x=x + sx, .y=y + sy});
            break;
          }
          else {
            sx += 1 * sgn(sx);
            sy += 1 * sgn(sy);
          }
        }
        else
          break;
      }
    }

  return rv;
}

int main()
{
  hall_t next_hall{};
  hall_t hall{};

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
        for(auto c: around(row, col, hall)) {
          if (hall[c.y][c.x] == '#')
            ++neighbors;
        }

        if (hall[row][col] == '#' && neighbors >= 5) {
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
