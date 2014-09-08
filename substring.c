#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    printf("Give me a string: ");
    char* s = GetString();
    
    int len = strlen(s);
    char cur[len];
    char longest[len];
    
    
    cur[0] = s[0];
    longest[0] = s[0];
    int j = 0;
    int m = 0;
    
    for (int i = 1; i < len; i++)
    {   
       
        if (s[i] >= cur[j])
        {
            cur[j+1] = s[i];
            j++;
            if (j > m)
            {
                for (int k = 0; k <= j; k++)
                {
                    longest[k] = cur[k];
                }
                m = j;
            }
        }
        else
        {
            cur[0] = s[i];
            j = 0;
        }
    }
    if (len < 2)
    {
        printf("%c\n", longest[0]);
    }
    else
    {
        printf("%s\n", longest);
    }
    
   
}
