#include <stdio.h>
#include <stdlib.h>

void enter_values(int* array1, int* array2, int* array3, int r1, int c1, int r2, int c2, int r3, int c3)
{
    int i, j;

    for (i = 0; i < r1; i++)
    {
        for (j = 0; j < c1; j++)
        {
            printf("enter array1 value %d x %d: ", i+1, j+1);
            scanf("%d", array1 + (i * c1) + j);
        }
    }

    printf("\n");

    for (i = 0; i < r2; i++)
    {
        for (j = 0; j < c2; j++)
        {
            printf("enter array2 value %d x %d: ", i+1, j+1);
            scanf("%d", array2 + (i * c2) + j);
        }
    }

    printf("\n");

    for (i = 0; i < r3; i++)
    {
        for (j = 0; j < c3; j++)
        {
            *(array3 + (i * c3) + j) = 0;
        }
    }
}

void print_values(int* array, int r, int c)
{
    int i, j;
    
    for (i = 0; i < r; i++)
    {
        printf(" | ");
        for (j = 0; j < c; j++)
        {
            printf(" %5d ", *(array + (i * c) + j));
        }
        printf(" | \n");
    }
}


void multiply(int* array1, int* array2, int* array3, int r1, int c1, int r2, int c2, int r3, int c3)
{
    int sum, i, j, k;

    for (i = 0; i < r3; i++)
    {
        for (j = 0; j < c3; j++)
        {
            sum = 0;

            for (k = 0; k < c1; k++)
            {
                sum += *((array1 + (i*c1)) + k) * *(array2 + (k*c2) + j);
            }

            *((array3 + (i*c3)) + j) = sum;
        }
    }
}

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void selectionSort(int array[], int size) {
  for (int step = 0; step < size - 1; step++) {
    int min_idx = step;
    for (int i = step + 1; i < size; i++) {

      // To sort in descending order, change > to < in this line.
      // Select the minimum element in each loop.
      if (array[i] < array[min_idx])
        min_idx = i;
    }

    // put min at the correct position
    swap(&array[min_idx], &array[step]);
  }
}








int main() 
{
    int r1, c1, r2, c2, r3, c3;

    printf("Enter rows and column for the first matrix: ");
    scanf("%d %d", &r1, &c1);
    printf("Enter rows and column for the second matrix: ");
    scanf("%d %d", &r2, &c2);

    // Taking input until columns of the first matrix is equal to the rows of the second matrix
    while (c1 != r2) 
    {
        printf("Error! Enter rows and columns again.\n");
        printf("Enter rows and columns for the first matrix: ");
        scanf("%d%d", &r1, &c1);
        printf("Enter rows and columns for the second matrix: ");
        scanf("%d%d", &r2, &c2);
    }

    r3 = r1;
    c3 = c2;

    int* array1 = (int*) malloc(r1 * c1 * sizeof(int));
    int* array2 = (int*) malloc(r2 * c2 * sizeof(int));
    int* array3 = (int*) malloc(r3 * c3 * sizeof(int));

    if ((array1 == NULL) || (array1 == NULL) || (array3 == NULL))                      
    {
        printf("Error! memory not allocated.");
        exit(0);
    }

    enter_values(array1, array2, array3, r1, c1, r2, c2, r3, c3);
    printf("\n");
    print_values(array1, r1, c1);
    printf("\n");
    print_values(array2, r2, c2);
    printf("\n");
    print_values(array3, r3, c3);

    multiply(array1, array2, array3, r1, c1, r2, c2, r3, c3);

    printf("\n");
    print_values(array3, r3, c3);

    selectionSort(array3, r3*c3);

    printf("\n");
    print_values(array3, r3, c3);

    return 0;
}