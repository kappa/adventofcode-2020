#include <array>
#include <iostream>
#include <vector>

struct coords {
  int x;
  int y;
};

using hall_t = std::vector<std::vector<char>>;

template <typename T> constexpr int sgn(T val) {
  return (T(0) < val) - (val < T(0));
}

std::vector<coords> around(const int y, const int x, const hall_t &hall) {
  std::vector<coords> rv{};

  const int height = (int)hall.size();
  const int width = (int)hall[0].size();

  for (int dy = -1; dy <= 1; ++dy)
    for (int dx = -1; dx <= 1; ++dx) {
      if (dx == 0 && dy == 0)
        continue;

      int sx = dx;
      int sy = dy;
      for (;;) {
        if (x + sx >= 0 && x + sx < width && y + sy >= 0 && y + sy < height) {
          if (hall[y + sy][x + sx] != '.') {
            rv.push_back(coords{.x = x + sx, .y = y + sy});
            break;
          } else {
            sx += 1 * sgn(sx);
            sy += 1 * sgn(sy);
          }
        } else
          break;
      }
    }

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
        for (auto c : around(row, col, *cur)) {
          if ((*cur)[c.y][c.x] == '#')
            ++neighbors;
        }

        if ((*cur)[row][col] == '#' && neighbors >= 5) {
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
