#include <forward_list>
#include <iostream>
#include <unordered_map>

typedef std::forward_list<int> ring_t;
typedef ring_t::const_iterator ring_i;

ring_i inc(ring_i cur, const ring_t &ring) {
  if (++cur == ring.cend())
    cur = ring.cbegin();

  return cur;
}

constexpr int dec_v(const int v, const int max, const int delta = 1) {
  return (v - 1 + max - delta) % max + 1;
}

ring_i erase3_after(ring_t &ring, ring_i pos) {
  ring_i after;
  for (auto i = 0; i < 3; ++i) {
    if (std::next(pos) == ring.cend())
      pos = ring.cbefore_begin();
    after = ring.erase_after(pos);
  }

  return after == ring.cend() ? ring.cbegin() : after;
}

int main() {
  ring_t ring = {7, 9, 2, 8, 4, 5, 1, 3, 6};
  ring_i end;
  const int initial_max = 9;
  std::unordered_map<int, ring_i> map = {};

  for (auto el = ring.cbegin(); el != ring.cend(); ++el) {
    map[*el] = el;
    end = el;
  }

  for (auto i = initial_max + 1; i <= 1000000; ++i) {
    end = ring.insert_after(end, i);
    map.insert({i, end});
  }

  ring_i cur = ring.cbegin();
  for (auto t = 0; t < 10000000; ++t) {
    const auto next = inc(cur, ring);
    const auto next_2 = inc(next, ring);
    const auto next_3 = inc(next_2, ring);
    ring_t three{*next, *next_2, *next_3};

    int dest_v = dec_v(*cur, 1000000);
    while (dest_v == *next || dest_v == *next_2 || dest_v == *next_3)
      dest_v = dec_v(dest_v, 1000000);

    const ring_i dest = map[dest_v];

    ring.splice_after(dest, three);
    map[*next] = std::next(dest);
    map[*next_2] = std::next(map[*next]);
    map[*next_3] = std::next(map[*next_2]);

    cur = erase3_after(ring, cur);
  }

  const ring_i one = map[1];
  std::cout << (uint64_t)*std::next(one) * *std::next(std::next(one))
            << std::endl;

  return 0;
}
