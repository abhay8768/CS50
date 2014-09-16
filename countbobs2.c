#include <stdio.h>
#include <cs50.h>
#include <string.h>


int main(void)
{
    printf("give me a string: ");
    char* s = malloc(sizeof(char) * 16 + 1);
    scanf("%s", s);
    
    char cur[4];
    cur[3] = '\0';
    
    int count = 0;
    int len = strlen(s);
    for (int i = 0; i < len - 2; i++)
    {
        for (int j = 0, n = i; j < 3; j++, n++)
        {
            cur[j] = s[n];
        }
        if (strcmp(cur, "bob") == 0)        // 要用strcmp函数，cur必须是字符串，即cur中要有'\0';
        {
            count++;
        }
    }
    free(s);
    printf("The number of bobs: %i\n", count);
}
