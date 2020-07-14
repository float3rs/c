#!/bin/zsh

> ./output.txt

for BENCH_SIZE in {0..2}
do
    for BENCH_RANGE in {0..2}
    do
        for BENCH_ORDER in {0..4}
        do
            for BENCH_SORT in {0..5}
            do

                echo ""                                                        | tee -a ./output.txt
                echo "> $BENCH_SIZE$BENCH_RANGE$BENCH_ORDER$BENCH_SORT:"       | tee -a ./output.txt
                echo ""                                                        | tee -a ./output.txt
                
                ./benchmark $BENCH_SIZE$BENCH_RANGE$BENCH_ORDER$BENCH_SORT -m2 | tee -a ./output.txt

            done
        done
    done
done