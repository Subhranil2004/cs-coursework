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
    int n;
    printf("n = ");
    scanf("%d", &n);
    int s, t, gcd;
    int count = 0;
    printf("Eqn: (b * t) mod %d = 1\n", n);
    printf("[b, t] pairs:\n");
    for (int b = 1; b < n; b++)
    {
        extended_euclidean_algo(n, b, &s, &t, &gcd);
        if (gcd == 1)
        {
            if (t < 0)
                t = (n + t) % n;
            printf("[%d, %d]\n", b, t);
            count++;
        }
    }
    printf("Count = %d\n", count);
}