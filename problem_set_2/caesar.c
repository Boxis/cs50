#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    // if more than 2 arguments then error
    if (argc !=2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // if anything other than a digit for argument, then error
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // convert argument to key (int)
    int k = atoi(argv[1]);
    if (k > 26)
    {
        k = k % 26;
    }

    // get string
    string text = get_string("plaintext: ");
    //string text = "barfoo";
    printf("plaintext: %s\n", text);

    // implement cipher based on key
    printf("ciphertext: ");
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (islower(text[i]))
        {
            if (text[i] + k < 122)
            {
                printf("%c", text[i] + k);
            }
            else
            {
                printf("%c", 96 + (text[i] + k)%122);
            }
        }
        else if (isupper(text[i]))
        {
            if (text[i] + k < 90)
            {
                printf("%c", text[i] + k);
            }
            else
            {
                printf("%c", 64 + (text[i] + k)%90);
            }
        }
        else
        {
            printf("%c", text[i]);
        }

    }

    printf("\n");
}