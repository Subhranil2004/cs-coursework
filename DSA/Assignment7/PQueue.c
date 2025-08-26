// Priority Queue
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// A linked list (LL) node to store a queue entry
typedef struct QNode
{
    struct QNode *prev;
    char data[20];
    struct QNode *next;
} node;

typedef struct Queue
{
    struct QNode *front, *rear;
} Queue;

// A utility function to create an empty queue
Queue *createQueue()
{
    Queue *q = (Queue *)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

int stringcmp(char *str1, char *str2)
{
    int i;
    for (i = 0; i < strlen(str1); i++)
    {
        if (toupper(str1[i]) < toupper(str2[i]))
            return -1;
        else if(toupper(str1[i]) > toupper(str2[i]))
            return 1;
    }
    if(str1[i] == '\0' && str2[i] == '\0')
        return 0;
    else
        return -1; // As '\0' <= any char.
}

void enQueue(Queue *q, char item[20])
{
    // Create a new LL node
    node *new = malloc(sizeof(node));
    strcpy(new->data, item);
    new->next = NULL;
    new->prev = NULL;
    // If queue is empty, then new node is front and rear
    // both
    if (q->rear == NULL)
    {
        q->front = q->rear = new;
        return;
    }
    node *temp = q->rear;
    while (temp != NULL)
    {
        if (stringcmp(item, temp->data) == 1)
        {
            if (temp != q->rear)
            {
                new->next = temp->next;
                new->prev = temp;
                temp->next->prev = new;
                temp->next = new;
            }
            else
            {
                temp->next = new;
                new->prev = temp;
                q->rear = new;
            }
            break;
        }
        temp = temp->prev;
    }

    if (temp == NULL)
    {
        temp = q->front;
        temp->prev = new;
        new->next = temp;
        q->front = new;
    }
}

// Function to remove a data from given queue q
char *extractMin(Queue *q, char min[20])
{
    // If queue is empty, return NULL.

    // Store previous front and move front one node ahead
    node *temp = q->front;
    // char min[20];
    strcpy(min, temp->data);
    q->front = q->front->next;

    // If front becomes NULL, then change rear also as NULL
    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
    return min;
}

void displayQ(Queue *q)
{
    node *temp = q->front;
    if(temp == NULL)
    {
        printf("Empty Queue.\n");
        return;
    }
    while(temp->next!=NULL)
    {
        printf("'%s' -> ", temp->data);
        temp = temp->next;
    }
    printf("'%s'\n", temp->data);
}

void merge(Queue *q1, Queue *q2)
{
    Queue *merged = createQueue();
    Queue *temp = q1;
    char min[20];
    while(temp->front != NULL)
    {
        enQueue(merged, extractMin(temp, min));
        displayQ(temp);
    }
    
    temp = q2;
    while(temp->front != NULL)
    {
        enQueue(merged, extractMin(temp, min));
        displayQ(temp);
    }
    printf("Merged Queue: \n");
    displayQ(merged);
}

int main()
{
    Queue *q1 = createQueue();
    Queue *q2 = createQueue();
    Queue *current;
    int ch1, ch2;
    char item[20];
    do
    {
        printf("MAIN MENU:(Queues to perform operations on)\n1. 1st Priority Queue\n2. 2nd Priority Queue\n3. Merge two Queues\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch1);
        switch (ch1)
        {
        case 1:
            current = q1;
            break;
        case 2:
            current = q2;
            break;
        case 3:
            merge(q1, q2);
            printf("\n");
            break;
        case 4:
            printf("Exiting...\n");
            break;
        default:
            printf("Wrong choice.\n");
        }
        if (ch1 == 1 || ch1 == 2)
        {
            char min[20];
            do
            {
                printf("\nMENU:\n1. Enqueue\n2. Extract Minimum\n3. Return to MAIN MENU\n");
                printf("Enter your choice: ");
                scanf("%d", &ch2);
                switch (ch2)
                {
                case 1:
                    printf("Item: ");
                    scanf("%s", item);
                    enQueue(current, item);
                    displayQ(current);
                    break;
                case 2:

                    if (current->front == NULL)
                        printf("Queue is empty.\n");
                    else
                    {
                        printf("Minimum element extracted: '%s'\n", extractMin(current, min));
                        displayQ(current);
                    }
                    break;
                case 3:
                    printf("\n");
                    break;
                default:
                    printf("Wrong choice.\n");
                }
            } while (ch2 != 3);
        }

    } while (ch1 != 4);
}
