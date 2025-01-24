#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX_LIMIT 500

int count_letters(char text[]);
int count_words(char text[]);
int count_sentences(char text[]);
int calculate_grade_level(int letters, int words, int sentences);

int main(void) {
    char text[MAX_LIMIT];
    printf("Text: ");
    fgets(text, MAX_LIMIT, stdin);

    int num_of_letters = count_letters(text);
    int num_of_words = count_words(text);
    int num_of_sentences = count_sentences(text);
    int index = calculate_grade_level(num_of_letters, num_of_words, num_of_sentences);

    if (index < 1) 
        printf("Before Grade 1\n");
    else if (index >= 16)
        printf("Grade 16+\n");
    else
        printf("Grade %i\n", index);
        
    return 0;
}

int count_letters(char text[]) {
    int count = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            count++;
        }
    }
    return count;
}

int count_words(char text[]) {
    int count = 0;
    int in_word = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (isspace(text[i])) {
            in_word = 0;
        } else if (in_word == 0) {
            in_word = 1;
            count++;
        }
    }
    return count;
}

int count_sentences(char text[]) {
    int count = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?') {
            count++;
        }
    }
    return count;
}

int calculate_grade_level(int letters, int words, int sentences) {
    // Coleman-Liau index
    float L = ((float) letters / words) * 100;
    float S = ((float) sentences / words) * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    return index;
}