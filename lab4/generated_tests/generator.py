import random
import re

# random.seed(42)
UNIC_WORD = 4
MAX_LEN_WORD = 1
LEN_TEXT = 10000
LEN_PATTERN = 5

def generate_word():
    alpha = [chr(i) for i in range(ord('a'), ord('z'))]
    random.shuffle(alpha)
    return ''.join([random.choice(alpha) for _ in range(random.randint(1, MAX_LEN_WORD))])

def generate_str(words, len_str):
    return [random.choice(words) for _ in range(len_str)]

# Создаем слова
words = []
for i in range(UNIC_WORD):
    word = generate_word()
    while(word in words):
        word = generate_word()
    words.append(word)

text = ' '.join(generate_str(words, LEN_TEXT))
pattern = ' '.join(generate_str(words, LEN_PATTERN))


with open("randomtest1000.txt", "w") as f:
    f.write(pattern + '\n')
    f.write(text + "\n\n")
with open("randomtest1000.txt.ans", "w") as f:
    res = [i.start()//2 for i in re.finditer(f"(?={pattern})", text)]
    for r in res:
        f.write(f"1, {r+1}\n")