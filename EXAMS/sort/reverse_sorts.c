#include <stdio.h>

void bubble_sort(int list[], int n)
{
  int i, c, d, t;
  int count = 0;

  for (c = 0 ; c < n - 1; c++) 
  {
    for (d = 0 ; d < n - c - 1; d++) 
    {
      if (list[d] > list[d+1]) 
      {
        /* Swapping */
        t         = list[d];
        list[d]   = list[d+1];
        list[d+1] = t;
      }
    }
    
    printf("STEP: %d\n", ++count);
    
    for (i=0; i<n; i++)
    {    
      printf("%d\n", list[i]);     
    }
    printf("--------\n");
  }
}

void reverse_bubble_sort(int list[], int n)
{
  int i, c, d, t;
  int count = 0;

  for (c = 0 ; c < n - 1; c++) 
  {
    for (d = 0 ; d < n - c - 1; d++) 
    {
      if (list[d] < list[d+1]) 
      {
        /* Swapping */
        t         = list[d];
        list[d]   = list[d+1];
        list[d+1] = t;
      }
    }
    
    printf("STEP: %d\n", ++count);
    
    for (i=0; i<n; i++)
    {    
      printf("%d\n", list[i]);     
    }
    printf("--------\n");
  }
}

void sortbyshaker(int *a, int n)
{ int count = 0;
  int *left = a, *right = a+n-1, *start = a, *p, *q, h;
  do { for(p = left; p<right; p++)
	{ q = p + 1;
	  if (*p > *q)
	  { h = *q; *q = *p; *p = h;
	    start = p;
	  }
	}
       right = start;
       for(p = right; p>left; p--)
	{ q = p - 1;
	  if (*q > *p)
	  { h = *q; *q = *p; *p = h;
	    start = p;
	  }
	}
	left = start;
  
  printf("STEP: %d\n", ++count);
    
    for (int i=0; i<n; i++)
    {    
      printf("%d\n", a[i]);     
    }
    printf("--------\n");

  }while (left < right);
  return ;
}

void reverse_sortbyshaker(int *a, int n)
{ int count = 0;
  int *left = a, *right = a+n-1, *start = a, *p, *q, h;
  do { for(p = left; p<right; p++)
	{ q = p + 1;
	  if (*p < *q)
	  { h = *q; *q = *p; *p = h;
	    start = p;
	  }
	}
       right = start;
       for(p = right; p>left; p--)
	{ q = p - 1;
	  if (*q < *p)
	  { h = *q; *q = *p; *p = h;
	    start = p;
	  }
	}
	left = start;
  
  printf("STEP: %d\n", ++count);
    
    for (int i=0; i<n; i++)
    {    
      printf("%d\n", a[i]);     
    }
    printf("--------\n");

  }while (left < right);
  return ;
}

void quicksort(int *left, int *right, int array[], int size)
{ int *p=left, *q=right, h, x=*(left+(right-left>>1));
  do{ while(*p<x) 
        p++;
	while(*q>x) 
        q--;
	if (p>q) 
        break; 
	h=*p; *p=*q; *q=h;
    
    for (int i=0; i<size; i++)
    {    
      printf("%d\n", array[i]);     
    }
    printf("--------\n");

  }while (++p<=--q);
  if (left<q)  
    quicksort(left, q, array, size);
  if (p<right) 
    quicksort(p, right, array, size);
  return ;
}

#include <stdlib.h>

void swap(int Array[], int one, int two) {
    int temp = Array[one];
    Array[one] = Array[two];
    Array[two] = temp;
}

int partition(int Array[], int left, int right) {
    int pivot = Array[right];
    int leftPointer = left - 1;
    int rightPointer = right;
    for (;;) {
        while (Array[++leftPointer] > pivot) {
        }
        while (rightPointer > 0 && Array[--rightPointer] < pivot) {
        }
        if (leftPointer >= rightPointer) {
            break;
        } else {
            swap(Array, leftPointer, rightPointer);
        }
    }
    /* move pivot to partition point */
    swap(Array, leftPointer, right);
    return leftPointer;
}

void reverse_quicksort(int Array[], int left, int right) {
    if (left < right) {
        int PartitionPoint = partition(Array, left, right);
        reverse_quicksort(Array, left, PartitionPoint - 1);
        reverse_quicksort(Array, PartitionPoint + 1, right);
    }
}

void sortbyselection(int a[], int n)
{
  int count = 0;
  int i, j, k, min;
  for(i=0; i<n-1; i++)
  {
    k=i; min=a[k];
    for (j=i+1;j<n;j++)
      if (a[j]<min)
	  {
	    k=j;
	    min=a[k];
	  }
    a[k]=a[i];
    a[i]=min;

    printf("STEP: %d\n", ++count);
    
    for (int j=0; j<n; j++)
    {    
      printf("%d\n", a[j]);     
    }
    printf("--------\n");
  }
  return;
}

void reverse_sortbyselection(int a[], int n)
{
  int count = 0;
  int i, j, k, min;
  for(i=0; i<n-1; i++)
  {
    k=i; min=a[k];
    for (j=i+1;j<n;j++)
      if (a[j]>min)
	  {
	    k=j;
	    min=a[k];
	  }
    a[k]=a[i];
    a[i]=min;

    printf("STEP: %d\n", ++count);
    
    for (int j=0; j<n; j++)
    {    
      printf("%d\n", a[j]);     
    }
    printf("--------\n");
  }
  return;
}

int main()
{
  
  // CHANGE THESE VALUES!
  int array[7] = {3,8,1,7,9,3,4};
  int size = 7;

  
  printf("START\n");
  for (int i = 0; i < size; i++)
     printf("%d\n", array[i]);
  printf("--------\n");
  
  //bubble_sort(array, size);
  reverse_bubble_sort(array, size);
  //sortbyshaker(array, size);
  //reverse_sortbyshaker(array, size);
  //quicksort(array, array+(size-1), array, size);
  //reverse_quicksort(array, 0, size);
  //sortbyselection(array, size);
  //reverse_sortbyselection(array, size);
  
  printf("FINAL\n");
  for (int i = 0; i < size; i++)
     printf("%d\n", array[i]);
  printf("--------\n");

  return 0;
}

