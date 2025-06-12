#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool validate_key(string key);
string encrypt(string plaintext, string key);

int main(int argc, string argv[])
{
    // Check for correct number of command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Validate the key, if it returns true !validate_key converts that true to false and the if
    // block does not execute if it returns false, !validate_key converts that false to true and the
    // if block executes
    if (!validate_key(argv[1]))
    {
        printf("Key must contain 26 unique alphabetic characters\n");
        return 1;
    }

    // Get plaintext from user
    printf("plaintext: ");
    string plaintext = get_string("");

    // Encrypt and print ciphertext
    printf("ciphertext: %s\n", encrypt(plaintext, argv[1]));

    return 0;
}

// Validate the key: must be 26 chars, all alphabetic, no duplicates
bool validate_key(string key)
{
    // Check length, if it's not 26 it fails (returns false)
    if (strlen(key) != 26)
    {
        return false;
    }

    // Check for alphabetic characters and duplicates
    int seen[26] = {0};          // create an array of 26 elements that are all started at {0} value
    for (int i = 0; i < 26; i++) // we run a for loop 26 times (for 26 key chars)
    {
        if (!isalpha(key[i])) // each time the for is run [i] runs through the entire key
        {
            return false; // Non-alphabetic character
        }

        // Convert to uppercase for case-insensitive comparison (we will fill the 26 values of
        // 'seen' with all uppercase to properly check duplicates)
        char c = toupper(key[i]); // we save each key[i] char to (c) variable
        int index = c - 'A'; // we assign that key char an index which will represent the position
                             // of that char in the alphabet, same as with caesar

        // Check for valid range in the alphabet and 'seen[index] != 0' checks for duplicates
        // because when checking in the seen[] array, each letter (index) will modify the value of
        // that array element (at the index position) with a +1 therefore, next time we get the same
        // index (same letter position in the alphabet) we will check if in the seen[] the element
        // that corresponds with the index position is already +1, so we check with != if it's a 1,
        // if it's a 1 it means we have a duplicate
        if (index < 0 || index >= 26 || seen[index] != 0)
        {
            return false; // Invalid character or duplicate
        }
        seen[index]++; // if the character is not duplicate, this increases that seen[] element from
                       // 0 to 1
    }

    return true;
}

// Encrypt the plaintext using the key
string encrypt(string plaintext, string key)
{
    // We assign the plaintext string to ciphertext string so we can cipher it
    string ciphertext = plaintext;

    // it's 27 so it can hold the 26 chars of the key + the null terminator (\0)
    char key_upper[27];

    // we loop through the 26 chars of the key, uppercase each of them for consistency and store
    // them in key_upper[]
    for (int i = 0; i < 26; i++)
    {
        key_upper[i] = toupper(key[i]);
    }
    key_upper[26] = '\0'; // we add the null terminator to make key_upper a valid C string

    // Encrypt each character
    int n =
        strlen(plaintext); // how long the plaintext is (how many characters to know how many loops)
    for (int i = 0; i < n; i++)
    {
        if (isalpha(plaintext[i])) // if the character in the plaintext is alphabetical (if not we
                                   // skip), then
        {
            // we stablish a reference point for the alphabet, we check if the character of the
            // plaintext being examined is uppercase or lowercase then with a terniary operator we
            // assign upper or lowercase ASCII value
            char referencePoint = isupper(plaintext[i]) ? 'A' : 'a';

            // we set an index value, like always substrating the reference point to the character
            // of the plaintext e.g. if plaintext[i] is C (ASCII 67) -uppercase- our referencePoint
            // will be 'A' (uppercase) so ASCII 65, then 67-65 = 2 (C is the 2nd letter of the
            // alphabet from 0)
            int index = plaintext[i] - referencePoint;

            // while checking for upper or lowercase (terniary again) we substitute each of the
            // plaintext[i] characters position by position with the equivalent index position of
            // key_upper, which is the original key e.g: if index is 2 like in the last commentary,
            // and key is 'NQXPOMAFTRHLZGECYJIUWSKDVB' position 2 is 'X', so C will be substituted
            // with X
            ciphertext[i] = isupper(plaintext[i]) ? key_upper[index] : tolower(key_upper[index]);
        }
    }

    return ciphertext;
}
