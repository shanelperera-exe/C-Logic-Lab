#include <stdio.h>

#define QUARTER 25
#define DIME 10
#define NICKLE 5
#define PENNY 1

int calc_quarters(int change);
int calc_dimes(int change);
int calc_nickels(int change);
int calc_pennies(int change);

int main(void) {
    int change;

    do {
        printf("Enter the change owed(¢): ");
        scanf("%d", &change);
    } while(change < 0);

    int num_of_quarters = calc_quarters(change);
    change -= num_of_quarters * QUARTER;

    int num_of_dimes = calc_dimes(change);
    change -= num_of_dimes * DIME;

    int num_of_nickels = calc_nickels(change);
    change -= num_of_nickels * NICKLE;

    int num_of_pennies = calc_pennies(change);
    change -= num_of_pennies * PENNY;

    int coins_sum = num_of_quarters + num_of_dimes + num_of_nickels + num_of_pennies;
    printf("Minimum coins needed: %d\n\n", coins_sum);

    printf("----- Coins ----\n");
    printf("x%d Quarters(25¢)\n", num_of_quarters);
    printf("x%d Dimes(10¢)   \n", num_of_dimes);
    printf("x%d Nickels(5¢) \n", num_of_nickels);
    printf("x%d Pennies(1¢) \n", num_of_pennies);

    return 0;
}

int calc_quarters(int change) {
    return change / QUARTER;
}

int calc_dimes(int change) {
    return change / DIME;
}

int calc_nickels(int change) {
    return change / NICKLE;
}

int calc_pennies(int change) {
    return change / PENNY;
}