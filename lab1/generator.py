#! /usr/bin/env python3

import sys
import random
import string

TEST_COUNT = 6

def get_random_date():
    day = random.randint(1,31)
    month = random.randint(1,12)
    year = random.randint(1,9999)
    return (day, month, year)

def get_random_number():
    return random.randint(0, 2**64 - 1)

def get_string(date, number):
    return f"{date[0]}.{date[1]}.{date[2]} {number}"

def main():
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <test directory>")
        sys.exit(1)

    test_dir = sys.argv[1]

    for test_count in range(1, TEST_COUNT+1):
        test = []
        answer = []

        lines_count = 10 ** test_count
        for _ in range(lines_count):
            key = get_random_date()
            value = get_random_number()
            test.append((key, value))
        
        test_name = "{}/{:02d}".format(test_dir, test_count)
        with open(f'{test_name}.t', 'w') as ftest:
            for key, value in test:
                ftest.write(get_string(key, value) + '\n')

        answer = sorted(test, key=lambda x: x[0][0] + ( x[0][1] + x[0][2] * 12) * 31)
        with open(f'{test_name}.a', 'w') as ftest:
            for key, value in answer:
                ftest.write(get_string(key, value) + '\n')
main()