#include <stdio.h>
#include <stdlib.h>

int main()
{
    int lines;
    scanf("%d", &lines);

    int characters;
    char * word;
    word = malloc(sizeof(char) * 100);

    for(int i = 0; i < lines; i++)
    {
        characters = 0;
        scanf("%s", word);
        while(word[characters] != 0)
        {
            characters++;
        }
        characters--;
        if(characters >= 10)
        {
            printf("%c%d%c\n", word[0], characters - 1, word[characters]);
            for(int j = 0; j < 100; j++)
            {
                word[j] = 0;
            }
        }
        else
        {
            printf("%s\n", word);
        }
        
    }
}