#include <array>
#include <iostream>
#include <vector>

struct coords {
  int x;
  int y;
};

std::vector<coords> around(const int y, const int x, const int height,
                           const int width) {
  std::vector<coords> rv{};

  for (int yy = y - 1; yy <= y + 1; ++yy)
    for (int xx = x - 1; xx <= x + 1; ++xx)
      if (xx >= 0 && xx < width && yy >= 0 && yy < height &&
          !(xx == x && yy == y))
        rv.push_back(coords{xx, yy});

  return rv;
}

int main() {
  std::array<std::vector<std::vector<char>>, 2> _halls{};

  for (std::string line; std::getline(std::cin, line);)
    _halls[0].push_back(std::vector<char>(line.begin(), line.end()));
  _halls[1] = _halls[0];

  auto *cur = &_halls[0], *next = &_halls[1];

  const auto height = (int)cur->size();
  const auto width = (int)(*cur)[0].size();

  bool were_changes = true;
  int occupied;

  while (were_changes) {
    were_changes = false;
    occupied = 0;
    for (int row = 0; row < height; ++row) {
      for (int col = 0; col < width; ++col) {
        int neighbors = 0;
        for (auto c : around(row, col, height, width)) {
          if ((*cur)[c.y][c.x] == '#')
            ++neighbors;
        }

        if ((*cur)[row][col] == '#' && neighbors >= 4) {
          (*next)[row][col] = 'L';
          were_changes = true;
        } else if ((*cur)[row][col] == 'L' && neighbors == 0) {
          (*next)[row][col] = '#';
          were_changes = true;
        } else
          (*next)[row][col] = (*cur)[row][col];

        if ((*next)[row][col] == '#')
          ++occupied;
      }
    }

    std::swap(cur, next);
  }

  std::cout << occupied << std::endl;

  return 0;
}
