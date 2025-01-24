#include <stdio.h>
#include <string.h>

int check_card_legitimacy(long card_number);
void get_card_type(long card_number);

int main(void) {
    long card_number;
    int result;
    while (1) {
        printf("Enter Credit Card Number: ");

        result = scanf("%ld", &card_number);

        if (result == 1 && card_number > 0) { // Ensure a valid number is entered
            break; // Exit the loop if the input is valid
        } else {
            printf("Invalid input. Please enter a valid numeric card number.\n");
            // Clear the invalid input from the input buffer
            while (getchar() != '\n');
        }
    }
    
    int is_legit = check_card_legitimacy(card_number);

    if (is_legit) {
        printf("Valid card\n");
        get_card_type(card_number);
    }
    else {
        printf("Invalid Card.\n");
    }

    return 0;
}

int check_card_legitimacy(long card_number) {
/* Using Luhn’s Algorithm */
    long original_card_number = card_number;

    int sum_of_multiplied_digits = 0;
    int position = 1;
    while (card_number > 0) {
        long digit = card_number % 10;
        if (position % 2 == 0) {
            digit *= 2;  // Multiply every other digit by 2, starting with the number’s second-to-last digit
            // Add those products’ digits together (i.e., not the products themselves) 
            if (digit > 9) {
                sum_of_multiplied_digits += digit / 10; // Add the tens place digit
                sum_of_multiplied_digits += digit % 10; // Add the ones place digit
            } else {
                sum_of_multiplied_digits += digit; // Add those products’ digits together
            }             
        }
        card_number /= 10;
        position++;
    }

    int sum_of_not_multiplied_digits = 0;
    card_number = original_card_number;
    position = 0;
    while (card_number > 0) {
        long digit = card_number % 10;
        if (position % 2 == 0) {
            sum_of_not_multiplied_digits += digit;  // Get the sum of the digits that weren’t multiplied by 2               
        }
        card_number /= 10;
        position++;
    }

    int sum = sum_of_multiplied_digits + sum_of_not_multiplied_digits;
    
    return (sum % 10 == 0) ? 1 : 0;  // Check if the last digit in that sum is a 0. If it is 0 then the card is valid.
}

void get_card_type(long card_number) {
    char start[3];
    char card_type[15];

    snprintf(start, sizeof(start), "%02ld", card_number);
    if (strncmp(start, "34", 2) == 0 || strncmp(start, "37", 2) == 0) {
        strcpy(card_type, "AMEX");
    }
    else if (strncmp(start, "51", 2) == 0 || strncmp(start, "52", 2) == 0 || strncmp(start, "53", 2) == 0 || strncmp(start, "54", 2) == 0 || strncmp(start, "55", 2) == 0) {
        strcpy(card_type, "MASTERCARD");
    }
    else if (strncmp(start, "4", 1) == 0) {
        strcpy(card_type, "VISA");
    }
    else {
        strcpy(card_type, "UNKNOWN");
    }

    printf("Card Type: %s\n", card_type);
}