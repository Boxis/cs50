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
        printf("Usage: ./substitution key\n");
        return 1;
    }

    int n = strlen(argv[1]);

    if (n < 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // if anything other than a digit for argument, then error
    for (int i = 0; i < n; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
    }

    // check for repeated characters
    for (int i = 0; i < n; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            if (argv[1][i] == argv[1][j])
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }

    // get string
    string text = get_string("plaintext: ");
    //string text = "hello, world";
    printf("plaintext: %s\n", text);

    int len_text = strlen(text);
    // implement cipher based on key
    printf("ciphertext: ");
    for (int i = 0; i < len_text; i++)
    {

        if (isalpha(text[i]))
        {
            if (islower(text[i]))
            {
                char letter = tolower(argv[1][text[i]-97]);
                printf("%c", letter);
            }
            else
            {
                char letter = toupper(argv[1][text[i]-65]);
                printf("%c", letter);
            }
        }
        else
        {
            printf("%c", text[i]);
        }

    }
    printf("\n");
    return 0;
}