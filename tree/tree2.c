#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct node
{
    int data;
    struct node*  left_ptr;
    struct node* right_ptr;
};

struct node* create_node_ptr(int item)
{  
    struct node* new_ptr;
    new_ptr = (struct node*) malloc(sizeof(struct node));
    
    if (new_ptr == NULL)
    {
        printf("\n|----------|\n");
        printf(  "| OVERFLOW |\n");
        printf(  "|----------|\n\n");

        return NULL;
    }

    (*new_ptr).data = item;
    (*new_ptr).left_ptr = NULL;
    (*new_ptr).right_ptr = NULL;

    // printf("> CREATED\n");
    // printf("%d\n", (*new_ptr).data);

    return new_ptr;
}
   
void inorder_traverse(struct node* root_ptr, char direction)
{   
    if (direction == 'l')
    {
        printf("<- ");
    }

    if (direction == 'r')
    {
        printf("-> ");
    }
    
    if (root_ptr == NULL)
    {

        // printf("\n|-------|\n");
        // printf(  "| EMPTY |\n");
        // printf(  "|-------|\n\n");
        
        return;
    }

    inorder_traverse((*root_ptr).left_ptr, 'l');
    printf("%d ", (*root_ptr).data);
    inorder_traverse((*root_ptr).right_ptr, 'r');

    return;
}

struct node* insert_node_ptr(struct node* node_ptr, int data)
{   
    if (node_ptr == NULL)
    {
        printf("\n|--- ------|\n");
        printf(  "| INSERTED |\n");
        printf(  "|----------|\n\n");
        
        return create_node_ptr(data);
    }
    
    if (data < (*node_ptr).data)
    {
        printf("> INSERT RECURSION: LEFT\n");
        (*node_ptr).left_ptr = insert_node_ptr((*node_ptr).left_ptr, data);
    }
  
    if (data > (*node_ptr).data)
    {
        printf("> INSERT RECURSION: RIGHT\n");
        (*node_ptr).right_ptr = insert_node_ptr((*node_ptr).right_ptr, data);
    }
  
    return node_ptr;
}

void search_data(struct node* root_ptr, int key)
{
    if (root_ptr == NULL)
    {
        printf("MISS\n");
        return;
    }
    
    if (key == (*root_ptr).data)
    {
        printf("HIT\n");
        return;
    }
    
        if (key < (*root_ptr).data)
        {
            printf("<- ");
            search_data((*root_ptr).left_ptr, key);
            
        }
        
        if (key > (*root_ptr).data)
        {
            printf("-> ");
            search_data((*root_ptr).right_ptr, key);
        }
}

struct node* delete_key(struct node* root_ptr, int key, int replace_by)
{
    if (root_ptr == NULL)
    {
        printf("\n\n|---------|\n");
        printf(    "| REMOVED |\n");
        printf(    "|---------|\n\n");
        
        return root_ptr;
    }

    if ((*root_ptr).data == key)
    {
        if ((*root_ptr).left_ptr == NULL && (*root_ptr).right_ptr == NULL)
        {
            // printf("\n|--------------|\n");
            // printf(  "| LEAF REMOVED |\n");
            // printf(  "|--------------|\n\n");
            
            return NULL;
        }
        else
        {
            if ((*root_ptr).left_ptr == NULL)
            {
                struct node* buffer_ptr;
                buffer_ptr = (*root_ptr).right_ptr;
                
                printf("\n\n|----------|\n");
                printf(    "| REMOVED  |\n");
                printf(    "|----------|\n");
                printf(    "| -> [] -> |\n");
                printf(    "|----------|\n\n");
                
                return buffer_ptr;
            }

            if ((*root_ptr).right_ptr == NULL)
            {
                struct node* buffer_ptr;
                buffer_ptr = (*root_ptr).left_ptr;
                
                printf("\n\n|----------|\n");
                printf(    "|  REMOVED |\n");
                printf(    "|----------|\n");
                printf(    "| <- [] <- |\n");
                printf(    "|----------|\n\n");

                return buffer_ptr;
            }

            if (replace_by == 1) // replace by inorder predecessor
            {
                struct node* buffer_ptr;
                buffer_ptr = (*root_ptr).left_ptr;

                while (((*buffer_ptr).right_ptr != NULL) && (buffer_ptr != NULL))
                {
                    buffer_ptr = (*buffer_ptr).right_ptr;
                }

                printf("\n>        SUBTREE: LEFT\n");
                printf(  ">           ROOT: %d\n", (*(*root_ptr).left_ptr).data );
                printf(  "> RIGHTMOST LEAF: %d\n\n", (*buffer_ptr).data);
                
                (*root_ptr).data = (*buffer_ptr).data;
                (*root_ptr).left_ptr = delete_key((*root_ptr).left_ptr, (*buffer_ptr).data, 1);
            }

            if (replace_by == 2) // replace by inorder successor
            {
                struct node* buffer_ptr;
                buffer_ptr = (*root_ptr).right_ptr;

                while (((*buffer_ptr).left_ptr != NULL) && (buffer_ptr != NULL))
                {
                    buffer_ptr = (*buffer_ptr).left_ptr;
                }

                printf("\n>       SUBTREE: RIGHT\n");
                printf(  ">          ROOT: %d\n", (*(*root_ptr).right_ptr).data );
                printf(  "> LEFTMOST LEAF: %d\n\n", (*buffer_ptr).data);

                (*root_ptr).data = (*buffer_ptr).data;
                (*root_ptr).right_ptr = delete_key((*root_ptr).right_ptr, (*buffer_ptr).data, 2);
            }
        }
    }

    if (key < (*root_ptr).data)
    {
        printf("<- ");
        (*root_ptr).left_ptr = delete_key((*root_ptr).left_ptr, key, replace_by);
    }

    if (key > (*root_ptr).data)
    {
        printf("-> ");
        (*root_ptr).right_ptr = delete_key((*root_ptr).right_ptr, key, replace_by);
    }

    return root_ptr;
    
}



int main()
{
    int choise = -1;
    int replacement = -1;
    int data;
    int key;

    struct node* root_ptr;
    root_ptr = (struct node*) NULL;

    while (choise != 0)
    {
        printf("\n");
        printf("[1] -> INSERT \n");
        printf("[2] -> REMOVE \n");
        printf("[3] -> DISPLAY\n");
        printf("[4] -> SEARCH \n");
        printf("[9] -> TEST \n");
        printf("[0] -> QUIT   \n\n");

        printf("? "); 
        scanf("%d", &choise);

        switch (choise)
        {
            case 1:
                
                printf("\nINT: ");
                scanf("%d", &data);

                printf("\n");

                if (root_ptr == NULL)
                {
                    root_ptr = insert_node_ptr(root_ptr, data);
                }
                else
                {
                    insert_node_ptr(root_ptr, data);
                }
                        
                break;

            case 2:

                while (replacement != 0)
                {
                    printf("\n");
                    printf("[1] -> by INORDER PREDECESSOR \n");
                    printf("[2] -> by INORDER SUCCESSOR\n");
                    printf("[0] -> CANCEL\n\n");

                    printf("REPLACE ? "); 
                    scanf("%d", &replacement);

                    switch (replacement)
                    {
                        case 1:

                            printf("\nKEY: ");
                            scanf("%d", &key);
                            
                            printf("\n");
                            
                            root_ptr = delete_key(root_ptr, key, replacement);
                            
                            printf("\n");

                            replacement = 0;
                            break;

                        case 2:

                            printf("\nKEY: ");
                            scanf("%d", &key);
                            
                            printf("\n");

                            root_ptr = delete_key(root_ptr, key, replacement);
                            
                            printf("\n");
                            
                            replacement = 0;
                            break;

                        case 0:

                            break;

                        default:

                            printf("\n|---------|\n");
                            printf(  "| INVALID |\n");
                            printf(  "|---------|\n\n");
                    }   
                }

                replacement = -1;
                break;

            case 3:
                
                printf("\n");
                inorder_traverse(root_ptr, 'c');
                printf("\n");

                break;

            case 4:
                
                printf("\nKEY: ");
                scanf("%d", &key);
                printf("\n");

                search_data(root_ptr, key);
                break;
            
            case 9:

                root_ptr = insert_node_ptr(root_ptr, 6);
                insert_node_ptr(root_ptr, 8);
                insert_node_ptr(root_ptr, 4);
                insert_node_ptr(root_ptr, 2);
                insert_node_ptr(root_ptr, 5);
                insert_node_ptr(root_ptr, 9);
                insert_node_ptr(root_ptr, 0);
                insert_node_ptr(root_ptr, 7);
                insert_node_ptr(root_ptr, 1);
                insert_node_ptr(root_ptr, 3);

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


