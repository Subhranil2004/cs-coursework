// Operations on fractions
#include <stdio.h>
#include <stdlib.h>

void scan_fraction(int *, int *);
char get_operator();
void add_fractions(int, int, int, int, int *, int *);
void multiply_fraction(int, int, int, int, int *, int *);
int find_gcd(int, int);
void reduce_fraction(int *, int *);
void print_fraction(int, int);

int main()
{
    int num1, denom1, num2, denom2;
    int *n_ansp = malloc(sizeof(int));
    int *d_ansp = malloc(sizeof(int));
    printf("Common fractions(Format : a/b), where a and b(≠0) are integers\n");
    printf("Enter fraction 1 : ");
    scan_fraction(&num1, &denom1);
    printf("Enter fraction 2 : ");
    scan_fraction(&num2, &denom2);
    if (denom1 == 0 || denom2 == 0)
    {
        printf("Error: 0 denominator in fraction. Exiting...");
        exit(0);
    }

    printf("Enter the operator to perform the corresponding operation : ");

    switch (get_operator())
    {
    case '+':
        add_fractions(num1, denom1, num2, denom2, n_ansp, d_ansp);
        printf("Result :\n");
        print_fraction(num1, denom1);
        printf("+ ");
        print_fraction(num2, denom2);
        printf("= ");
        print_fraction(*n_ansp, *d_ansp);
        break;
    case '-':
        add_fractions(num1, denom1, -num2, denom2, n_ansp, d_ansp);
        printf("Result :\n");
        print_fraction(num1, denom1);
        printf("- ");
        print_fraction(num2, denom2);
        printf("= ");
        print_fraction(*n_ansp, *d_ansp);
        break;
    case '*':
        multiply_fraction(num1, denom1, num2, denom2, n_ansp, d_ansp);
        printf("Result :\n");
        print_fraction(num1, denom1);
        printf("* ");
        print_fraction(num2, denom2);
        printf("= ");
        print_fraction(*n_ansp, *d_ansp);
        break;
    case '/':
        if (num2 == 0)
        {
            printf("Error : Division by 0. Exiting...");
            exit(0);
        }
        multiply_fraction(num1, denom1, denom2, num2, n_ansp, d_ansp);
        printf("Result :\n");
        print_fraction(num1, denom1);
        printf("/ ");
        print_fraction(num2, denom2);
        printf("= ");
        print_fraction(*n_ansp, *d_ansp);
        break;
    default:
        printf("Wrong operator.Exiting...");
    }
    printf("\n");
    return 0;
}

void scan_fraction(int *num, int *den)
{
    scanf("%d/%d", num, den);
}

char get_operator()
{
    char op = getchar();
    while (op == ' ' || op == '\n' || op == '\t')
        op = getchar();
    return op;
}

void add_fractions(int n1, int d1, int n2, int d2, int *n_ansp, int *d_ansp)
{
    *d_ansp = d1 * d2;
    *n_ansp = n1 * d2 + n2 * d1;
    reduce_fraction(n_ansp, d_ansp);
}

void multiply_fraction(int n1, int d1, int n2, int d2, int *n_ansp, int *d_ansp)
{
    *n_ansp = n1 * n2;
    *d_ansp = d1 * d2;
    reduce_fraction(n_ansp, d_ansp);
}

int find_gcd(int n1, int n2)
{
    if (n2 == 0)
        return n1;
    else
        return find_gcd(n2, n1 % n2);
}

void reduce_fraction(int *nump, int *denomp)
{
    int gcd = find_gcd(*nump, *denomp);
    *nump = *nump / gcd;
    *denomp = *denomp / gcd;
}

void print_fraction(int num, int denom)
{
    printf("(%d/%d) ", num, denom);
}
