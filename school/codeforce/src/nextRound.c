#include <stdlib.h>
#include <stdio.h>

int main()
{
    int n, k, score;
    scanf("%d %d", &n, &k);
    int i = 1;
    int kthScore = 0;
    while(1)
    {
        if(i > n)
        {
            i--;
            break;
        }
        scanf("%d", &score);
        if(i == k)
            kthScore = score;
        if(score < kthScore || score <= 0)
        {
            i--;
            break;
        }
        i++;
    }
    printf("%d\n", i);
}