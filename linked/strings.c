#include <stdio.h>
#include <string.h>

# define SIZE 20

int main()
{
    char string1[20] = "testC";
    char string2[20] = "testB";

    
    if (strcmp(string1, string2) == 0)
    {
        printf("strings equal\n");
    }
    else
    {
        if (strcmp(string1, string2) < 0)
        {
            printf("string1 first\n");
        }

        if (strcmp(string1, string2) > 0)
        {
            printf("string2 first\n");
        }
    }
    
    return 0;
}