from z3 import *
from sys import stdin

ts = int(stdin.readline())
buses = [ int(b) for b in stdin.readline().split(',') if b != "x" ]

s = Optimize()

rv = Int("rv")

s.add(rv > ts)

bus_fs = []
for i in range(len(buses)):
    bus_fs.append(Bool(f"bus_{i}"))
    s.add(bus_fs[i] == (rv % buses[i] == 0))

s.add(Or([ bus_f for bus_f in bus_fs]))

s.minimize(rv)

if s.check() == sat:
    m = s.model()
    print(m[rv])
    for i in range(len(buses)):
        if m[bus_fs[i]]:
            print(f"bus = {buses[i]}")
            bus = buses[i]

    result = (m[rv].as_long() - ts) * bus
    print(f"result = {result}")
