#include <stdio.h>
#include <stdlib.h>
int extended_euclidean_algo(int a, int b, int *s, int *t, int *gcd)
{
    int r1 = a, r2 = b;
    int s1 = 1, s2 = 0;
    int t1 = 0, t2 = 1;

    while (r2 > 0)
    {
        int q = r1 / r2;
        // updating r's
        int r = r1 - q * r2;
        r1 = r2;
        r2 = r;

        // updating s's
        *s = s1 - q * s2;
        s1 = s2;
        s2 = *s;

        // updating t's
        *t = t1 - q * t2;
        t1 = t2;
        t2 = *t;
    }
    *gcd = r1;
    *s = s1;
    *t = t1;
}
int main()
{
    int a, b;
    printf("a, b = ");
    scanf("%d %d", &a, &b);
    int s, t, gcd;

    extended_euclidean_algo(a, b, &s, &t, &gcd);

    printf("Eqn: s * a + t * b = gcd(a,b)");
    printf("\n=> %d * %d + %d * %d = %d", s, a, t, b, gcd);
    printf("\ns = %d, t = %d\n", s, t);
}