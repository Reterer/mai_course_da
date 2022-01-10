import random
N = 10;
M = 100;
MIN_VALUE = -5;
MAX_VALUE = 100;

def generate_seg():
    a = random.randint(MIN_VALUE, MAX_VALUE - 1)
    b = random.randint(a + 1, MAX_VALUE)
    return f"{a} {b}\n";

with open("randomtest5.txt", "w") as f:
    f.write(f"{N}\n")
    for _ in range(N):
        f.write(generate_seg())
    f.write(f"{M}\n")