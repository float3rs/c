# include <stdio.h>
# define SIZE 5

int circularray[SIZE];

int front = -1;
int rear = -1;

void enqueue (int item)
{
    if ((front == -1) &&  (rear == -1))
    {
        printf("\n|-----||-----|\n");
        printf(  "|     ||     | <- [ %d ]\n", item);
        printf(  "|-----||-----|\n\n");

        front = 0;
        rear = 0;

        circularray[rear] = item;
        return;
    }
    
    if (((rear + 1) % SIZE) == front)
    {
        printf("\n<!> //////// <!>\n");
        printf("<!> OVERFLOW <!>\n");
        printf("<!> //////// <!>\n\n");

        return;
    }
    else
    {
        
        printf("\n|-----||-----|\n");
        printf(  "|  X  ||     | <- [ %d ]\n", item);
        printf(  "|-----||-----|\n\n");

        rear = (rear + 1) % SIZE;

        circularray[rear] = item;

        return;
    }
}

void dequeue()
{
    if ((front == -1) && (rear == -1))
    {
        
        printf("\n<!> ///////// <!>\n");
        printf("<!> UNDERFLOW <!>\n");
        printf("<!> ///////// <!>\n\n");
        return;
    }
    
    if (front == rear)
    {
        
        printf("\n                   |-----||-----|\n");
        printf(  " [ %10d ] <- |     ||     |\n", circularray[front]);
        printf(  "                   |-----||-----|\n\n");

        front = -1;
        rear = -1;

        return;
    }
    else
    {
        printf("\n                   |-----||-----|\n");
        printf(  " [ %10d ] <- |     ||  X  |\n", circularray[front]);
        printf(  "                   |-----||-----|\n\n");
        
        front = (front + 1) % SIZE;

        return;
    }
}

void display()
{
    int frontCursor = front;

    if ((front == -1) && (rear == -1))
    {
        printf("\n|-------|\n");
        printf(  "| EMPTY |\n");
        printf(  "|-------|\n");
    }
    else
    {
        printf("\n");

        if (((rear + 1) % SIZE) == frontCursor)
        {
            printf("[ %d ]", circularray[frontCursor]);
            frontCursor = (frontCursor + 1) % SIZE;
        }
        
        while (((rear + 1) % SIZE) != frontCursor)
        {
            printf("[ %d ]", circularray[frontCursor]);
            frontCursor = (frontCursor + 1) % SIZE;
        }

        printf("\n");
    }

    printf("\n");
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
                        printf("\n> INVALID <\n\n");
        }
    }

    return 0;

}
