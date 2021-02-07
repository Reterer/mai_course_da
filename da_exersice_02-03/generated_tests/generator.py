import random 

random.seed(42)
MAX_LEN_WORD = 10
MAX_NUMBER = 1000
COMMANDS = 10000

def generate_name():
    alpha = [chr(i) for i in range(ord('a'), ord('z'))]
    random.shuffle(alpha)
    return ''.join([random.choice(alpha) for _ in range(random.randint(1,MAX_LEN_WORD))])

# Создает пару имя:число
def generate_word():
    return (generate_name(), random.randint(0, MAX_NUMBER))

# Создаем названия и значения слов
words = [generate_word() for i in range(COMMANDS)]

# Создаем список команд
commands = []
for _ in range(COMMANDS):
    word = random.choice(words)
    commands.append(f"+ {word[0]} {word[1]}")
    commands.append(f"{word[0]}")
    commands.append(f"- {word[0]}")

random.shuffle(commands)

with open("randomtest10000.txt", "w") as f:
    f.write('\n'.join(commands))