#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define PLAYERS 2

const char LETTERS[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
const int POINTS[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int calc_word_score(char word[]);

int main(void) {
    int player_scores[PLAYERS] = {0};
    char word[30];
    for (int player = 0; player < PLAYERS; player++) {
        printf("Player %d: ", player + 1);
        scanf("%s", word);

        int score = calc_word_score(word);
        player_scores[player] = score;
    }

    if (player_scores[0] > player_scores[1]) {
        printf("Player 1 wins!\n");
    } else if (player_scores[0] < player_scores[1]) {
        printf("Player 2 wins!\n");
    } else {
        printf("It's a tie!\n");
    }
    return 0;
}

int calc_word_score(char word[]) {
    int score = 0;
    for (int i = 0; i < strlen(word); i++) {
        for (int j = 0; j < 26; j++) {
            if (toupper(word[i]) == LETTERS[j]) {
                score += POINTS[j];
            }
        }
    }
    return score;
}