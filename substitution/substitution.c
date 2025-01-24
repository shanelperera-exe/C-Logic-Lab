/* Substitution Cipher Program
 * 
 * This program encrypts or decrypts text using a substitution cipher.
 * The key must be a 26-character string containing each letter of the alphabet exactly once.
 * 
 * Usage: ./substitution <KEY> <e|d>
 * 
 * Arguments:
 *   <KEY> - A 26-character string representing the substitution key.
 *   <e|d> - 'e' to encrypt or 'd' to decrypt. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define TEXT_LENGTH 200
#define KEY_LENGTH 26

int validate_key(char *key);
void encrypt(char text[], char *key);
void decrypt(char *text, char *key);
void key_to_uppercase(char *key);

int main(int argc, char *argv[]) {
    char text[TEXT_LENGTH];

    if (argc != 3) {
        printf("Usage: %s <KEY> <e|d>\n", argv[0]);
        return 1;
    }

    char *key;
    if (validate_key(argv[1])) {
        key = argv[1];
        key_to_uppercase(key);
    } 
    else {
        return 1;
    }

    if (tolower(argv[2][0]) == 'e') {
        printf("Plaintext: ");
        fgets(text, TEXT_LENGTH, stdin);
        text[strcspn(text, "\n")] = '\0';

        encrypt(text, key);

        printf("Ciphertext: %s\n", text);
    }
    else if (tolower(argv[2][0]) == 'd') {
        printf("Ciphertext: ");
        fgets(text, TEXT_LENGTH, stdin);
        text[strcspn(text, "\n")] = '\0';

        decrypt(text, key);

        printf("Plaintext: %s\n", text);
    }
    else {
        printf("Invalid mode. Please enter 'E' for Encrypt or 'D' for Decrypt\n");
        return 1;
    }

    return 0;
}

int validate_key(char *key) {
    int is_valid_key = true;

    if (strlen(key) != KEY_LENGTH) {
        printf("Key must contain 26 characters.\n");
        is_valid_key = false;
    }

    int chars_seen[26] = {0};

    for (int i = 0; i < strlen(key); i++) {
        if (!isalpha(key[i])) {
            printf("Key must only contain alphabetic characters.\n");
            is_valid_key = false;
            break;
        } else {
            int index = toupper(key[i]) - 'A';
            if (chars_seen[index] > 0) {
                printf("Key must not contain repeated characters.\n");
                is_valid_key = false;
                break;
            }
            chars_seen[index]++;
        }
    }

    
    return is_valid_key;
}

void encrypt(char text[], char *key) {
    for (int i = 0; i < strlen(text); i++) {
        if (isupper(text[i])) {
            text[i] = key[text[i] - 'A'];
        }
        else if (islower(text[i])) {
            text[i] = tolower(key[text[i] - 'a']);
        }
    }
}

void decrypt(char *text, char *key) {
    char reverse_key[26];
    for (int i = 0; i < 26; i++) {
        reverse_key[tolower(key[i]) - 'a'] = 'a' + i;
    }

    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            int index = tolower(text[i]) - 'a';
            if (islower(text[i])) {
                text[i] = tolower(reverse_key[index]);
            } else {
                text[i] = toupper(reverse_key[index]);
            }
        }
    }
}

void key_to_uppercase(char *key) {
    for (int i = 0; key[i] != '\0'; i++) {
        key[i] = toupper(key[i]);
    }
}