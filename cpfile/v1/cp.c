#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: ./cpfile source destination\n");
        return 1;
    }

    FILE *src = fopen(argv[1], "r");
    if (src == NULL) {
        printf("ERROR: Couldn't open source file %s\n", argv[1]);
        return 1;
    }

    FILE *dest = fopen(argv[2], "w");
    if (dest == NULL) {
        printf("ERROR: Couldn't open destination file %s\n", argv[2]);
        fclose(src);
        return 1;
    }

    char buffer[1024];
    size_t bytes;

    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes, dest);
    }

    fclose(src);
    fclose(dest);

    printf("File copied successfully.\n");
    return 0;
}