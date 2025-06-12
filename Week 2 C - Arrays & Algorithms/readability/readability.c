#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // prompt user for input text
    string text = get_string("Text: ");

    // variables to count letters, words and sentences
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // calculate L (average letters per 100 words) and S (average sentences per 100 words) for
    // Coleman-Lieau index we don't cast letters and sentences to a float because C does so
    // automatically when there is another float in the division (words).
    float L = (letters / (float) words) * 100;
    float S = (sentences / (float) words) * 100;

    // calculate Coleman-Liau index
    float grade_calculation = 0.0588 * L - 0.296 * S - 15.8;

    // grade level rounding to nearest integer with CS50 round method
    int grade = (int) round(grade_calculation);

    // grade level print
    if (grade <= 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 1 && grade < 16)
    {
        printf("Grade %i\n", grade);
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
}

// method to count letters using strlen and isalpha from CS50 library
int count_letters(string text)
{
    int letters = 0;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }

    return letters;
}

// method to count words, we use a bool to check if we are in a word or not, we start assuming we
// are not in a word until we find something that's not a space, then we asumme we are in a word
// until the next space so words++ and the bool gets back to false until we find again a char
// different than a space, which will prompt another words++
int count_words(string text)
{
    int words = 0;
    bool are_we_in_a_word = false;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] != ' ' && !are_we_in_a_word)
        {
            words++;
            are_we_in_a_word = true;
        }
        else if (text[i] == ' ')
        {
            are_we_in_a_word = false;
        }
    }

    return words;
}

// method to count sentences, similar logic to count_words, we use a bool flag and we
// start assuming we are not in a sentence until we find an alphabetic character, then
// when we find a . ! ? we sentences++ and return the bool to false
int count_sentences(string text)
{
    int sentences = 0;
    bool are_we_in_a_sentence = false;

for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isalpha(text[i]) && !are_we_in_a_sentence)
        {
            are_we_in_a_sentence = true; // Start of a potential sentence
        }
        else if ((text[i] == '.' || text[i] == '!' || text[i] == '?') && are_we_in_a_sentence)
        {
            sentences++; // Count a sentence only if we were in one
            are_we_in_a_sentence = false; // Reset for the next sentence
        }
    }

    return sentences;
}

