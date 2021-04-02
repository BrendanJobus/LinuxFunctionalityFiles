#include <stdlib.h>
#include <stdio.h>

int main()
{
    int problems, canSolve = 0;
    scanf("%d", &problems);
    for(int i = 0; i < problems; i++)
    {
        int petya, vasya, tonya;
        scanf("%d %d %d", &petya, &vasya, &tonya);
        if( petya + vasya + tonya >= 2)
            canSolve++;
    }
    printf("%d\n", canSolve);
}