#include <stdio.h>
#include <string.h>

int main(void) {
    FILE *file;

    file = fopen("phonebook.csv", "a");
    if (file == NULL) {
        printf("ERROR: Couldn't open phonebook.csv\n");
        return 1;
    }

    char name[25];
    char phone_number[15];

    printf("Name: ");
    fgets(name, 25, stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Phonenumber: ");
    fgets(phone_number, 15, stdin);
    phone_number[strcspn(phone_number, "\n")] = '\0';

    fprintf(file, "%s,%s\n", name, phone_number);

    printf("Contact saved.\n");
    fclose(file);

    return 0;
}