#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// using the Coleman-Liau index to find out the readability level
// index = 0.0588 * L - 0.296 * S - 15.8
// L is average number of words per 100 words in text
// S is average number of sentences per 100 words in text

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // get user input text to analyze
    string text = get_string("Text: ");
    // string text = "It was a bright cold day in April, and the clocks were striking thirteen. Winston Smith, his chin nuzzled into his breast in an effort to escape the vile wind, slipped quickly through the glass doors of Victory Mansions, though not quickly enough to prevent a swirl of gritty dust from entering along with him.";

    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    printf("Text: %s\n", text);
    printf("%d letter(s)\n", letters);
    printf("%d word(s)\n", words);
    printf("%d sentence(s)\n", sentences);
    printf("\n");

    // find L: avg number of letters per 100 words in text
    // 100 / total words = factor to multiply total letters to get avg # of letters per 100 words
    float avg_letters = 100.0/words*letters;

    // find S: avg number of sentences per 100 words in text
    // 100 / total words = factor to multiply total sentences to get avg # of sentences per 100 words
    float avg_sentences = 100.0/words*sentences;

    float index = 0.0588 * avg_letters - 0.296 * avg_sentences - 15.8;
    int grade = round(index);
    // printf("L: %f\n", avg_letters);
    // printf("S: %f\n", avg_sentences);

    // print grade
    if(grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    }

}

int count_letters(string text)
{
    int letters = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            letters ++;
        }
    }
    return letters;
}

int count_words(string text)
{
    int words = 1;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isspace(text[i]))
        {
            words ++;
        }
    }
    return words;
}

int count_sentences(string text)
{
    int sentences = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.'|| text[i] == '!' || text[i] == '?')
        {
            sentences ++;
        }
    }
    return sentences;
}
