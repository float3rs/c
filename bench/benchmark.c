#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define MANY INT_MAX
#define FEW 64

// #define SIZE 524288
// #define SIZE 262144

// #define SIZE SHRT_MAX
#define SIZE 1000

void syntax_print()
{
    printf("\n|--------------------------------|\n");
    printf(  "| INVALID CALL ARGUEMENTS        |\n");
    printf(  "| PROPER BENCHMARK SYNTAX:       |\n");
    printf(  "|--------------------------------|\n");
    printf(  "| ./benchmark nxy [--debug]      |\n");           
    printf(  "|--------------------------------|\n");
    printf(  "|  size |------------------------|\n");
    printf(  "|-------|------------------------|\n");
    printf(  "| n = 0 |   3276 (SHT_MAX / 10)  |\n");
    printf(  "| n = 1 |  32767 (SHT_MAX     )  |\n");
    printf(  "| n = 2 | 327670 (SHT_MAX * 10)  |\n");
    printf(  "|-------|------------------------|\n");
    printf(  "| range |----------------------- |\n");
    printf(  "|-------|------------------------|\n");
    printf(  "| x = 0 | unique many            |\n");
    printf(  "| x = 1 | few & large            |\n");
    printf(  "| x = 2 | few & small            |\n");
    printf(  "|-------|------------------------|\n");
    printf(  "|  sort |------------------------|\n");
    printf(  "|-------|------------------------|\n");
    printf(  "| y = 0 |      unsorted          |\n");
    printf(  "| y = 1 |        sorted          |\n");
    printf(  "| y = 2 | mostly sorted          |\n");
    printf(  "| y = 3 |        sorted reversed |\n");
    printf(  "| y = 4 | mostly sorted reversed |\n");
    printf(  "|--------------------------------|\n");
    printf(  "|       --debug: print arrays    |\n");
    printf(  "|--------------------------------|\n\n");
}

void array_print(long* r, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("{%5d} %ld\n", i, r[i]);
    }

    return;
}

int intcmp_asc (const void * a, const void * b) 
{
   return ( *(long*)a - *(long*)b );
}

int intcmp_des (const void * a, const void * b) 
{
   return - ( *(long*)a - *(long*)b );
}

long rand_int(unsigned long min, unsigned long max)

// https://stackoverflow.com/a/6852396
//
// All the answers so far are mathematically wrong. Returning rand() % N does not 
// uniformly give a number in the range [0, N) unless N divides the length of the 
// interval into which rand() returns (i.e. is a power of 2). Furthermore, one has
// no idea whether the moduli of rand() are independent: it's possible that they 
// go 0, 1, 2, ..., which is uniform but not very random. The only assumption it 
// seems reasonable to make is that rand() puts out a Poisson distribution: any 
// two nonoverlapping subintervals of the same size are equally likely and 
// independent. For a finite set of values, this implies a uniform distribution 
// and also ensures that the values of rand() are nicely scattered.
//
// This means that the only correct way of changing the range of rand() is to 
// divide it into boxes; for example, if RAND_MAX == 11 and you want a range of 
// 1..6, you should assign {0,1} to 1, {2,3} to 2, and so on. These are disjoint, 
// equally-sized intervals and thus are uniformly and independently distributed.

{
    const unsigned long range = max - min + 1;

    if (range < 1)
    {
        fprintf(stderr,"RANGE < 1\n");
        exit(-1);
    }
    
    const unsigned long num_bins = (unsigned long) max + 1;
    const unsigned long num_rand = (unsigned long) RAND_MAX + 1;

    // printf("num_bins: %lu\n", num_bins);
    // printf("num_rand: %lu\n", num_rand);
    
    const unsigned long bin_size = num_rand / num_bins;
    const unsigned long bin_rest = num_rand % num_bins;

    // printf("bin_size: %lu\n", bin_size);
    // printf("bin_rest: %lu\n", bin_rest);
    
    long x;

    do
    {
        x = random();
        
        // printf("random(): %ld\n", x);
    }
    while (num_rand - bin_rest <= (unsigned long) x);

    // printf("num_rand - bin_rest: %ld\n", num_rand - bin_rest);
    
    return (x / bin_size) + min;
}

void fill_keys(long* r, int size, long limit, int offset)
{
    for (int i = 0; i < size; i++)
    {
        r[i] = rand_int(0, limit) + (long) offset;
    }

    return;
}

void swap(long* r, int i, int j)
{
    long buffer;

    buffer = r[i];
    r[i]   = r[j];
    r[j]    = buffer;

    return;
}

void shuffle (long *r, int size) // modified Fisher–Yates shuffle
{
    for (int i = size -1; i > 0; i--)
    {
        int j = (int) rand_int(0, (long) i);
        swap(r, i, j);
    }

    return;
}

void mostly_unsort(long* r, int size, int bucket_size)
{
    int num_buckets = size / bucket_size;
    int bucket = 0;

    for (int i = 0; i + bucket_size < size; i += bucket_size)
    {
        shuffle(r + i, bucket_size);
    }

    return;
}

int main(int argc, char *argv[])
{   
    int i, size;
    long* r;

    if ((argc < 2) || (argc > 3))
    {
        syntax_print();
        return 1;
    }

    switch (argv[1][0])
    {
        case '0':

            printf("> size: %d keys\n", SIZE / 10);

            size = SIZE / 10;
            r = (long*)(malloc(size * sizeof(long)));

            switch (argv[1][1])
            {
                case '0':

                    printf("> range: [0 - %d]\n", MANY);

                    fill_keys(r, size, MANY, 0);
                    // array_print(r, size);

                    break;

                case '1':

                    printf("> range: [%d - %d]\n", MANY-FEW, MANY);

                    fill_keys(r, size, FEW, MANY-FEW);
                    // array_print(r, size);

                    break;

                case '2':

                    printf("> keys: [0 - %d]\n", FEW);

                    fill_keys(r, size, FEW, 0);
                    // array_print(r, size);

                    break;

                default:

                    syntax_print();
                    return 1;
            }

            break;

        case '1':

            printf("> size: %d keys\n", SIZE);

            size = SIZE;
            r = (long*)(malloc(size * sizeof(long)));

            switch (argv[1][1])
            {
                case '0':

                    printf("> range: [0 - %d]\n", MANY);

                    fill_keys(r, size, FEW, 0);
                    // array_print(r, size);

                    break;

                case '1':

                    printf("> keys: [%d - %d]\n", MANY-FEW, MANY);

                    fill_keys(r, size, FEW, MANY-FEW);
                    // array_print(r, size);

                    break;

                case '2':

                    printf("> range: [0 - %d]\n", FEW);

                    fill_keys(r, size, FEW, 0);
                    // array_print(r, size);

                    break;

                default:

                    syntax_print();
                    return 1;
            }
            
            break;

        case '2':

            printf("> size: %d keys\n", SIZE * 10);
            
            size = SIZE * 10;
            r = (long*)(malloc(size * sizeof(long)));

            switch (argv[1][1])
            {
                case '0':

                    printf("> range: [0 - %d]\n", MANY);

                    fill_keys(r, size, MANY, 0);
                    // array_print(r, size);

                    break;

                case '1':

                    printf("> range: [%d - %d]\n", MANY-FEW, MANY);

                    fill_keys(r, size, FEW, MANY-FEW);
                    // array_print(r, size);

                    break;

                case '2':

                    printf("> range: [0 - %d]\n", FEW);

                    fill_keys(r, size, FEW, 0);
                    // array_print(r, size);

                    break;

                default:

                    syntax_print();
                    return 1;
            }
            
            break;

        default:

            syntax_print();
            return 1;
    }

    switch (argv[1][2])
    {
        case '0':

            printf("> sort: unsorted\n");

            break;

        case '1':

            printf("> sort: sorted\n");

            qsort(r, size, sizeof(long), intcmp_asc);
            // array_print(r, size);

            break;

        case '2':

            printf("> sort: mostly sorted\n");

            qsort(r, size, sizeof(long), intcmp_asc);
            // array_print(r, size);

            mostly_unsort(r, size, 3);

            break;

        case '3':

            printf("> sort: sorted reversed\n");

            qsort(r, size, sizeof(long), intcmp_des);
            // array_print(r, size);

            break;

        case '4':

            printf("> sort: mostly sorted reversed\n");

            qsort(r, size, sizeof(long), intcmp_des);
            // array_print(r, size);

            mostly_unsort(r, size, 10);

            break;
        
        default:

            syntax_print();
            return 1;
    }

    if (argc == 3)
    { 
        if (!strcmp(argv[2], "--debug"))
        {
            array_print(r, size);
        }
        else
        {
            syntax_print();
            return 1;
        }
    }

    return 0;
}