# include <stdio.h>
# include <stdlib.h>
# include <limits.h>

struct node
{
    int data;
    struct node* next_ptr;
};

void list(struct node** head_ptr_ptr, int x)
{
    struct node* new_ptr;
    new_ptr = (struct node*) malloc(sizeof(struct node));
    
    struct node* temp_ptr = *head_ptr_ptr;
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

        printf("INSERTED: %d\n", (**head_ptr_ptr).data);

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
            while ((*temp_ptr).next_ptr != NULL)
            {
                temp_ptr = (*temp_ptr).next_ptr;
                count++;
            }
        }
        
        (*temp_ptr).next_ptr = new_ptr;

        printf("\n|--------|\n");
        printf(  "| LISTED |\n");
        printf(  "|--------|\n\n");

        printf("INSERTED INT: %d\n", (*new_ptr).data);
        printf("TRAVERSED: %d NODES\n", count+1);

        return;


        // count = 0;
        
        // *tail_ptr_ptr = *head_ptr_ptr;
        
        // while ((**tail_ptr_ptr).next_ptr != NULL)
        // {
        //     *tail_ptr_ptr = (**tail_ptr_ptr).next_ptr;
        //     count++;
        // }

        // printf("\n# TRAVERSED: %d NODES\n", count);

        // *tail_ptr_ptr = new_ptr;

        // printf("\n|--------|\n");
        // printf(  "| LISTED |\n");
        // printf(  "|--------|\n\n");

        // return;
    }
}

int unlist(struct node** head_ptr_ptr)
{
    int x;

    if (*head_ptr_ptr == NULL)
    {
        printf("\n|-----------|\n");
        printf(  "| UNDERFLOW |\n");
        printf(  "|-----------|\n\n");

        return INT_MIN;
    }

    if ((**head_ptr_ptr).next_ptr == NULL)
    {
        x = (**head_ptr_ptr).data;

        printf("\nRETURNED: [ %d ]\n", x);

        *head_ptr_ptr = NULL;
        
        printf("\n|-----------------|\n");
        printf(  "| LIST: DESTROYED |\n");
        printf(  "|-----------------|\n\n");

        return x;
    }
    else
    {
        x = (**head_ptr_ptr).data;

        printf("\nRETURNED: [ %d ]\n", x);

        *head_ptr_ptr = (**head_ptr_ptr).next_ptr;

        printf("\n|----------|\n");
        printf(  "| UNLISTED |\n");
        printf(  "|----------|\n\n");

        return x;
    }
}

void display(struct node* head_ptr)
{
    struct node* temp_ptr = head_ptr;
    
    if (head_ptr == NULL) 
    {
        printf("\n|-------|\n");
        printf(  "| EMPTY |\n");
        printf(  "|-------|\n\n");
        
        return;
    }

    
    
    if ((*head_ptr).next_ptr == NULL)
    {
        printf("\n[ %d ]\n", (*head_ptr).data);
        return;
    }
    else
    {
        while ((*temp_ptr).next_ptr != NULL)
        {
            printf("\n[ %d ]", (*temp_ptr).data);
            temp_ptr = (*temp_ptr).next_ptr;
        }

        printf("\n[ %d ]", (*temp_ptr).data);

        printf("\n");
        return;
    }
    

    // *tail_ptr_ptr = *head_ptr_ptr;

    // printf("\n");

    // while ((**tail_ptr_ptr).next_ptr != NULL)
    // {
    //     printf("[ %d ]\n", (**tail_ptr_ptr).data);
    // }

    // return;
}



int main()
{
    int choise = -1;
    int item;
    
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
                        printf("\nINT: ");
                        scanf(" %d", &item);

                        list(&head_ptr, item);
                        break;

            case 2:
                        unlist(&head_ptr);
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

