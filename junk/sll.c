# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define SIZE 21

struct node
{
    char data[SIZE];
    size_t offset;
};

void printall  (char* headdata, size_t headoffset,
                char* taildata, size_t tailoffset,
                char* currentdata, size_t currentoffset,
                char* precurrentdata, size_t precurrentoffset,
                char* newdata, size_t newoffset, int counter)
{
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("      NULL:                       | %zu \n", (size_t) NULL);
    printf("      HEAD: %21s | %zu\n", headdata, headoffset);
    printf("      TAIL: %21s | %zu\n", taildata, tailoffset);
    printf("   CURRENT: %21s | %zu\n", currentdata, currentoffset);
    printf("PRECURRENT: %21s | %zu\n", precurrentdata, precurrentoffset);
    printf("       NEW: %21s | %zu\n", newdata, newoffset);
    printf("   COUNTER:                       | %d\n", counter);
    printf("  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

    return;
}

// printf("\nTEXT\n");
// printall((**head_ptr_ptr).data, (**head_ptr_ptr).offset,
//         (**tail_ptr_ptr).data, (**tail_ptr_ptr).offset,
//         (*current_ptr).data, (*current_ptr).offset,
//         (*precurrent_ptr).data, (*current_ptr).offset,
//         (*new_ptr).data, (*new_ptr).offset, 0);

void insert(struct node** head_ptr_ptr, struct node** tail_ptr_ptr, char x[SIZE])
{
    int count = 0;
    size_t buffer;
    struct node* prelast_ptr;

    struct node* precurrent_ptr = *head_ptr_ptr;
    struct node* current_ptr = (struct node*) ( ((size_t)(struct node*) NULL) + ((size_t) (*precurrent_ptr).offset) );

    struct node* new_ptr;
    new_ptr = (struct node*) malloc(sizeof(struct node));

    if (new_ptr == NULL)
    {
        printf("\n|----------|\n");
        printf(  "| OVERFLOW |\n");
        printf(  "|----------|\n\n");

        return;
    }

    strcpy((*new_ptr).data, x);

    if ((size_t) (**head_ptr_ptr).offset == ((size_t) *tail_ptr_ptr) - (size_t)(struct node*) NULL )
    {

        (*new_ptr).offset = (size_t) *tail_ptr_ptr - (size_t) *head_ptr_ptr;
        (**head_ptr_ptr).offset = (size_t) new_ptr - (size_t)(struct node*) NULL;
        (**tail_ptr_ptr).offset = (size_t)(struct node*) NULL - (size_t) new_ptr;

        printf("\n|---------------|\n");
        printf(  "| LIST: CREATED |\n");
        printf(  "|---------------|\n\n");
    }
    else
    {
        
        // while (current_ptr != *tail_ptr_ptr)
        // {
        //     buffer = (*current_ptr).offset;
        //     current_ptr = (struct node*) ((size_t) precurrent_ptr + (size_t) (*current_ptr).offset);
        //     precurrent_ptr = (struct node*) ((size_t) current_ptr - buffer);
            
        //     count++;
        // }

        // (*new_ptr).offset = (size_t) *tail_ptr_ptr - (size_t) current_ptr;
        // (**tail_ptr_ptr).offset = (size_t) new_ptr - (size_t) NULL;
        // (*current_ptr).offset = (size_t) precurrent_ptr - (size_t) new_ptr;

        (*new_ptr).offset = (size_t) (*tail_ptr_ptr) - ((size_t)(struct node*) NULL + (**tail_ptr_ptr).offset);
    
        size_t tailoffset =  (**tail_ptr_ptr).offset;

        prelast_ptr = (struct node*) ( (size_t)(struct node*) NULL - tailoffset);

        (*prelast_ptr).offset = (size_t) new_ptr - ( (size_t) *tail_ptr_ptr - (*prelast).offset );

        printf("5\n");
        (**tail_ptr_ptr).offset = (size_t)(struct node*) NULL - (*new_ptr).offset;


        // (*((struct node*)((size_t)(struct node*) NULL + (**tail_ptr_ptr).offset))).offset = (*new_ptr).offset - ( ((size_t) *tail_ptr_ptr) - (*((struct node*)((size_t)(struct node*) NULL + (**tail_ptr_ptr).offset))).offset );
        // (**tail_ptr_ptr).offset = (size_t)(struct node*) NULL - (*new_ptr).offset;


        printf("\n|----------|\n");
        printf(  "| INSERTED |\n");
        printf(  "|----------|\n\n");
    }

    printf("INSERTED STRING: %s\n", (*new_ptr).data);
    printf("TRAVERSED NODES: %d\n", count);
    
    return;
}

void display(struct node* head_ptr, struct node* tail_ptr)
{
    int count = 0;
    size_t buffer;
    struct node* buffer_ptr;
    struct node* precurrent_ptr = head_ptr;
    struct node* current_ptr = (struct node*) ((size_t) NULL + (size_t) (*head_ptr).offset);

    printf("\nBEFORE\n");
    printall((*head_ptr).data, (*head_ptr).offset,
        (*tail_ptr).data, (*tail_ptr).offset,
        (*current_ptr).data, (*current_ptr).offset,
        (*precurrent_ptr).data, (*current_ptr).offset,
        " ", 0, 0);


    while (current_ptr != tail_ptr)
    {
        printf("[ %s ]\n", (*current_ptr).data);

        buffer = (*current_ptr).offset;
        current_ptr = (struct node*) ((size_t) precurrent_ptr + (size_t) (*current_ptr).offset);
        precurrent_ptr = (struct node*) ((size_t) current_ptr - buffer);

        count++;
    }

    printf("\nAFTER1\n");
    printall((*head_ptr).data, (*head_ptr).offset,
        (*tail_ptr).data, (*tail_ptr).offset,
        (*current_ptr).data, (*current_ptr).offset,
        (*precurrent_ptr).data, (*current_ptr).offset,
        " ", 0, 0);

    // printf("\nTEXT\n");
    // printall((*head_ptr).data, (*head_ptr).offset,
    //     (*tail_ptr).data, (*tail_ptr).offset,
    //     (*current_ptr).data, (*current_ptr).offset,
    //     (*precurrent_ptr).data, (*current_ptr).offset,
    //     " ", 0, 0);

    return;
}





int main()
{   
    int choise = -1;
    int position;
    char text[SIZE];
    
    struct node* head_ptr;
    head_ptr = (struct node*) malloc(sizeof(struct node));
    struct node* tail_ptr;
    tail_ptr = (struct node*) malloc(sizeof(struct node));

    if ((head_ptr == NULL) || (tail_ptr == NULL))
    {
        printf("\n|----------|\n");
        printf(  "| OVERFLOW |\n");
        printf(  "|----------|\n\n");

        return 1;
    }

    strcpy((*head_ptr).data, "__HEAD__");
    (*head_ptr).offset = (size_t) tail_ptr - ((size_t) (struct node*) NULL);
    strcpy((*tail_ptr).data, "__TAIL__");
    (*tail_ptr).offset = (((size_t) (struct node*) NULL) - (size_t) head_ptr);


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
                        
                        printf(  "ENTERED: %s\n", text);

                        insert(&head_ptr, &tail_ptr, text);
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

                        //delete(&head_ptr, position);
                        position = 0;

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