#include <stdio.h>
#include <cs50.h>
#include <string.h>


int main(void)
{
    printf("give me a string: ");
    char* s = malloc(sizeof(char) * 16 + 1);
    scanf("%s", s);
    
    char cur[3];
    
    int count = 0;
    int len = strlen(s);
    for (int i = 0; i < len - 2; i++)
    {
        for (int j = 0; j < 3 && i < i + 3; j++, i++)
        {
            cur[j] = s[i];
        }
        if (strcmp(cur, "bob") == 0)
        {
            count++;
        }
    }
    free(s);
    printf("The number of bobs: %i\n", count);
}
