# include <stdio.h>
# include <stdlib.h>

struct node
{
    char data;
    struct node* next_ptr;
};

void list(struct node** head_ptr_ptr, char x)
{
    struct node* new_ptr;
    new_ptr = (struct node*) malloc(sizeof(struct node));
    
    struct node* tail_ptr = *head_ptr_ptr;
    int count = 0;

    if (new_ptr == NULL)
    {
        printf("\n|----------|\n");
        printf(  "| OVERFLOW |\n");
        printf(  "|----------|\n\n");

        return;
    } 
    else
    {
        (*new_ptr).data = x;
        (*new_ptr).next_ptr = NULL;
    }

    if (*head_ptr_ptr == NULL)
    {
        *head_ptr_ptr = new_ptr;

        printf("\n|---------------|\n");
        printf(  "| LIST: CREATED |\n");
        printf(  "|---------------|\n\n");

        printf("INSERTED: %c\n", (**head_ptr_ptr).data);

        return;
    }
    else
    {
        
        if ((**head_ptr_ptr).next_ptr == NULL)
        {
            (**head_ptr_ptr).next_ptr = new_ptr;
        }
        else
        {
            while ((*tail_ptr).next_ptr != NULL)
            {
                tail_ptr = (*tail_ptr).next_ptr;
                count++;
            }
        }
        
        (*tail_ptr).next_ptr = new_ptr;

        printf("\n|--------|\n");
        printf(  "| LISTED |\n");
        printf(  "|--------|\n\n");

        printf("INSERTED CHAR: %c\n", (*new_ptr).data);
        printf("TRAVERSED: %d NODES\n", count+1);

        return;
    }
}

char unlist(struct node** head_ptr_ptr, int pos)
{
    int count = 0;
    char x;

     struct node* tail_ptr = *head_ptr_ptr;
     struct node* pretail_ptr = *head_ptr_ptr;

    if (*head_ptr_ptr == NULL)
    {
        printf("\n|-----------|\n");
        printf(  "| UNDERFLOW |\n");
        printf(  "|-----------|\n\n");

        return '0';
    }

    if ((**head_ptr_ptr).next_ptr == NULL)
    {
        x = (**head_ptr_ptr).data;

        printf("\nRETURNED CHAR: [ %c ]\n", x);

        *head_ptr_ptr = NULL;
        
        printf("\n|-----------------|\n");
        printf(  "| LIST: DESTROYED |\n");
        printf(  "|-----------------|\n\n");

        return x;
    }
    else
    {
        if (pos == 4)
        {
            x = (**head_ptr_ptr).data;

            printf("\nRETURNED CHAR: [ %c ]\n", x);

            *head_ptr_ptr = (**head_ptr_ptr).next_ptr;

            printf("\n|----------|\n");
            printf(  "| UNLISTED |\n");
            printf(  "|----------|\n\n");
        }

        if (pos == 5)
        {
            while ((*tail_ptr).next_ptr != NULL)
            {
                tail_ptr = (*tail_ptr).next_ptr;
                count++;
            }

            x = (*tail_ptr).data;

            printf("\nTRAVERSED: %d NODES\n", count+1);
            printf("RETURNED CHAR: [ %c ]\n", x);

            for (int i = 0; i < count-1; i++)
            {
                pretail_ptr = (*pretail_ptr).next_ptr;
            }

            (*pretail_ptr).next_ptr = NULL;

            printf("\n|----------|\n");
            printf(  "| UNLISTED |\n");
            printf(  "|----------|\n\n");
        }

        return x;
    }
}

void display(struct node* head_ptr)
{
    struct node* tail_ptr = head_ptr;
    
    if (head_ptr == NULL) 
    {
        printf("\n|-------|\n");
        printf(  "| EMPTY |\n");
        printf(  "|-------|\n\n");
        
        return;
    }
    
    if ((*head_ptr).next_ptr == NULL)
    {
        printf("\n[ %c ]\n", (*head_ptr).data);
        return;
    }
    else
    {
        while ((*tail_ptr).next_ptr != NULL)
        {
            printf("\n[ %c ]", (*tail_ptr).data);
            tail_ptr = (*tail_ptr).next_ptr;
        }

        printf("\n[ %c ]", (*tail_ptr).data);

        printf("\n");
        return;
    }
}

int main()
{
    int choise = -1;
    int position = 0;
    char item;
    
    struct node* head_ptr = NULL;
    struct node* tail_ptr = NULL;

    while (choise != 0)
    {
        printf("\n");
        printf("[1] -> INSERT\n");
        printf("[2] -> REMOVE\n");
        printf("[3] -> DISPLAY\n");
        printf("[0] -> QUIT\n\n");

        printf("? "); 
        scanf("%d", &choise);

        switch (choise)
        {
            case 1:
                        printf("\nCHAR: ");
                        scanf(" %c", &item);

                        list(&head_ptr, item);
                        break;

            case 2:
                        while (position != 4 && position != 5)
                        {
                            printf("\n");
                            printf("[4] -> FIRST\n");
                            printf("[5] -> LAST\n\n");

                            printf("? "); 
                            scanf("%d", &position);

                            if (position != 4 && position != 5)
                            {
                                printf("\n|---------|\n");
                                printf(  "| INVALID |\n");
                                printf(  "|---------|\n\n");
                            }
                        }

                        unlist(&head_ptr, position);
                        position = 0;

                        break;

            case 3:
                        display(head_ptr);
                        break;

            case 0:
                        printf("\n");
                        break;

            default:
                        printf("\n|---------|\n");
                        printf(  "| INVALID |\n");
                        printf(  "|---------|\n\n");
        }
    }

    return 0;
}

