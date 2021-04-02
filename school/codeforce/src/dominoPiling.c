#include <stdlib.h>
#include <stdio.h>

int main()
{
    int m, n;
    scanf("%d %d", &m, &n);

    int answer, otherAnswer, mDivide, nDivide, addAnother = 0;

    if(m % 2 == 1)
    {
        m -= 1;
        addAnother = n / 2;
    }
    else if(n % 2 == 1)
    {
        n -= 1;
        addAnother = m / 2;
    }

    mDivide = m / 2;
    nDivide = n / 1;
    answer = mDivide * nDivide;

    mDivide = m / 1;
    nDivide = n / 2;
    otherAnswer = mDivide * nDivide;
    answer = (answer > otherAnswer) ? answer : otherAnswer;
    answer += addAnother;
    printf("%d\n", answer);
}