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
// #define SIZE 1024

#define SIZE SHRT_MAX

///////////////////////////////////////////////////////////////////////////////
// PRINTING FUNCTIONS /////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void syntax_print()
{
    printf("\n|----------------------------------|\n");
    printf(  "| INVALID CALL ARGUEMENTS          |\n");
    printf(  "| PROPER BENCHMARK SYNTAX:         |\n");
    printf(  "|----------------------------------|\n");
    printf(  "| ./benchmark nxyz [-xX] [--debug] |\n");           
    printf(  "|----------------------------------|\n");
    printf(  "|  size |--------------------------|\n");
    printf(  "|-------|--------------------------|\n");
    printf(  "| n = 0 |   3276 (SHT_MAX / 10)    |\n");
    printf(  "| n = 1 |  32767 (SHT_MAX     )    |\n");
    printf(  "| n = 2 | 327670 (SHT_MAX * 10)    |\n");
    printf(  "|-------|--------------------------|\n");
    printf(  "| range |--------------------------|\n");
    printf(  "|-------|--------------------------|\n");
    printf(  "| x = 0 | unique many              |\n");
    printf(  "| x = 1 | few & large              |\n");
    printf(  "| x = 2 | few & small              |\n");
    printf(  "|-------|--------------------------|\n");
    printf(  "| order |--------------------------|\n");
    printf(  "|-------|--------------------------|\n");
    printf(  "| y = 0 |      unsorted            |\n");
    printf(  "| y = 1 |        sorted            |\n");
    printf(  "| y = 2 | mostly sorted            |\n");
    printf(  "| y = 3 |        sorted reversed   |\n");
    printf(  "| y = 4 | mostly sorted reversed   |\n");
    printf(  "|-------|--------------------------|\n");
    printf(  "|  sort |--------------------------|\n");
    printf(  "|-------|--------------------------|\n");
    printf(  "| z = 0 |                      -   |\n");
    printf(  "| z = 1 |         selection sort   |\n");
    printf(  "| z = 2 |         insertion sort   |\n");
    printf(  "| z = 3 |            bubble sort   |\n");
    printf(  "| z = 4 |              quicksort   |\n");
    printf(  "| z = 5 |                qsort()   |\n");
    printf(  "|-------|--------------------------|\n");
    printf(  "| timer |--------------------------|\n");
    printf(  "|-------|--------------------------|\n");
    printf(  "|   -m2 |       mean time / 3 runs |\n");
    printf(  "|   -c8 | cumulative time / 9 runs |\n");
    printf(  "|----------------------------------|\n");
    printf(  "|       --debug: print arrays      |\n");
    printf(  "|----------------------------------|\n\n");
}

void array_print(long* r, int size)
{
    printf("\n");
    
    for (int i = 0; i < size; i++)
    {
        printf("{%5d} %ld\n", i, r[i]);
    }

    return;
}

///////////////////////////////////////////////////////////////////////////////
// qsort() CMPS ///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int intcmp_asc (const void * a, const void * b) // ascending
{
   return ( *(long*)a - *(long*)b );
}

int intcmp_des (const void * a, const void * b) // descending
{
   return - ( *(long*)a - *(long*)b );
}

///////////////////////////////////////////////////////////////////////////////
// RNG ////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////
// ARRAY CONSTRUCTION /////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////
// SORTING FUNCTIONS //////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int min_value_index(long* r, int size)
{
    int i;
    int min_index;

    if(size == 0) return -1;

    min_index = 0;

    for (i = 1;i < size; i++)
    {
        if (r[i] < r[min_index]) 
        {
            min_index=i;
        }
    }
    
    return min_index;
}

void selection_sort(long* r, int size)
{
    int i;
    int k;

    if(size < 2) return;

    for (i = 0; i < size -1; i++)
    {
        if ((k = i + min_value_index(r + i, size -i)) != i)
        {
            swap(r, i, k);
        }
    }

    return;
}

///////////////////////////////////////////////////////////////////////////////

void insertion_sort(long* r, int size)
{
  
    int i;
    int j;
    
    long rj;

    for (i = 1; i < size; i++)
    {
        rj = r[i];
        
        for (j = i; j >= 0; j--)
        {
            if ((j==0) || (r[j -1] <= (int) rj))
            {
                r[j] = rj;
                break;
            } 
            else
            {
                r[j] = r[j -1];
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////

void bubble_sort(long* r, int size)
{
    int i;
    int j;

    if (size < 2) return;
    
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size -1; j++)
        {
            if (r[j] > r[j +1]) swap(r, j, j +1);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////

int partition(long* r, int size, long pivot)
{
    int partition = 0;
    int i;
    
    for (i = 0; i < size; i++)
    {
        if (r[i] <= pivot)
        {
            if (partition < i)
            {
                swap(r, partition, i);
            }
                
            partition++;
        }
    }
    
    return partition;
}

void quicksort_sort(long* r, int size)
{
    int ptn;

    if(size < 2) return;
    
    ptn = 1 + partition(r +1, size -1, r[0]);
    
    if (ptn > 1)
    {
        swap(r, 0, ptn -1);
    }
        
    quicksort_sort(r, ptn -1);
    quicksort_sort(r + ptn, size - ptn);
}

// </></></></></></></></></></></></></></></></></></></></></></></></></><
// </></></></></></></></></></></></></></></></></></></></></></></></></><
// </></></></></></></></></></></></></></></></></></></></></></></></></><
// </></></></></></></></></></></></></></></></></></></></></></></></></><
// </></></></></></></></></></></></></></></></></></></></></></></></></><

int main(int argc, char *argv[])
{   
    int i;
    int j;

    int size;
    
    int repeats = 1;
    int result = 0;
    
    int mean = 0;
    int cumulative = 0;
    int debug = 0;

    long sum = 0;

    long* r;

    time_t start[9]; 
    time_t end[9];

    if ((argc < 2) || (argc > 4))
    {
        syntax_print();
        return 1;
    }
    else
    {
        switch (argc)
        {
            case 2:

                mean = 0;
                cumulative = 0;
                repeats = 1;
                debug = 0;
                
                break;
            
            case 3:

                if (!strcmp(argv[2], "--debug"))
                {
                    debug = 1;
                    // array_print(r, size);
                }
                else
                {
                    if ((argv[2][0] == '-') && (argv[2][1] == 'm'))
                    {
                        mean = 1;
                        cumulative = 0;

                        if (atoi(&argv[2][2]))
                        {
                            repeats = atoi(&argv[2][2]) +1;
                        }
                        else
                        {
                            repeats = 1;
                        }
                           
                    }
                    else
                    {
                        if ((argv[2][0] == '-') && (argv[2][1] == 'c'))
                        {
                            mean = 0;
                            cumulative = 1;
                            
                            if (atoi(&argv[2][2]))
                            {
                                repeats = atoi(&argv[2][2]) +1;
                            }
                            else
                            {
                                repeats = 1;
                            }
                        }
                        else
                        {
                            syntax_print();
                            return 1;
                        }
                    }
                }

                break;
            
            case 4:

                if ((argv[2][0] == '-') && (argv[2][1] == 'm'))
                {
                    mean = 1;
                    cumulative = 0;

                    if (atoi(&argv[2][2]))
                    {
                        repeats = atoi(&argv[2][2]);
                    }
                    else
                    {
                        repeats = 1;
                    }
                }
                else
                {
                    if ((argv[2][0] == '-') && (argv[2][1] == 'c'))
                    {
                        mean = 0;
                        cumulative = 1;
                        
                        if (atoi(&argv[2][2]))
                        {
                            repeats = atoi(&argv[2][2]);
                        }
                        else
                        {
                            repeats = 1;
                        }
                    }
                    else
                    {
                        syntax_print();
                        return 1;
                    }
                }

                if (!strcmp(argv[3], "--debug"))
                {
                    debug = 1;
                    // array_print(r, size);
                }
                else
                {
                    syntax_print();
                    return 1;
                }
                
                break;
        }
    }

    printf("\n");

    for (j = 0; j < repeats; j++)
    {
        if (j == repeats -1) printf("   runs: %d\n", repeats);
        
        switch (argv[1][0])
        {
            case '0':

                if (j == repeats -1) printf("   size: %d keys\n", SIZE / 10);

                size = SIZE / 10;
                r = (long*)(malloc(size * sizeof(long)));

                switch (argv[1][1])
                {
                    case '0':

                        if (j == repeats -1) printf("  range: [0 - %d]\n", MANY);

                        fill_keys(r, size, MANY, 0);
                        // array_print(r, size);

                        break;

                    case '1':

                        if (j == repeats -1) printf("  range: [%d - %d]\n", MANY-FEW, MANY);

                        fill_keys(r, size, FEW, MANY-FEW);
                        // array_print(r, size);

                        break;

                    case '2':

                        if (j == repeats -1) printf("  range: [0 - %d]\n", FEW);

                        fill_keys(r, size, FEW, 0);
                        // array_print(r, size);

                        break;

                    default:

                        syntax_print();
                        return 1;
                }

                break;

            case '1':

                if (j == repeats -1) printf("   size: %d keys\n", SIZE);

                size = SIZE;
                r = (long*)(malloc(size * sizeof(long)));

                switch (argv[1][1])
                {
                    case '0':

                        if (j == repeats -1) printf("  range: [0 - %d]\n", MANY);

                        fill_keys(r, size, FEW, 0);
                        // array_print(r, size);

                        break;

                    case '1':

                        if (j == repeats -1) printf("  range: [%d - %d]\n", MANY-FEW, MANY);

                        fill_keys(r, size, FEW, MANY-FEW);
                        // array_print(r, size);

                        break;

                    case '2':

                        if (j == repeats -1) printf("  range: [0 - %d]\n", FEW);

                        fill_keys(r, size, FEW, 0);
                        // array_print(r, size);

                        break;

                    default:

                        syntax_print();
                        return 1;
                }
                
                break;

            case '2':

                if (j == repeats -1) printf("   size: %d keys\n", SIZE * 10);
                
                size = SIZE * 10;
                r = (long*)(malloc(size * sizeof(long)));

                switch (argv[1][1])
                {
                    case '0':

                        if (j == repeats -1) printf("  range: [0 - %d]\n", MANY);

                        fill_keys(r, size, MANY, 0);
                        // array_print(r, size);

                        break;

                    case '1':

                        if (j == repeats -1) printf("  range: [%d - %d]\n", MANY-FEW, MANY);

                        fill_keys(r, size, FEW, MANY-FEW);
                        // array_print(r, size);

                        break;

                    case '2':

                        if (j == repeats -1) printf("  range: [0 - %d]\n", FEW);

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

                if (j == repeats -1) printf("  order: unsorted\n");

                break;

            case '1':

                if (j == repeats -1) printf("  order: sorted\n");

                qsort(r, size, sizeof(long), intcmp_asc);
                // array_print(r, size);

                break;

            case '2':

                if (j == repeats -1) printf("  order: mostly sorted\n");

                qsort(r, size, sizeof(long), intcmp_asc);
                // array_print(r, size);

                mostly_unsort(r, size, 3);

                break;

            case '3':

                if (j == repeats -1) printf("  order: sorted reversed\n");

                qsort(r, size, sizeof(long), intcmp_des);
                // array_print(r, size);

                break;

            case '4':

                if (j == repeats -1) printf("  order: mostly sorted reversed\n");

                qsort(r, size, sizeof(long), intcmp_des);
                // array_print(r, size);

                mostly_unsort(r, size, 10);

                break;
            
            default:

                syntax_print();
                return 1;
        }

        switch (argv[1][3])
        {
            case '0':

                if (j == repeats -1) printf("   sort: -\n");

                start[0] = -1;
                end[0] = -1;

                break;

            case '1':

                if (j == repeats -1) printf("   sort: selection\n");

                start[j] = clock();
                selection_sort(r, size);
                end[j] = clock();

                break;

            case '2':

                if (j == repeats -1) printf("   sort: insertion\n");
                
                start[j] = clock();
                insertion_sort(r, size);
                end[j] = clock();

                break;

            case '3':

                if (j == repeats -1) printf("   sort: bubble\n");

                start[j] = clock();
                bubble_sort(r, size);
                end[j] = clock();

                break;

            case '4':

                if (j == repeats -1) printf("   sort: quicksort\n");

                start[j] = clock();
                quicksort_sort(r, size);
                end[j] = clock();

                break;

            case '5':

                if (j == repeats -1) printf("   sort: qsort()\n");

                start[j] = clock();
                qsort(r, size, sizeof(long), intcmp_asc);
                end[j] = clock();
                
                break;
            
            default:

                syntax_print();
                return 1;
        }

        if ((start[0] < 0) && (end[0] < 0))
        {
            if (j == repeats -1) printf("   time: -\n");
            if (j == repeats -1) printf(" result: -\n");
        }
        else
        {
            if (mean)
            {
                if (j == repeats -1) printf("   time: mean\n");

                result = 0;

                for (i = 0; i < repeats; i++)
                {
                    result += (end[i] - start[i]);
                }
                
                if (j == repeats -1) result /= repeats;
                if (j == repeats -1) printf(" result: %f (s)\n", (double) result / CLOCKS_PER_SEC);
            }
            else
            {
                if (cumulative)
                {
                    if (j == repeats -1) printf("   time: cumulative\n");

                    result = 0;

                    for (i = 0; i < repeats; i++)
                    {
                        result += (end[i] - start[i]);
                    }

                    if (j == repeats -1) printf(" result: %f (s)\n", (double) result / CLOCKS_PER_SEC);
                }
                else
                {
                    result = end[0] - start[0];
                    
                    if (j == repeats -1) printf("   time: direct\n");
                    if (j == repeats -1) printf(" result: %f (s)\n", (double) result / CLOCKS_PER_SEC);
                }
            }
        }
        
        if (j == repeats -1) printf("\n");
    }
    
    if (debug)
    {
        array_print(r, size);
        
        printf("\n      mean ? %d\n", mean);
        printf(  "cumulative ? %d\n", cumulative);
        printf(  "   repeats = %d\n\n", repeats);

        if ((start[0] != -1) && (end[0] != -1))
        {
            for (i = 0; i < repeats; i++)
            {
                printf("end[%d]: %ld - start[%d]: %ld = %ld\n", i, end[i], i, start[i], (end[i] - start[i]));
            }

            printf("                             ------------\n");

            for (i = 0; i < repeats; i++)
            {
               sum += end[i] - start[i];
            }

            printf("                          sum = %ld\n", sum);
            printf("                sum / repeats = %ld\n", sum / (long) repeats);

            printf("\n");

        }
    }

    return 0;
}