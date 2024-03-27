#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *longest;

char *longest_word(const char *str);

int main()
{
    longest = longest_word("la fava puppami fava");

    printf("%s\n", longest);
}

char *longest_word(const char *str)
{
    int i = 0;
    int len = 0;
    int last = 0;
    while (str[i] != '\0')
    {
        if ((str[i] == ' ') && i -last > len)
        {
            i++;
            len = i - last;
            longest = malloc(len * sizeof(char));
            for (int j = last,k=0; j < i; j++,k++)
            {
                longest[k] = str[j];
            }
            
            last = i;
        }
        
        i++;
    }
    return longest;
}