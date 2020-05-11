# include <stdio.h>
# include <limits.h>

# define SIZE 4

int circularray[SIZE];

int front = -1;
int rear = -1;

void enqueue (int x)
{
    if ((front == -1) &&  (rear == -1))
    {
        printf("\n|----------------|\n");
        printf(  "| QUEUE: CREATED |\n");
        printf(  "|----------------|\n\n");

        front = 0;
        rear = 0;

        circularray[rear] = x;
        return;
    }
    
    if (((rear + 1) % SIZE) == front)
    {
        printf("\n|----------|\n");
        printf(  "| OVERFLOW |\n");
        printf(  "|----------|\n\n");

        return;
    }
    else
    {
        
        printf("\n|----------|\n");
        printf(  "| ENQUEUED |\n");
        printf(  "|----------|\n\n");

        rear = (rear + 1) % SIZE;

        circularray[rear] = x;

        return;
    }
}

int dequeue()
{
    int data = INT_MIN;
    
    if ((front == -1) && (rear == -1))
    {
        
        printf("\n|-----------|\n");
        printf(  "| UNDERFLOW |\n");
        printf(  "|-----------|\n\n");
        
        return data;
    }
    
    if (front == rear)
    {
        
        data = circularray[front];
        
        printf("\n# DEQUEUED = [ %d ]\n", data);

        front = -1;
        rear = -1;

        printf("\n|------------------|\n");
        printf(  "| QUEUE: DESTROYED |\n");
        printf(  "|------------------|\n\n");

        return data;
    }
    else
    {
        data = circularray[front];
        
        printf("\n# DATA = [ %d ]\n", data);
        
        printf("\n|----------|\n");
        printf(  "| DEQUEUED |\n");
        printf(  "|----------|\n\n");
        
        front = (front + 1) % SIZE;

        return data;
    }
}

void display()
{
    int frontCursor = front;

    if ((front == -1) && (rear == -1))
    {
        printf("\n|-------|\n");
        printf(  "| EMPTY |\n");
        printf(  "|-------|\n\n");
    }
    else
    {
        printf("\n");

        if (((rear + 1) % SIZE) == frontCursor)
        {
            printf("[ %10d ]\n", circularray[frontCursor]);
            frontCursor = (frontCursor + 1) % SIZE;
        }
        
        while (((rear + 1) % SIZE) != frontCursor)
        {
            printf("[ %10d ]\n", circularray[frontCursor]);
            frontCursor = (frontCursor + 1) % SIZE;
        }

        printf("\n");
    }

    return;
}

int main()
{
    int choise = -1;
    int item;

    printf("\nSIZE: %d\n\n", SIZE);

    while (choise != 0)
    {
        printf("FRONT: %d\n", front);
        printf(" REAR: %d\n", rear);
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
                        scanf("%d", &item);

                        enqueue(item);
                        break;

            case 2:
                        dequeue();
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
                        printf(  "|---------|\n\n");
        }
    }

    return 0;
}
