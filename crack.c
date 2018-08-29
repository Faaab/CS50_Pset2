#define _XOPEN_SOURCE
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

bool keycheck(string userhash, string key, string salt);

int main(int argc, string argv[])
{
    //if no argument is given, or the hash is not the correct length, yell at user
    if(argc != 2)
    {
        printf("usage: ./crack hash\n");
        exit(1);
    }

    //store user's hash in string called userhash, store first two characters of hash in string called salt
    string userhash = argv[1];
    char salt[3];
    salt[0] = userhash[0];
    salt[1] = userhash[1];
    salt[2] = '\0';

    //print userhash and salt back to user (for checking purposes)
    printf("userhash: %s\n", userhash);
    printf("salt: %s\n", salt);

    //Array called key will contain the generated key. Array called ntol (for number to letter) is used to iterate over possible keys.
    char key[6] = { 0 };
    int ntol[6] = { 0 };

    //Iterate over every possible combination of up to 5 alphabetical characters. Check if generated sequence of character is the key.
    do
    {
        ntol[0]++;

        //spill over and wrap around if an int in ntol gets too high
        for (int i = 1; i < 5; i++)
        {
            if (ntol[i - 1] >= 53)
            {
                ntol[i]++;
                ntol[i - 1] = 1;
            }
        }

        //Translate each int in ntol into an alphabetical character; place character in key.
        for (int i = 0; i < 6; i++)
        {
            //if ntol[i] == 0, algorithmdoes nothing; key[i] stays 0. If it is between 1 and 26 (inc), assign uppercase letter to key[i].
            if (ntol[i] > 0 && ntol[i] <= 26)
            {
                key[i] = ntol[i] - 1 + 65;
            }
            //If ntol[i] is between 27 and 52 (inc), assign lowercase letter to key[i].
            else if (ntol[i] >= 27 && ntol[i] <= 52)
            {
                key[i] = ntol[i] - 27 + 97;
            }
        }

        //Check if generated key is equal to the key used to create userhash.
        if (keycheck(userhash, key, salt))
        {
            printf("cracked password: %s\n", key);
            return 0;
        }
    } while (ntol[4] < 52);

    //if the program reaches this line, something went wrong. Probably the hash was not made with 5 alphabetical characters.
    printf("key not found\n");
    return 1;
}

bool keycheck(string userhash, string key, string salt)
{
    string checkhash = crypt(key, salt);

    for (int i = 0, n = strlen(userhash); i < n; i++)
    {
        if (userhash[i] != checkhash[i])
        {
            return 0;
        }
    }

    return 1;
}