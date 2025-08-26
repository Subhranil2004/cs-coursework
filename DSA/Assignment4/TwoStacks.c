// Implementation of two stacks in a single array
#define MAX 10
#include <stdio.h>
typedef struct
{
    int arr[MAX];
    int top1;
    int top2;
} stack;
void push(int, stack *, int);
int pop(stack *, int);
void display(stack, int);
int main()
{
    int ch;
    int ele;
    int stkno;
    printf("Two Stack Implementation\n");
    stack stk;
    stk.top1 = -1;
    stk.top2 = MAX;
    do
    {
        printf("\nMenu :\n1. Push element\n2. Pop element\n3. Display Stack\n4. Exit\n");
        printf("Enter your choice as integer : ");
        scanf("%d", &ch);
        printf("Enter stack no.(1/2) : ");
        scanf("%d", &stkno);
        switch (ch)
        {
        case 1:
            printf("Element to push : ");
            scanf("%d", &ele);
            if (stkno == 1)
                push(ele, &stk, stkno);
            else
                push(ele, &stk, stkno);
            break;
        case 2:
            ele = pop(&stk, stkno);
            if (ele != -99999)
                printf("Popped element from stack-%d : %d.", stkno, ele);
            break;
        case 3:
            display(stk, stkno);
            break;
        case 4:
            printf("Exiting...\n");
            break;
        default:
            printf("Wrong choice.Enter value from 1 to 4\n");
        }
    } while (ch != 4);
}
void push(int n, stack *stk, int stkno)
{
    if (stk->top1 >= stk->top2)
    {
        printf("Stack Overflow.\n");
        return;
    }
    if (stkno == 1)
    {

        stk->top1++;
        stk->arr[stk->top1] = n;
    }
    else
    {
        stk->top2--; // !
        stk->arr[stk->top2] = n;
    }
}
int pop(stack *stk, int stkno)
{
    if (stkno == 1)
    {
        if (stk->top1 <= -1)
        {
            printf("Stack-%d Underflow.\n", stkno);
            return -99999;
        }
        return stk->arr[stk->top1--];
    }
    else
    {
        if (stk->top2 >= MAX)
        {
            printf("Stack-%d Underflow.\n", stkno);
            return -99999;
        }
        return stk->arr[stk->top2--];
    }
}
void display(stack stk, int stkno)
{
    int i;
    printf("Stack-%d:\n", stkno);
    if (stkno == 1)
    {
        if (stk.top1 == -1)
        {
            printf("Stack-%d empty\n", stkno);
            return;
        }
        for (i = stk.top1; i >= 0; i--)
            printf("%d\n", stk.arr[i]);
    }
    else
    {
        if (stk.top2 == MAX)
        {
            printf("Stack-%d empty\n", stkno);
            return;
        }
        for (i = stk.top2; i < MAX; i++)
            printf("%d\n", stk.arr[i]);
    }
}
