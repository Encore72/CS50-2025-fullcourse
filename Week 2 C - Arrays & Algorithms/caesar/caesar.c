#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string s);
char rotate(char c, int k);

int main(int argc, string argv[])
{
    // Makes sure program was run with just one command-line argument
    // argc does not start counting at 0, it starts at 1 and 1 is always by convention
    // the name of the program (./caesar) and 2 is the one command-line argument so if
    // value is different than 2 we are in the wrong
    if (argc != 2)
    {
        printf("You must provide a single command-line argument \n");
        return 1;
    }

    // Calls only_digits and delivers argv[1] (the one command-line argument)
    // we use ! to negate the result we are receiving, so:
    // if only_digits returns true (digits) !true = false so the if block does not execute
    // if only_digits returns false (no digits) !false = true so the if block executes
    if (!only_digits(argv[1]))
    {
        printf("Usage: ./caesar key \n");
        return 1;
    }

    // Convert argv[1] from a string to an int with the atoi method from cs50
    int k = atoi(argv[1]);

    // Prompt user for plaintext
    string plainText = get_string("Plain text? ");

    // Print ciphertext header which will be followed by "char rotated"
    printf("ciphertext: ");

    // For each character in plaintext we call rotate and provide the character [i] and the key (k)
    // we save the rotate return un the variable char rotated and print it, which will print
    // following the ciphertext: header from before
    for (int i = 0; i < strlen(plainText); i++)
    {
        char rotated = rotate(plainText[i], k);
        printf("%c", rotated);
    }

    printf("\n");
    return 0;
}

// receives the one command-line argument as a string
// and checks every char of that string,
// if no digits (!isdigit) return false, otherwise return true
bool only_digits(string s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

// receives "c" which is every character from plaintext and receives the key "k"
// we use isupper and islower from ctype library to check for uppercase or lowercase
// with c - 'A' we get the letter that c is representing position in the alphabet
// e.g. the ASCII value of 'A' (65) acts as the base, when we substract it we shift the
// entire alphabet so A starts at 0, for example A - 'A' would be 65 - 65 = 0 (A is position 0 in
// alphabet) B - 'A' would be 66 - 65 = 1 (B is position 1 in alphabet). It would be the same for
// lowercase Then we add (k), the key, e. g. if key = 3 then we would be doing: 65 - 65 = 0 + 3 = 3,
// our A just shifted to a D (position 3 in alphabet). then we use Modulo (%26) to wrap around in
// case the result exceeds 25 (25 letters in alphabet) because 3 % 26 = 3 or 5 % 26 = 5... and
// finally we add 'A' ASCII value again which is 65. e.g. 5 + 'A' = 5 + 65 = 70, ASCII 70 is letter
// F.
char rotate(char c, int k)
{
    if (isupper(c))
    {
        return ((c - 'A' + k) % 26) + 'A';
    }
    else if (islower(c))
    {
        return ((c - 'a' + k) % 26) + 'a';
    }
    else
    {
        return c;
    }
}
