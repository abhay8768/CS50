#include <stdio.h>
#include <cs50.h>
#include <string.h>


int main(void)
{
    printf("give me a string: ");
    char* s = malloc(sizeof(char) * 16 + 1);
    scanf("%s", s);
    
    int count = 0;
    int len = strlen(s);
    for (int i = 0; i < len - 2; i++)
    {
        if (s[i] == 'b' && s[i+1] == 'o' && s[i+2] == 'b')
        {
            count++;
        }
    }
    free(s);
    printf("The number of bobs: %i\n", count);
}
