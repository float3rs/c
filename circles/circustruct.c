# include <stdio.h>
# include <stdlib.h>
# include <float.h>

# define SIZE 7

struct node
{
    float data;
    struct node* next_ptr;
};

struct node* front_ptr = NULL;
struct node* rear_ptr = NULL;

void enqueue(float x)
{
    struct node* new_ptr;
    new_ptr = (struct node*) malloc(sizeof(struct node));

    (*new_ptr).data = x;
    (*new_ptr).next_ptr = NULL;

    if (rear_ptr == NULL)
    {
        front_ptr = new_ptr;
        
        rear_ptr = new_ptr;
        (*rear_ptr).next_ptr = front_ptr;

        printf("\n|----------------|\n");
        printf(  "| QUEUE: CREATED |\n");
        printf(  "|----------------|\n");
    }
    else
    {
        (*rear_ptr).next_ptr = new_ptr;
        
        rear_ptr = new_ptr;
        (*rear_ptr).next_ptr = front_ptr;

        printf("\n|----------|\n");
        printf(  "| ENQUEUED |\n");
        printf(  "|----------|\n");
    }
    
    // free(new_ptr);
    return;
}

float dequeue()
{
    float f = FLT_MIN;
    
    if ((front_ptr == NULL) && (rear_ptr == NULL))
    {
        printf("\n|-----------|\n");
        printf(  "| UNDERFLOW |\n");
        printf(  "|-----------|\n");

        return f;
    }

    if ((*front_ptr).next_ptr == front_ptr)
    {   
        f = (*front_ptr).data;
        
        printf("\n# DATA = [ %f ]\n", f);

        front_ptr = NULL;
        rear_ptr = NULL;

        printf("\n|------------------|\n");
        printf(  "| QUEUE: DESTROYED |\n");
        printf(  "|------------------|\n");
    }
    else
    {
        f = (*front_ptr).data;

        printf("\n# DATA = [ %f ]\n", f);
        
        front_ptr = (*front_ptr).next_ptr;
        (*rear_ptr).next_ptr = front_ptr;
        
        printf("\n|----------|\n");
        printf(  "| DEQUEUED |\n");
        printf(  "|----------|\n");
    }
    return f;
}

void display()
{
    struct node* i_ptr;
    i_ptr = front_ptr;
    
    if (i_ptr == NULL)
    {
        printf("\n|-------|\n");
        printf(  "| EMPTY |\n");
        printf(  "|-------|\n");
        return;
    }

    if ((*i_ptr).next_ptr == i_ptr)
    {
        printf("\n[ %f ]\n", (*front_ptr).data);
        return;
    }
    else
    {
        printf("\n");
        
        printf("[ %f ]\n", (*i_ptr).data);
        i_ptr = (*i_ptr).next_ptr;

        while (i_ptr != front_ptr)
        {
            printf("[ %f ]\n", (*i_ptr).data);
            i_ptr = (*i_ptr).next_ptr;
        }

        return;
    }
}

int main()
{
    int choise = -1;
    int count = 0;
    
    float item;

    while (choise != 0)
    {
        printf("\n");
        printf("COUNT: %d/%d\n", count, SIZE);
        printf("\n");
        
        printf("[1] -> ENQUEUE\n");
        printf("[2] -> DEQUEUE\n");
        printf("[3] -> DISPLAY\n");
        printf("[0] ->    QUIT\n\n");

        printf("? "); 
        scanf("%d", &choise);

        switch (choise)
        {
            case 1:
                        printf("\nINT: ");
                        scanf("%f", &item);

                        if (count < SIZE)
                        {
                            enqueue(item);
                            count++;
                        }
                        else
                        {
                            printf("\n|----------|\n");
                            printf(  "| OVERFLOW |\n");
                            printf(  "|----------|\n");
                        }

                        break;

            case 2:
                        if (dequeue() != FLT_MIN)
                        {
                            count--;
                        }

                        break;

            case 3:
                        display();
                        break;

            case 0:
                        printf("\n");
                        break;

            default:
                        printf("\n|---------|\n");
                        printf(  "| INVALID |\n");
                        printf(  "|---------|\n");
        }
    }

    return 0;
}