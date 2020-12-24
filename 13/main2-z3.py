from z3 import *
from sys import stdin

stdin.readline()
buses = stdin.readline().split(',')

s = Optimize()

t = Int("t")

for i in range(len(buses)):
    if buses[i] != "x":
        s.add((t + i) % int(buses[i]) == 0)

s.minimize(t)

if s.check() == sat:
    m = s.model()
    print(m[t])
