#include <stdio.h>

#define SIZE 10

struct student 
{
    char first[16];
    char last[16];
    int roll;
    float mark;
};

void initarray(struct student *array)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            array[i].first[j] = '-';
            array[i].last[j] = '-';
        }
        
        array[i].roll = 0;
        array[i].mark = 0;
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

int file_detected(char *filename)
{
    FILE *fptr;
    fptr = fopen(filename, "r");
    
    if(fptr == NULL)
    {  
        return 0;             
    }

    fclose(fptr);
    return 1;
}

int main()
{
    struct student st[SIZE];
    struct student rc[SIZE];
    
    char ans = 'z';
    char buffer[128];

    int i;

    FILE *fp;

    initarray(st);
    initarray(rc);

    if (file_detected("record.txt"))
    {
        printf("\n");
        printf("\n");
        printf("\t >>>> FILE RECORD DETECTED\n");
        printf("\n");
        
        while (ans != 'r' && ans != 'd' && ans != 'w' && ans != 'q')
        {
            initarray(st);
            initarray(rc);
            
            printf("\n");
            printf("[r] \t FILE READ\n");
            printf("[d] \t FILE DELETE\n");
            printf("[w] \t FILE WRITE\n");
            printf("[q] \t QUIT\n");
            printf("\n");
            printf("> ");
            scanf("%s", &ans);

            if (ans != 'r' && ans != 'd' && ans != 'w' && ans != 'q')
            {
                printf("OPTION [%s] DOES NOT EXIST (YET)\n", &ans);
            }

            if (ans == 'q')
            {
                return 0;
            }

            if (ans == 'r')
            {
                fp = fopen("record.txt", "r");

                while (fgets(buffer, 144, fp) != NULL)
                {
                    printf("%s\n", buffer);
                }

                fclose(fp);
                ans = 'e';
            }

            if (ans == 'd')
            {
                fp = fopen("record.txt", "w");
            
                for (i = 0; i < SIZE; i++)
                {
                    fprintf(fp, "%s %s %d %f\n", rc[i].first, rc[i].last, rc[i].roll, rc[i].mark);
                }

                fclose(fp);
                ans = 'e';
            }

            if (ans == 'w')
            {
                fillarray(st);
                printarray(st);

                printf("\n");

                while (ans != 'y' && ans != 'n')
                {
                    printf("STORE ARRAY IN FILE (y/n): ");
                    scanf("%s", &ans);
                    printf("\n");
                }

                if (ans == 'y')
                {
                    fp = fopen("record.txt", "w");
            
                    for (i = 0; i < SIZE; i++)
                    {
                        fprintf(fp, "%s %s %d %f\n", st[i].first, st[i].last, st[i].roll, st[i].mark);
                    }

                    fclose(fp);
                    ans = 'e';
                }
            }
        } 
    }
    else
    {
        printf("\n");
        printf("\n");
        printf("\t >>>> NO FILE RECORD DETECTED\n");
        printf("\n");

        fillarray(st);
        printarray(st);

        printf("\n");

        while (ans != 'y' && ans != 'n')
        {
            printf("STORE ARRAY IN FILE (y/n): ");
            scanf("%s", &ans);
            printf("\n");
        }

        if (ans == 'y')
        {
            fp = fopen("record.txt", "w");
            
            for (i = 0; i < SIZE; i++)
            {
                fprintf(fp, "%s %s %d %f\n", st[i].first, st[i].last, st[i].roll, st[i].mark);
            }

            fclose(fp);

        }
        
    }
    return 0;
}

