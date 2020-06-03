#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct node
{
    int data;
    struct node*  left_ptr;
    struct node* right_ptr;
};

struct node* create(char direction, int parent_data)
{   
    int x;
    
    struct node* new_ptr;
    new_ptr = (struct node*) malloc(sizeof(struct node));
    
    if (new_ptr == NULL)
    {
        printf("\n|----------|\n");
        printf(  "| OVERFLOW |\n");
        printf(  "|----------|\n\n");

        return (struct node*) NULL;
    }

    printf("\nDATA (%d FOR NULL): ", INT_MIN);
    scanf("%d", &x);
    
    if (x == INT_MIN)
    {
        if (direction == 'l')
        {
            printf("\n                |-------------| \n");
            printf(  "                | %11d |        \n", parent_data);
            printf(  "             -- |-------------| \n");
            printf(  "            /      \n");
            printf(  "|------|   /       \n");
            printf(  "| NONE | <-        \n");
            printf(  "|------|           \n\n\n");
        }

        if (direction == 'r')
        {
            printf("\n|-------------|                \n");
            printf(  "| %11d |                      \n", parent_data);
            printf(  "|-------------| --             \n");
            printf(  "                  \\            \n");
            printf(  "                   \\   |------|\n");
            printf(  "                    -> | NONE | \n");
            printf(  "                       |------| \n\n\n");
        }

        if (direction == 'c')
        {
            printf("\n|------|\n");
            printf(  "| NONE |\n");
            printf(  "|------|\n\n\n");
        }
        
        return (struct node*) NULL;
    }
    
    (*new_ptr).data = x;

    if (direction == 'l')
    {
        printf("\n                     |-------------| \n");
        printf(  "                     | %11d |        \n", parent_data);
        printf(  "                     |-------------| \n");
        printf(  "                    /                \n");
        printf(  "|--------------|   /                 \n");
        printf(  "| LEAF CREATED | <-                  \n");
        printf(  "|--------------|                     \n");
        printf(  "| DATA: %d                           \n", (*new_ptr).data);
        printf(  "|--------------|                     \n\n\n");
    }

    if (direction == 'r')
    {
        printf("\n|-------------|                         \n");
        printf(  "| %11d |                                \n", parent_data);
        printf(  "|-------------| --                      \n");
        printf(  "                  \\                    \n");
        printf(  "                   \\   |--------------|\n");
        printf(  "                    -> | LEAF CREATED | \n");
        printf(  "                       |--------------| \n");
        printf(  "                       | DATA: %d       \n", (*new_ptr).data);
        printf(  "                       |--------------| \n\n\n");
    }

    if (direction == 'c')
    {
        printf("\n|--------------|\n");
        printf(  "| ROOT CREATED |\n");
        printf(  "|--------------|\n");
        printf(  "| DATA: %d      \n", (*new_ptr).data);
        printf(  "|--------------|\n\n\n");
    }
    
    printf("{LEFT} <- %d\n", x);
    (*new_ptr).left_ptr = create('l', x);

    printf("%d -> {RIGHT}\n", x);
    (*new_ptr).right_ptr = create('r', x);

    return new_ptr;
}

void traverse (struct node* root_ptr)
{
    if (root_ptr == NULL)
    {
        // printf("\n|-------|\n");
        // printf(  "| EMPTY |\n");
        // printf(  "|-------|\n\n");
        
        return;
    }

    traverse((*root_ptr).left_ptr);
    printf("%d ", (*root_ptr).data);
    traverse((*root_ptr).right_ptr);

    return;
}


int main()
{
    int choise = -1;

    struct node* root_ptr;
    root_ptr = (struct node*) NULL;

    root_ptr = create('c', INT_MIN);
    traverse(root_ptr);

    while (choise != 0)
    {
        printf("\n");
        printf("[1] -> CREATE\n");
        printf("[2] -> REMOVE\n");
        printf("[3] -> DISPLAY\n");
        printf("[4] -> SEARCH\n");
        printf("[0] -> QUIT\n\n");

        printf("? "); 
        scanf("%d", &choise);

        switch (choise)
        {
            case 1:
                        
                        break;

            case 2:
                        
                        break;

            case 3:
                        
                        break;

            case 4:
                        
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


