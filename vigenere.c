#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    //Check if a single command line argument is given. If not, yell at user and exit.
    if (argc != 2)
    {
        printf("usage: ./vigenere k\n");
        exit(1);
    }

    //Check if the command line argument is completely alphabetical. If not, yell at user and exit.
    string k = argv[1];
    int k_len = strlen(k);
    for (int i = 0; i < k_len; i++)
    {
        if (isalpha(k[i]) == false)
        {
            printf("usage: ./vigenere k\n");
            exit(1);
        }
    }

    //prompt user for plaintext input
    string p = get_string("plaintext: ");

    //let user know output is ciphertext
    printf("ciphertext: ");

    //convert k into series of integers from 0 to 25. Only two branches here, since k only exists of lower and/or upper case characters
    for (int i = 0; i < k_len; i++)
    {
        if (isupper(k[i]))
        {
            //65 since 'A' == 65 in ASCII
            k[i] = k[i] % 65;
        }

        else
        {
            //97 since 'a' == 97 in ASCII
            k[i] = k[i] % 97;
        }
    }


    //NOTE TO SELF: The below works, but might need some more comments (if you were so inclined)

    //Go through p, use k on each character in p and print. Make sure to cycle through k and to wrap around the alphabet when applying k to p.
    for (int i = 0, j = 0, p_len = strlen(p); i < p_len; i++)
    {
        //j is used to cycle through k; here the program makes sure to wrap around k when it comes to the end
        j %= k_len;

        if (isupper(p[i]))
        {
            if (p[i] + k[j] >  'Z')
            {
                p[i] -= 'Z' - '@';
            }

            printf("%c", p[i] + k[j]);
            j++;
        }

        else if (islower(p[i]))
        {
            if (p[i] + k[j] > 'z')
            {
                p[i] -= 'z' - '`';
            }

            printf("%c", p[i] + k[j]);
            j++;
        }

        else
        {
            printf("%c", p[i]);
        }
    }

    printf("\n");

}