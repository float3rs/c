# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define SIZE 21

struct node
{
    char data[SIZE];
    size_t offset;
};

void insert(struct node** head_ptr_ptr, struct node** tail_ptr_ptr, char* text)
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
            printf("[%d] %s \n", counter, (*curr_ptr).data);

            swap_ptr = curr_ptr;
            curr_ptr = (struct node*) ((size_t) prev_ptr + (*curr_ptr).offset);
            prev_ptr = swap_ptr;
            
            counter++;
        }
        
        return;
    }
}

char* delete(struct node** head_ptr_ptr, struct node** tail_ptr_ptr)
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
        printf(  "next -> %s\n\n", (*next_ptr).data);

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

                        insert(&head_ptr, &tail_ptr, text);
                        break;

            case 2:
                        delete(&head_ptr, &tail_ptr);
                        break;

            case 3:
                        display(head_ptr, tail_ptr);
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