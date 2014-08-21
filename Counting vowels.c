#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main()
{
    printf("Give me a string: ");
    string s = GetString();
    int n = strlen(s);
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u')
        {
            count += 1;
        }
    }
    printf("%i\n", count);
}
