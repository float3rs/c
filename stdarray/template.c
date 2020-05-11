#include <stdio.h>

#define SIZE 10

struct student {
    char first[32];
    char last[32];
    int roll;
    float mark;
} s[SIZE];


int main()
{
    int i;
    printf("Enter information of students:\n");

    // storing information
    for (i = 0; i < 5; ++i) {
        s[i].roll = i + 1;
        printf("\nFor roll number%d,\n", s[i].roll);
        printf("Enter first name: ");
        scanf("%s", s[i].first);
        printf("Enter last name: ");
        scanf("%s", s[i].last);
        printf("Enter mark: ");
        scanf("%f", &s[i].mark);
    }
    printf("Displaying Information:\n\n");

    // displaying information
    for (i = 0; i < 5; ++i) {
        printf("\nRoll number: %d\n", i + 1);
        printf("First name: ");
        puts(s[i].first);
        printf("Last name: ");
        puts(s[i].last);
        printf("Mark: %.1f", s[i].mark);
        printf("\n");
    }



    return 0;
}

