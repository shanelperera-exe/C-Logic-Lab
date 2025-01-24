#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define TEXT_SIZE 200

void encrypt(char text[], int key);

int main(int argc, char* argv[]) {
    char text[TEXT_SIZE];

    if (argc != 2 || !isdigit(argv[1][0])) {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int key = atoi(argv[1]);
    if (key < 0 || key > 26) {
        printf("Error: Key must be between 0 and 26\n");
        return 1;
    }

    printf("plaintext: ");
    fgets(text, TEXT_SIZE, stdin);
    encrypt(text, key);
    printf("ciphertext: %s\n", text);
    return 0;
}

void encrypt(char text[], int key) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char offset = isupper(text[i]) ? 'A' : 'a';
            text[i] = (text[i] - offset + key) % 26 + offset;
        }
    }
}