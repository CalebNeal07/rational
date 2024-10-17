from collections import deque
from itertools import islice, count

n = 33

def fusc():
    q = deque([1])
    yield 0
    yield 1

    while True:
        x = q.popleft()
        q.append(x)
        yield x

        x += q[0]
        q.append(x)
        yield x

# Generates the members of stern's diatomic sequence up to n
sds = list(islice(fusc(), n)) 

print(sds)

for i in range(n - 1):
    print(f"\\frac{{{sds[i]}}}{{{sds[i + 1]}}}", end=", ")

