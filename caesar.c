#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    //Program only works when user has used a command-line argument. If no argument is given, program yells at user.
    if (argc != 2)
    {
        printf("usage: ./caesar k\n");
        exit(1);
    }

    //store key in k; make sure it is less between 0 and 25 (inclusive).
    int k = atoi(argv[1]) % 26;

    //Get plaintext input from user
    string s = get_string("plaintext: ");

    //Let user know that the output is ciphertext
    printf("ciphertext: ");

    //look at the ith character in the string, convert it to ciphertext and print it
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        //branch for encrypting and printing uppercase letters.
        if (isupper(s[i]))
        {
            if (s[i] + k > 'Z')
            {
                //To wrap around alphabet, @ is used as it is the character before 'A'
                s[i] = s[i] - ('Z' - '@');
            }

            printf("%c", s[i] + k);
        }

        //branch for encrypting and printing lowercase letters
        else if (islower(s[i]))
        {
            if (s[i] + k > 'z')
            {
                //To wrap around alphabet, ` is used as it is the character before 'a'
                s[i] = s[i] - ('z' - '`');
            }

            printf("%c", s[i] + k);
        }

        //Print every character in the string that is neither upper nor lower case, i.e. not alphabetic.
        else
        {
            printf("%c", s[i]);
        }
    }

    //end with new line
    printf("\n");
}