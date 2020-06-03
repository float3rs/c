#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct StackNode 
{ 
    int data; 
    struct StackNode* next; 
}; 
  
struct StackNode* newNode(int data) 
{ 
    struct StackNode* stackNode = (struct StackNode*) malloc(sizeof(struct StackNode)); 

    stackNode->data = data; 
    stackNode->next = NULL; 

    return stackNode; 
} 
  
int isEmpty(struct StackNode* root) 
{ 
    return !root; 
} 
  
void push(struct StackNode** root, int data) 
{ 
    struct StackNode* stackNode = newNode(data);

    stackNode->next = *root; 
    *root = stackNode;
} 
  
int pop(struct StackNode** root) 
{ 
    if (isEmpty(*root))
    {
        return INT_MIN;
    }
    
    struct StackNode* temp = *root;
    int popped;

    *root = (*root)->next; 
    popped = temp->data; 
    
    free(temp); 
  
    return popped; 
} 
  
int peek(struct StackNode* root) 
{ 
    if (isEmpty(root))
    {
        return INT_MIN; 
    }
        
    return root->data; 
} 

int check(char c1, char c2)
{
    if ((c1 == '(' && c2 == ')') ||
        (c1 == '{' && c2 == '}') ||
        (c1 == '[' && c2 == ']'))
    {
        return 1;
    }
    else
    {
        return 0;
    } 
}


int main() 
{
    struct StackNode* root = NULL; 
    int c;
    
    while ((c = getchar()) != EOF)
    {
        // if (c == '\n') continue;

        printf("\n");
        
        if (c == '{' || c == '(' || c == '[')
        {
            push(&root, c);
            
            printf(">       PUSH: %c\n", (char) c);
        }
        else
        {
            if (!(c == '}' || c == ')' || c == ']'))
            {
                printf(">     IGNORE: %c\n", (char) c);
            }
        }
        
        if (c == '}' || c == ')' || c == ']')
        {   
            if (root == NULL)
            {
                printf("\nEXP: [NON BALANCED] -> STACK EXHAUSTED\n");
                printf("\n");

                return 0;
            }
            else
            {
                printf(">        POP: %c\n", (char) c);
                
                if (!check(pop(&root), c))
                {
                    printf("\nEXP: [NON BALANCED] -> UNMATCHED CLOSURE SYMBOLS\n");
                    printf("\n");

                    return 0;
                }
            }
        }

        if (peek(root) == INT_MIN)
        {
            printf("#   STACK EMPTY\n");
        }
        else
        {
            printf("#  STACK TOP: %c\n", (char) peek(root));
        }
    }

    if (root == NULL)
    {
        printf("\n");
        printf("\nEXP: [BALANCED]\n");
        printf("\n");
    }
    else
    {
        printf("\n");
        printf("\nEXP: [NON BALANCED] -> STACK NOT YET EMPTY\n");
        printf("\n");
    }
        
    return 0;
}