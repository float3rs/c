# include <stdio.h>
# include <stdlib.h>
# include <float.h>

struct node
{
    float data;
    struct node* prev_ptr;
    struct node* next_ptr;
};

struct node* head_ptr;

void insert(struct node** head_ptr_ptr, float x)
{
    struct node* new_ptr;
    new_ptr = (struct node*) malloc(sizeof(struct node));

    struct node* current_ptr;
    int count = 0;

    if (new_ptr == NULL)
    {
        printf("\n|----------|\n");
        printf(  "| OVERFLOW |\n");
        printf(  "|----------|\n\n");

        return;
    }

    (*new_ptr).data = x;
    (*new_ptr).prev_ptr = NULL;
    (*new_ptr).next_ptr = NULL;

    if (*head_ptr_ptr == NULL)
    {
        printf("\n### FOUND: NO NODES ###\n");
        
        *head_ptr_ptr = new_ptr;

        printf("\n|---------------|\n");
        printf(  "| LIST: CREATED |\n");
        printf(  "|---------------|\n\n");

        printf("INSERTED FLOAT: %f\n", (**head_ptr_ptr).data);

        return;
    }
    
    // <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
    // ORDERED <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
    // <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

    if ((**head_ptr_ptr).next_ptr == NULL)
    {
        printf("\n###         FOUND NODE: JUST 1 (HEAD) ###\n");

        if ((*new_ptr).data < (**head_ptr_ptr).data)
        {
            printf("### POSITION-TO-INSERT: AFTER HEAD    ###\n");

            
            (*new_ptr).prev_ptr = *head_ptr_ptr;
            (**head_ptr_ptr).next_ptr = new_ptr;
        }
        else
        {
            printf("### POSITION-TO-INSERT: BEFORE HEAD   ###\n");

            (*new_ptr).next_ptr = (*head_ptr_ptr);
            (**head_ptr_ptr).prev_ptr = new_ptr;

            (*head_ptr_ptr) = new_ptr;
        }
    }
    else
    {
        printf("\n###        FOUND NODES: MULTIPLE    ###\n");

        current_ptr = *head_ptr_ptr;

        while ((*current_ptr).next_ptr != NULL)
        {
            if ((*new_ptr).data > (*current_ptr).data )
            {
                break;
            }
            
            current_ptr = (*current_ptr).next_ptr;
            count++;
        }

        if ( (*current_ptr).prev_ptr != NULL && (*current_ptr).next_ptr != NULL)
        {
            printf("### POSITION-TO-INSERT: IN BETWEEN  ###\n");

            printf("\nCURRENT: [%f] <- [%f] -> [%f]\n", (*(*current_ptr).prev_ptr).data, (*current_ptr).data, (*(*current_ptr).next_ptr).data);

            (*new_ptr).next_ptr = current_ptr;
            (*new_ptr).prev_ptr = (*current_ptr).prev_ptr;

            (*(*current_ptr).prev_ptr).next_ptr = new_ptr;
            (*current_ptr).prev_ptr = new_ptr;
        }
        else
        {
            if ((*current_ptr).prev_ptr == NULL)
            {
                printf("### POSITION-TO-INSERT: BEFORE HEAD ###\n");
            
                (*new_ptr).next_ptr = current_ptr;
                (*current_ptr).prev_ptr = new_ptr;

                *head_ptr_ptr =new_ptr;
            }

            if ((*current_ptr).next_ptr == NULL)
            {
                printf("### POSITION-TO-INSERT: AFTER TAIL  ###\n");
            
                (*new_ptr).prev_ptr = current_ptr;
                (*current_ptr).next_ptr = new_ptr;
            }
        }
    }

    printf("\n|--------|\n");
    printf(  "| LISTED |\n");
    printf(  "|--------|\n\n");

    printf(" INSERTED FLOAT: %lf\n", (*new_ptr).data);
    printf("TRAVERSED NODES: %d\n", count);

    return;

    // <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
    // UNORDERED <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
    // <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
    
    // if ((**head_ptr_ptr).next_ptr == NULL)
    // {
    //     printf("\n### FOUND: JUST 1 NODE ###\n");
        
    //     (**head_ptr_ptr).next_ptr = new_ptr;
    //     (*new_ptr).prev_ptr = *head_ptr_ptr;
    // }
    // else
    // {
    //     printf("\n### FOUND: MULTIPLE NODES ###\n");
        
    //     current_ptr = *head_ptr_ptr;
    //     count = 0;

    //     while ( (*current_ptr).next_ptr != NULL )
    //     {
    //         current_ptr = (*current_ptr).next_ptr;
    //         count++;
    //     }

    //     (*current_ptr).next_ptr = new_ptr;
    //     (*new_ptr).prev_ptr = current_ptr;
    // }

    // printf("\n|--------|\n");
    // printf(  "| LISTED |\n");
    // printf(  "|--------|\n\n");

    // printf("INSERTED DOUBLE: %lf\n", (*new_ptr).data);
    // printf("TRAVERSED NODES: %d\n", count+1);
    
    // return
    
    // <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
    // <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
    // <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
}

float delete(struct node** head_ptr_ptr, int position)
{
    struct node* current_ptr;
    
    int count;
    float x;
    
    if ((*head_ptr_ptr) == NULL)
    {
        printf("\n### FOUND: NO NODES ###\n");

        printf("\n|-----------|\n");
        printf(  "| UNDERFLOW |\n");
        printf(  "|-----------|\n\n");

        return FLT_MIN;
    }

    if ((**head_ptr_ptr).next_ptr == NULL)
    {
        printf("\n### FOUND: JUST 1 NODE ###\n");

        x = (**head_ptr_ptr).data;
        printf("\nRETURNED DOUBLE: [ %f ]\n", x);

        *head_ptr_ptr = NULL;

        printf("\n|-----------------|\n");
        printf(  "| LIST: DESTROYED |\n");
        printf(  "|-----------------|\n\n");
    }
    else
    {
        printf("\n### FOUND: MULTIPLE NODES ###\n");

        if (position == 4)
        {
            printf("### NODE-TO-DELETE: FIRST ###\n");
            
            x = (**head_ptr_ptr).data;
            printf("\nRETURNED FLOAT: [ %f ]\n", x);

            *head_ptr_ptr = (**head_ptr_ptr).next_ptr;
            (**head_ptr_ptr).prev_ptr = NULL;

            printf("\n|----------|\n");
            printf(  "| UNLISTED |\n");
            printf(  "|----------|\n\n");
        }

        if (position == 5)
        {
            printf("### NODE-TO-DELETE: LAST  ###\n");
            
            current_ptr = *head_ptr_ptr;
            count = 0;

            while ((*current_ptr).next_ptr != NULL)
            {
                current_ptr = (*current_ptr).next_ptr;
                count++;
            }

            x = (*current_ptr).data;
            
            printf("\nTRAVERSED: %d NODES\n", count+1);
            printf("RETURNED FLOAT: [ %f ]\n", x);
            
            (*(*current_ptr).prev_ptr).next_ptr = NULL;

            printf("\n|----------|\n");
            printf(  "| UNLISTED |\n");
            printf(  "|----------|\n\n");
        }
    }

    return x;    
}

void display(struct node* head_ptr)
{
    struct node* current_ptr = head_ptr;
    
    if (head_ptr == NULL) 
    {
        printf("\n|-------|\n");
        printf(  "| EMPTY |\n");
        printf(  "|-------|\n\n");
        
        return;
    }
    
    if ((*head_ptr).next_ptr == NULL)
    {
        printf("\n[ %16f ]\n", (*head_ptr).data);
        return;
    }
    else
    {
        while ((*current_ptr).next_ptr != NULL)
        {
            printf("\n[ %16f ]", (*current_ptr).data);
            current_ptr = (*current_ptr).next_ptr;
        }

        printf("\n[ %16f ]", (*current_ptr).data);

        printf("\n");
        return;
    }
}

int main()
{
    int choise = -1;
    int position = 0;
    float item;
    
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
                        printf("\nFLOAT: ");
                        scanf(" %f", &item);

                        insert(&head_ptr, item);
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

                        delete(&head_ptr, position);
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

