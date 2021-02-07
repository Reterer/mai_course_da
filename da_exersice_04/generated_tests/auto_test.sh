#!/bin/bash

for ((i = 0; i < 10; i++))
do
    python3 ./generator.py 
    ../solution/solution < randomtest1000.txt > randomtest1000.txt.res
    if !(diff randomtest1000.txt.ans randomtest1000.txt.res)
    then
        echo "Ох, как больно!"
        break
    fi

done