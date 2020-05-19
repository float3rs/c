# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define SIZE 21

struct node
{
    char data[SIZE];
    size_t offset;
};


void insert_last(struct node** head_ptr_ptr, struct node** tail_ptr_ptr, char* text)
{
    int counter = 0;

    struct node* curr_ptr;
    struct node* prev_ptr;
    struct node* swap_ptr;
    
    struct node* new_ptr;
    new_ptr = (struct node*) malloc(sizeof(struct node));

    if (new_ptr == NULL)
    {
        printf("\n|----------|\n");
        printf(  "| OVERFLOW |\n");
        printf(  "|----------|\n\n");

        return;
    }

    strcpy((*new_ptr).data, text);

    if ((**head_ptr_ptr).offset == (size_t)(struct node*) NULL)
    {
        (*new_ptr).offset = (size_t) *tail_ptr_ptr - (size_t) *head_ptr_ptr;
        (**head_ptr_ptr).offset = (size_t) new_ptr - (size_t)(struct node*) NULL;
        (**tail_ptr_ptr).offset = (size_t)(struct node*) NULL - (size_t) new_ptr;

        printf("\n|---------------|\n");
        printf(  "| LIST: CREATED |\n");
        printf(  "|---------------|\n\n");

        printf("INSERTED STRING: %s\n", (*new_ptr).data);

        return;
    }
   
    prev_ptr = *head_ptr_ptr;
    curr_ptr = (struct node*)((size_t)(struct node*) NULL + (**head_ptr_ptr).offset);

    counter = 0;

    while (curr_ptr != *tail_ptr_ptr)
    {   
        swap_ptr = curr_ptr;
        curr_ptr = (struct node*)((size_t) prev_ptr + (*curr_ptr).offset);
        prev_ptr = swap_ptr;

        counter++;
    }

    printf("counted %d nodes\n", counter);

    if (counter == 1)
    {
        prev_ptr = *head_ptr_ptr;
        curr_ptr = (struct node*)((size_t)(struct node*) NULL + (**head_ptr_ptr).offset);

        (*new_ptr).offset = (size_t) *tail_ptr_ptr - (size_t) curr_ptr;
        (*curr_ptr).offset = (size_t) new_ptr - (size_t) prev_ptr;
        (**tail_ptr_ptr).offset = (size_t)(struct node*) NULL - (size_t) new_ptr;

        printf("\n|-------------|\n");
        printf(  "| 1+ INSERTED |\n");
        printf(  "|-------------|\n\n");
    }
    else
    {
        // printf("\ncurr -> %s\n", (*curr_ptr).data);
        // printf("\nprev -> %s\n", (*prev_ptr).data);

        prev_ptr = *head_ptr_ptr;
        curr_ptr = (struct node*)((size_t)(struct node*) NULL + (**head_ptr_ptr).offset);

        for (int i = 0; i < counter - 1; i++)
        {
            swap_ptr = curr_ptr;
            curr_ptr = (struct node*)((size_t) prev_ptr + (*curr_ptr).offset);
            prev_ptr = swap_ptr;
        }

        // printf("\ncurr -> %s\n", (*curr_ptr).data);
        // printf("\nprev -> %s\n", (*prev_ptr).data);

        (*new_ptr).offset = (size_t) *tail_ptr_ptr - (size_t) curr_ptr;
        (*curr_ptr).offset = (size_t) new_ptr - (size_t) prev_ptr;
        (**tail_ptr_ptr).offset = (size_t)(struct node*) NULL - (size_t) new_ptr;

        printf("\n|----------|\n");
        printf(  "| INSERTED |\n");
        printf(  "|----------|\n\n");
    }

    return;   
}

void display(struct node* head_ptr, struct node* tail_ptr)
{
    struct node* prev_ptr;
    struct node* curr_ptr;
    struct node* swap_ptr;
    int counter = 0;

    if ((*head_ptr).offset == (size_t)(struct node*) NULL)
    {
        printf("\n|-------|\n");
        printf(  "| EMPTY |\n");
        printf(  "|-------|\n\n");
        
        return;
    }
    else
    {
        prev_ptr = head_ptr;
        curr_ptr = (struct node*) ((*head_ptr).offset - (size_t)(struct node*) NULL);

        printf("\n");
        
        while (curr_ptr != tail_ptr)
        {
            printf("{%d} %s \n", counter, (*curr_ptr).data);

            swap_ptr = curr_ptr;
            curr_ptr = (struct node*) ((size_t) prev_ptr + (*curr_ptr).offset);
            prev_ptr = swap_ptr;
            
            counter++;
        }
        
        return;
    }
}

char* delete_first(struct node** head_ptr_ptr, struct node** tail_ptr_ptr)
{
    
    struct node* prev_ptr;
    struct node* curr_ptr;
    struct node* next_ptr;
    struct node* swap_ptr;
    int counter = 0;
    char text[21];

    struct node* preprev_ptr;
    struct node* nexnext_ptr;

    if ((**head_ptr_ptr).offset == (size_t)(struct node*) NULL)
    {
        printf("\n|-----------|\n");
        printf(  "| UNDERFLOW |\n");
        printf(  "|-----------|\n\n");

        return " ";
    }

    prev_ptr = *head_ptr_ptr;
    curr_ptr = (struct node*)((size_t)(struct node*) NULL + (**head_ptr_ptr).offset);

    counter = 0;

    while (curr_ptr != *tail_ptr_ptr)
    {   
        swap_ptr = curr_ptr;
        curr_ptr = (struct node*)((size_t) prev_ptr + (*curr_ptr).offset);
        prev_ptr = swap_ptr;

        counter++;
    }

    printf("\nTOTAL NODES: %d\n", counter);

    if (counter == 1)
    {
        strcpy(text, (*prev_ptr).data);
        printf("\nRETURNED STRING: %s\n", text);
        
        (**head_ptr_ptr).offset = (size_t)(struct node*) NULL;
        (**tail_ptr_ptr).offset = (size_t)(struct node*) NULL;

        printf("\n|-----------------|\n");
        printf(  "| LIST: DESTROYED |\n");
        printf(  "|-----------------|\n\n");
    }
    else
    {
        prev_ptr = *head_ptr_ptr;
        curr_ptr = (struct node*)((size_t)(struct node*) NULL + (**head_ptr_ptr).offset);
        next_ptr = (struct node*)((size_t) *head_ptr_ptr + (*curr_ptr).offset);

        swap_ptr = curr_ptr;
        curr_ptr = (struct node*)((size_t) prev_ptr + (*curr_ptr).offset);
        next_ptr = (struct node*)((size_t) swap_ptr + (*curr_ptr).offset);
        prev_ptr = swap_ptr;

        printf("\nprev -> %s\n", (*prev_ptr).data);
        printf(  "curr -> %s\n", (*curr_ptr).data);
        printf(  "next -> %s\n", (*next_ptr).data);

        strcpy(text, (*prev_ptr).data);
        printf("\nRETURNED STRING: %s\n", text);

        (*curr_ptr).offset = ((size_t) next_ptr) - ((size_t) *head_ptr_ptr);
        (**head_ptr_ptr).offset = (size_t) curr_ptr - (size_t)(struct node*) NULL;

        printf("\n|---------|\n");
        printf(  "| DELETED |\n");
        printf(  "|---------|\n\n");
    }

    return text;
}

char* delete_last(struct node** head_ptr_ptr, struct node** tail_ptr_ptr)
{
    
    struct node* prev_ptr;
    struct node* curr_ptr;
    struct node* next_ptr;
    struct node* swap_ptr;
    int counter = 0;
    char text[21];

    struct node* preprev_ptr;
    struct node* nexnext_ptr;

    if ((**head_ptr_ptr).offset == (size_t)(struct node*) NULL)
    {
        printf("\n|-----------|\n");
        printf(  "| UNDERFLOW |\n");
        printf(  "|-----------|\n\n");

        return " ";
    }

    prev_ptr = *head_ptr_ptr;
    curr_ptr = (struct node*)((size_t)(struct node*) NULL + (**head_ptr_ptr).offset);

    counter = 0;

    while (curr_ptr != *tail_ptr_ptr)
    {   
        swap_ptr = curr_ptr;
        curr_ptr = (struct node*)((size_t) prev_ptr + (*curr_ptr).offset);
        prev_ptr = swap_ptr;

        counter++;
    }

    printf("\nTOTAL NODES: %d\n", counter);

    if (counter == 1)
    {
        strcpy(text, (*prev_ptr).data);
        printf("\nRETURNED STRING: %s\n", text);
        
        (**head_ptr_ptr).offset = (size_t)(struct node*) NULL;
        (**tail_ptr_ptr).offset = (size_t)(struct node*) NULL;

        printf("\n|-----------------|\n");
        printf(  "| LIST: DESTROYED |\n");
        printf(  "|-----------------|\n\n");
    }
    else
    {
        prev_ptr = *head_ptr_ptr;
        curr_ptr = (struct node*)((size_t)(struct node*) NULL + (**head_ptr_ptr).offset);
        next_ptr = (struct node*)((size_t) *head_ptr_ptr + (*curr_ptr).offset);

        for (int i = 0; i <= counter - 3; i++)
        {
            swap_ptr = curr_ptr;
            curr_ptr = (struct node*)((size_t) prev_ptr + (*curr_ptr).offset);
            next_ptr = (struct node*)((size_t) swap_ptr + (*curr_ptr).offset);
            prev_ptr = swap_ptr;
        }

        printf("\nprev -> %s\n", (*prev_ptr).data);
        printf(  "curr -> %s\n", (*curr_ptr).data);
        printf(  "next -> %s\n", (*next_ptr).data);

        strcpy(text, (*next_ptr).data);
        printf("\nRETURNED STRING: %s\n", text);

        (*curr_ptr).offset = (size_t) *tail_ptr_ptr - (size_t) prev_ptr;
        (**tail_ptr_ptr).offset = (size_t)(struct node*) NULL - (size_t) prev_ptr;

        printf("\n|---------|\n");
        printf(  "| DELETED |\n");
        printf(  "|---------|\n\n");
    }

    return text;
}

char* delete_any(struct node** head_ptr_ptr, struct node** tail_ptr_ptr, int position)
{    
    struct node* prev_ptr;
    struct node* curr_ptr;
    struct node* next_ptr;
    struct node* swap_ptr;
    
    int counter = 0;
    char text[21];

    struct node* preprev_ptr;
    struct node* nexnext_ptr;
    struct node* preswap_ptr;
    struct node* curswap_ptr;
    struct node* nexswap_ptr;


    if ((**head_ptr_ptr).offset == (size_t)(struct node*) NULL)
    {
        printf("\n|-----------|\n");
        printf(  "| UNDERFLOW |\n");
        printf(  "|-----------|\n\n");

        return " ";
    }

    prev_ptr = *head_ptr_ptr;
    curr_ptr = (struct node*)((size_t)(struct node*) NULL + (**head_ptr_ptr).offset);

    counter = 0;

    while (curr_ptr != *tail_ptr_ptr)
    {   
        swap_ptr = curr_ptr;
        curr_ptr = (struct node*)((size_t) prev_ptr + (*curr_ptr).offset);
        prev_ptr = swap_ptr;

        counter++;
    }

    printf("\nTOTAL NODES: %d\n", counter);

    if ((position < 0) || (position > counter-1))
    {
        printf("\n|---------|\n");
        printf(  "| INVALID |\n");
        printf(  "|---------|\n\n");

        return " ";
    }

    if ((counter == 1) && (position == 0))
    {
        strcpy(text, (*prev_ptr).data);
        printf("\nRETURNED STRING: %s\n", text);
        
        (**head_ptr_ptr).offset = (size_t)(struct node*) NULL;
        (**tail_ptr_ptr).offset = (size_t)(struct node*) NULL;

        printf("\n|-----------------|\n");
        printf(  "| LIST: DESTROYED |\n");
        printf(  "|-----------------|\n\n");
    }
    else
    {
        if (counter < 4)
        {
            if (counter == 2)
            {
                if (position == 0)
                {
                    prev_ptr = *head_ptr_ptr;
                    curr_ptr = (struct node*)((size_t)(struct node*) NULL + (**head_ptr_ptr).offset);
                    next_ptr = (struct node*)((size_t) *head_ptr_ptr + (*curr_ptr).offset);

                    swap_ptr = curr_ptr;
                    curr_ptr = (struct node*)((size_t) prev_ptr + (*curr_ptr).offset);
                    next_ptr = (struct node*)((size_t) swap_ptr + (*curr_ptr).offset);
                    prev_ptr = swap_ptr;

                    printf("\nprev -> %s\n", (*prev_ptr).data);
                    printf(  "curr -> %s\n", (*curr_ptr).data);
                    printf(  "next -> %s\n", (*next_ptr).data);

                    strcpy(text, (*prev_ptr).data);
                    printf("\nRETURNED STRING: %s\n", text);

                    (*curr_ptr).offset = ((size_t) next_ptr) - ((size_t) *head_ptr_ptr);
                    (**head_ptr_ptr).offset = (size_t) curr_ptr - (size_t)(struct node*) NULL;
                }

                if (position == 1)
                {
                    prev_ptr = *head_ptr_ptr;
                    curr_ptr = (struct node*)((size_t)(struct node*) NULL + (**head_ptr_ptr).offset);
                    next_ptr = (struct node*)((size_t) *head_ptr_ptr + (*curr_ptr).offset);

                    for (int i = 0; i <= counter - 3; i++)
                    {
                        swap_ptr = curr_ptr;
                        curr_ptr = (struct node*)((size_t) prev_ptr + (*curr_ptr).offset);
                        next_ptr = (struct node*)((size_t) swap_ptr + (*curr_ptr).offset);
                        prev_ptr = swap_ptr;
                    }

                    printf("\nprev -> %s\n", (*prev_ptr).data);
                    printf(  "curr -> %s\n", (*curr_ptr).data);
                    printf(  "next -> %s\n", (*next_ptr).data);

                    strcpy(text, (*next_ptr).data);
                    printf("\nRETURNED STRING: %s\n", text);

                    (*curr_ptr).offset = (size_t) *tail_ptr_ptr - (size_t) prev_ptr;
                    (**tail_ptr_ptr).offset = (size_t)(struct node*) NULL - (size_t) prev_ptr;
                }
            }

            if (counter == 3)
            {
                if (position == 0)
                {
                    prev_ptr = *head_ptr_ptr;
                    curr_ptr = (struct node*)((size_t)(struct node*) NULL + (**head_ptr_ptr).offset);
                    next_ptr = (struct node*)((size_t) *head_ptr_ptr + (*curr_ptr).offset);

                    swap_ptr = curr_ptr;
                    curr_ptr = (struct node*)((size_t) prev_ptr + (*curr_ptr).offset);
                    next_ptr = (struct node*)((size_t) swap_ptr + (*curr_ptr).offset);
                    prev_ptr = swap_ptr;

                    printf("\nprev -> %s\n", (*prev_ptr).data);
                    printf(  "curr -> %s\n", (*curr_ptr).data);
                    printf(  "next -> %s\n", (*next_ptr).data);

                    strcpy(text, (*prev_ptr).data);
                    printf("\nRETURNED STRING: %s\n", text);

                    (*curr_ptr).offset = ((size_t) next_ptr) - ((size_t) *head_ptr_ptr);
                    (**head_ptr_ptr).offset = (size_t) curr_ptr - (size_t)(struct node*) NULL;
                }

                if (position == 1)
                {
                    prev_ptr = (struct node*)((size_t)(struct node*) NULL + (**head_ptr_ptr).offset);
                    curr_ptr = (struct node*)((size_t) *head_ptr_ptr + (*prev_ptr).offset);
                    next_ptr = (struct node*)((size_t) prev_ptr + (*curr_ptr).offset);
                    
                    printf("\nprev -> %s\n", (*prev_ptr).data);
                    printf(  "curr -> %s\n", (*curr_ptr).data);
                    printf(  "next -> %s\n", (*next_ptr).data);

                    strcpy(text, (*curr_ptr).data);
                    printf("\nRETURNED STRING: %s\n", text);

                    (*prev_ptr).offset = (size_t) next_ptr      - (size_t) *head_ptr_ptr;
                    (*next_ptr).offset = (size_t) *tail_ptr_ptr - (size_t) prev_ptr;
                }

                if (position == 2)
                {
                    prev_ptr = *head_ptr_ptr;
                    curr_ptr = (struct node*)((size_t)(struct node*) NULL + (**head_ptr_ptr).offset);
                    next_ptr = (struct node*)((size_t) *head_ptr_ptr + (*curr_ptr).offset);

                    for (int i = 0; i <= counter - 3; i++)
                    {
                        swap_ptr = curr_ptr;
                        curr_ptr = (struct node*)((size_t) prev_ptr + (*curr_ptr).offset);
                        next_ptr = (struct node*)((size_t) swap_ptr + (*curr_ptr).offset);
                        prev_ptr = swap_ptr;
                    }

                    printf("\nprev -> %s\n", (*prev_ptr).data);
                    printf(  "curr -> %s\n", (*curr_ptr).data);
                    printf(  "next -> %s\n", (*next_ptr).data);

                    strcpy(text, (*next_ptr).data);
                    printf("\nRETURNED STRING: %s\n", text);

                    (*curr_ptr).offset = (size_t) *tail_ptr_ptr - (size_t) prev_ptr;
                    (**tail_ptr_ptr).offset = (size_t)(struct node*) NULL - (size_t) prev_ptr;
                }
            }
        }
        else
        {
            preprev_ptr = *head_ptr_ptr;
            prev_ptr = (struct node*)((size_t)(struct node*) NULL + (*preprev_ptr).offset);
            curr_ptr = (struct node*)((size_t) preprev_ptr + (*prev_ptr).offset);
            next_ptr = (struct node*)((size_t) prev_ptr + (*curr_ptr).offset);
            nexnext_ptr = (struct node*)((size_t) curr_ptr + (*next_ptr).offset);

            for (int i = 0; i <= position-2; i++)
            {
                if (nexnext_ptr == *tail_ptr_ptr) break;
                
                preswap_ptr = prev_ptr;
                curswap_ptr = curr_ptr;
                nexswap_ptr = next_ptr;
                prev_ptr    = (struct node*)((size_t) preprev_ptr + (*prev_ptr).offset);
                curr_ptr    = (struct node*)((size_t) preswap_ptr + (*prev_ptr).offset);
                next_ptr    = (struct node*)((size_t) curswap_ptr + (*curr_ptr).offset);
                nexnext_ptr = (struct node*)((size_t) nexswap_ptr + (*next_ptr).offset);
                preprev_ptr = preswap_ptr;
            }

            printf("\npreprev -> %s\n", (*preprev_ptr).data);
            printf(  "   prev -> %s\n", (*prev_ptr).data);
            printf(  "   curr -> %s\n", (*curr_ptr).data);
            printf(  "   next -> %s\n", (*next_ptr).data);
            printf(  "nexnext -> %s\n\n", (*nexnext_ptr).data);

            if (position == 0)
            {
                strcpy(text, (*prev_ptr).data);
                printf("\nRETURNED STRING: %s\n", text);

                (*curr_ptr).offset      = ((size_t) next_ptr) - ((size_t) *head_ptr_ptr);
                (**head_ptr_ptr).offset = (size_t) curr_ptr - (size_t)(struct node*) NULL;
            }

            if ((position > 0) && (position < counter - 1))
            {
                strcpy(text, (*curr_ptr).data);
                printf("\nRETURNED STRING: %s\n", text);
                
                (*prev_ptr).offset = ((size_t) next_ptr)    - ((size_t) preprev_ptr);
                (*next_ptr).offset = ((size_t) nexnext_ptr) - ((size_t) prev_ptr);
            }

            if (position == counter - 1)
            {
                strcpy(text, (*next_ptr).data);
                printf("\nRETURNED STRING: %s\n", text);

                (*curr_ptr).offset      = (size_t) *tail_ptr_ptr - (size_t) prev_ptr;
                (**tail_ptr_ptr).offset = (size_t)(struct node*) NULL - (size_t) prev_ptr;
            }

            printf("\n|---------|\n");
            printf(  "| DELETED |\n");
            printf(  "|---------|\n\n");
        }
    }

    return text;
}

void test(struct node** head_ptr_ptr, struct node** tail_ptr_ptr)
{
    insert_last(head_ptr_ptr, tail_ptr_ptr, "test_0");
    insert_last(head_ptr_ptr, tail_ptr_ptr, "test_1");
    insert_last(head_ptr_ptr, tail_ptr_ptr, "test_2");
    insert_last(head_ptr_ptr, tail_ptr_ptr, "test_3");
    insert_last(head_ptr_ptr, tail_ptr_ptr, "test_4");
    insert_last(head_ptr_ptr, tail_ptr_ptr, "test_5");
    insert_last(head_ptr_ptr, tail_ptr_ptr, "test_6");
    insert_last(head_ptr_ptr, tail_ptr_ptr, "test_7");
    insert_last(head_ptr_ptr, tail_ptr_ptr, "test_8");
    insert_last(head_ptr_ptr, tail_ptr_ptr, "test_9");
    return;
}

int main()
{   
    int choise = -1;
    int position;
    
    char text[SIZE];
    
    struct node* head_ptr;
    head_ptr = (struct node*) malloc(sizeof(struct node));
    
    if (head_ptr == NULL)
    {
        printf("\n|----------|\n");
        printf(  "| OVERFLOW |\n");
        printf(  "|----------|\n\n");

        return 1;
    }

    struct node* tail_ptr;
    tail_ptr = (struct node*) malloc(sizeof(struct node));

    if (tail_ptr == NULL)
    {
        printf("\n|----------|\n");
        printf(  "| OVERFLOW |\n");
        printf(  "|----------|\n\n");

        return 1;
    }

    strcpy((*head_ptr).data, "__HEAD__");
    (*head_ptr).offset = (size_t)(struct node*) NULL;
    strcpy((*tail_ptr).data, "__TAIL__");
    (*tail_ptr).offset = (size_t)(struct node*) NULL;

    while (choise != 0)
    {
        printf("\n");
        printf("[9] -> TEST\n");
        printf("[1] -> INSERT\n");
        printf("[2] -> REMOVE\n");
        printf("[3] -> DISPLAY\n");
        printf("[0] -> QUIT\n\n");

        printf("? "); 
        scanf("%d", &choise);

        switch (choise)
        {
            case 1:
                        printf("\n STRING: ");
                        scanf(" %s", text);
                        
                        printf(  "ENTERED: %s\n\n", text);

                        insert_last(&head_ptr, &tail_ptr, text);
                        break;

            case 2:
                        choise = -1;
                        
                        while ((choise < 0) || (choise > 3))
                        {
                            printf("\n");
                            printf("[1] REMOVE -> FIRST\n");
                            printf("[2] REMOVE -> LAST\n");
                            printf("[3] REMOVE -> ANY\n");
                            printf("[0] REMOVE -> QUIT\n\n");

                            printf("OPTION ? "); 
                            scanf("%d", &choise);

                            switch (choise)
                            {
                                case 1:
                                        printf("\n");
                                        delete_first(&head_ptr, &tail_ptr);
                                        break;

                                case 2:
                                        printf("\n");
                                        delete_last(&head_ptr, &tail_ptr);
                                        break;

                                case 3:
                                        printf(" INDEX ? "); 
                                        scanf("%d", &position);
                                        printf("\n");
                                        
                                        delete_any(&head_ptr, &tail_ptr, position);
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
                        
                        choise = 2;
                        break;

            case 3:
                        display(head_ptr, tail_ptr);
                        break;

            case 9:     
                        test(&head_ptr, &tail_ptr);
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