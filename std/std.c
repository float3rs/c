#include <stdio.h>

#define SIZE 10

struct student 
{
    char first[32];
    char last[32];
    int roll;
    float mark;
};

struct student st[SIZE];

void initarray(struct student *array)
{
    for (int i = 0; i < SIZE; i++)
    {
        array[i].roll = 0;
    }
}

void fillarray(struct student *array)
{
    int ctrl = 2;
    for (int i = 0; i < SIZE; i++)
    {
        
        while (ctrl != 0 && ctrl != 1)
        {
            printf("\n");
            printf("%d RECORDS STORED SO FAR\n", i);
            printf("0 TO BREAK, 1 TO CONTINUE: ");
            scanf("%d", &ctrl);
        }
        
        if (ctrl == 0)
        {
            printf("\n");
            break;
        }

        printf("\n");
        
        printf("\tENTER INFO FOR STUDENT: %d/%d\n", i+1, SIZE);
        printf("\n");
        printf("\t>   FIRST NAME: ");
        scanf("%s", array[i].first);
        printf("\t>    LAST NAME: ");
        scanf("%s", array[i].last);
        printf("\t>    ROLL CODE: ");
        scanf("%d", &array[i].roll);
        printf("\t>   MARK FLOAT: ");
        scanf("%f", &array[i].mark);

        ctrl = 2;
    }
    printf("\n");
}

void printarray(struct student *array)
{
    printf("\n");
    printf("\t PRINTING ARRAY OF STUDENTS\n");
    printf("\n");
    printf("\n");
    printf("A/A \t FIRST            \t LAST             \t ROLL     \t MARK  \n");
    printf("------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < SIZE; i++)
    {
        if (array[i].roll != 0)
        {
            printf("%d \t %-16s \t %-16s \t %-8d \t %2.2f \n", i+1, array[i].first, array[i].last, array[i].roll, array[i].mark);
        }
    }
    printf("\n");
}

int main()
{

    fillarray(st);
    printarray(st);
    return 0;
}

