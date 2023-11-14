#! /bin/bash

make ecosys

if [ $# -eq "1" ]; then
    i=0
    while [ $i -lt $1 ]; do
        ./ecosys
        i=$((i+1))
    done

    python ./stats.py
else

    ./ecosys
    ./plot.py
fi

rm ./data/Eco_Stats.txt
make clean
