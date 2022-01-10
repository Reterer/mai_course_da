import random
N = 100000;
M = 100000;
MIN_VALUE = 1;
MAX_VALUE = 100;

def generate_edge():
    a = random.randint(1, N)
    b = random.randint(1, N)
    while a == b:
        b = random.randint(1, N)
    c = random.randint(MIN_VALUE, MAX_VALUE)
    return f"{a} {b} {c}\n"

with open("rtest.txt", "w") as f:
    f.write(f"{N} {M} {1} {N}\n")
    for _ in range(M):
        f.write(generate_edge())
    f.write(f"{M}\n")