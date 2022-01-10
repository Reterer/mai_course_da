import random
N = 100;
M = 100;
zero_chance = 0.3;

with open("randomtest10.txt", "w") as f:
    f.write(str(N) + ' ' + str(M) + "\n")
    for _ in range(N) :
        f.write(''.join(['0' if random.random() < zero_chance else '1' for _ in range(M)]) + '\n')