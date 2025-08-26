// Sort the given set of elements present in three stack data structures and put them in a single stack using recursion
#define SIZE 25
#define ERR -99999
#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    int arr[SIZE];
    int top;
} stack;

void push(int, stack *);
int pop(stack *);
int peek(stack *);
void display(stack);
void insertTop(stack *, stack *);
stack *create(int);
void sort(stack *, stack *);
int main()
{
    stack *stk1 = create(1);
    stack *stk2 = create(2);
    stack *stk3 = create(3);

    stack *stkf = malloc(sizeof(stack));
    stkf->top = -1;
    printf("Stack-1:\n");
    display(*stk1);
    printf("Stack-2:\n");
    display(*stk2);
    printf("Stack-3:\n");
    display(*stk3);
    sort(stkf, stk1);
    sort(stkf, stk2);
    sort(stkf, stk3);

    printf("The final sorted stack :\n");
    display(*stkf);
    return 0;
}
stack *create(int n)
{
    stack *stk = malloc(sizeof(stack));
    stk->top = -1;
    int size, i, ele;
    printf("For stack-%d:\n", n);
    printf("No. of elements: ");
    scanf("%d", &size);
    printf("Enter %d elements: ", size);
    for (i = 1; i <= size; i++)
    {
        scanf("%d", &ele);
        push(ele, stk);
    }
    return stk;
}
void sort(stack *stkf, stack *stk)
{
    // Sorting in ascending order
    int i;
    int size = stk->top;
    for (i = 0; i <= size; i++)
        insertTop(stkf, stk);
}
void insertTop(stack *stkf, stack *stk)
{
    if (stk->top == -1)
        return;
    else if (stkf->top == -1 || peek(stkf) > peek(stk))
        push(pop(stk), stkf);
    else
    {
        int ele = pop(stkf);
        insertTop(stkf, stk);
        push(ele, stkf);
    }
}
void push(int n, stack *stk)
{
    if (stk->top >= SIZE - 1)
    {
        printf("Stack Overflow.\n");
        return;
    }
    stk->top++;
    stk->arr[stk->top] = n;
}
int pop(stack *stk)
{
    if (stk->top <= -1)
    {
        printf("Stack Underflow.\n");
        return ERR;
    }
    return stk->arr[stk->top--];
}
int peek(stack *stk)
{
    if (stk->top == -1)
        return ERR;
    return stk->arr[stk->top];
}
void display(stack stk)
{
    int i;
    if (stk.top == -1)
    {
        printf("Stack empty\n");
        return;
    }
    for (i = stk.top; i >= 0; i--)
        printf("%d\n", stk.arr[i]);
}
